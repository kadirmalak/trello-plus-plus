#pragma once

#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using std::string;
using rapidjson::Document;

class TrelloApi {
public:
	// static callback for curl
	static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
	{
		auto _this = static_cast<TrelloApi*>(userdata);
		return _this->WriteCallback(ptr, size, nmemb);
	}

	TrelloApi(const string & apiBase, const string & key, const string & token) 
		: _apiBase{ apiBase }, _key{ key }, _token{ token } {
		
		curl_global_init(CURL_GLOBAL_DEFAULT);
		_curl = curl_easy_init();
		if (_curl) {
			curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, TrelloApi::write_callback);
			curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this); // we're passing this as *userdata
		}
	}

	~TrelloApi() {
		if (_curl) {
			curl_easy_cleanup(_curl);
		}
		curl_global_cleanup();
	}

	size_t WriteCallback(char *ptr, size_t size, size_t nmemb)
	{
		size_t len = size * nmemb;
		_response.append(ptr, len);
		return len;
	}

	void ListBoards() {
		if (!_curl) {
			fprintf(stderr, "curl is not ready\n");
			return;
		}

		//response.clear();
		// TODO: clear response buffer here
		string url = _apiBase + "/members/me/boards?key=" + _key + "&token=" + _token;
		curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
		_res = curl_easy_perform(_curl);
		/* Check for errors */
		if (_res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(_res));
			return;
		}
		
		Document d;
		d.Parse(_response.c_str());

		if (d.HasParseError()) {
			fprintf(stderr, "could not parse response\n");
			return;
		}

		for (auto & listVal : d.GetArray())
		{
			fprintf(stdout, " - %s\n", listVal.GetObjectW()["name"].GetString());
		}
	}
private:
	string _apiBase;
	string _key;
	string _token;
	string _response;
	CURL *_curl;
	CURLcode _res;
};