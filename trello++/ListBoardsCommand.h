#pragma once

#include <iostream>

#include "AbstractCommand.h"
#include "Config.h"
#include "TrelloApi.h"

using namespace std;

class ListBoardsCommand : public AbstractCommand {
public:
	ListBoardsCommand() : AbstractCommand("list boards") {}

	// TODO: implement, refactor
	virtual void operator()() {
		cout << "listing boards..." << endl;
		auto api = TrelloApi(TRELLO_API_BASE, TRELLO_KEY, TRELLO_TOKEN);
		api.ListBoards();
	}
};
