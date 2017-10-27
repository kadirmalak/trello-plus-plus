#pragma once

#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

// TODO: don't use global variable here
string response;

// TODO: don't use global function here
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t len = size * nmemb;
	response.append(ptr, len);
	return len;
}

class TrelloApi {
public:
	TrelloApi(const string & apiBase, const string & key, const string & token) 
		: _apiBase{ apiBase }, _key{ key }, _token{ token } {
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		}
	}

	~TrelloApi() {
		if (curl) {
			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
	}

	void ListBoards() {
		if (!curl) {
			fprintf(stderr, "curl is not ready\n");
			return;
		}

		//response.clear();
		// TODO: clear response buffer here
		string url = _apiBase + "/members/me/boards?key=" + _key + "&token=" + _token;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return;
		}
		
		Document d;
		d.Parse(response.c_str());

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
	CURL *curl;
	CURLcode res;
};