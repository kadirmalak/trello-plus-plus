#pragma once

#include "AbstractCommand.h"
#include <iostream>
using namespace std;

class ListBoardsCommand : public AbstractCommand {
public:
	ListBoardsCommand() : AbstractCommand("list boards") {}
	virtual void operator()() {
		cout << "listing boards..." << endl;
	}
};
