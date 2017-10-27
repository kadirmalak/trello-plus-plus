#pragma once

#include "AbstractCommand.h"
#include <iostream>
#include <curl/curl.h>
#include "Config.h"

using namespace std;

string response;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t len = size * nmemb;
	response.append(ptr, len);
	return len;
}

class ListBoardsCommand : public AbstractCommand {
public:
	ListBoardsCommand() : AbstractCommand("list boards") {}

	// TODO: implement
	virtual void operator()() {
		cout << "listing boards..." << endl;

		CURL *curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_DEFAULT);

		string URL = string{ TRELLO_API_BASE "/members/me/boards?key=" TRELLO_KEY "&token=" TRELLO_TOKEN };

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

			/* Perform the request, res will get the return code */
			res = curl_easy_perform(curl);
			/* Check for errors */
			if (res != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			}
			else
			{
				fprintf(stdout, "curl integration ok!\n");
			}

			/* always cleanup */
			curl_easy_cleanup(curl);
		}

		curl_global_cleanup();
	}
};
