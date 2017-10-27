#pragma once

#include <string>
using namespace std;

class TrelloApi {
public:
	TrelloApi(const string & apiBase) : _apiBase{ apiBase } {

	}

	void ListBoards(const string & username) {
		string url = _apiBase + "/members/" + username + "/boards";

	}
private:
	string _apiBase;
};