// trello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include "ListBoardsCommand.h"

using namespace std;

template <typename T>
void println(T t) {
	cout << t << endl;
}

int main()
{
	vector< shared_ptr<AbstractCommand> > commands;
	commands.push_back(make_shared<ListBoardsCommand>());

	string input = "list boards";
	for (auto & cmd : commands) {
		if (cmd->IsMatch(input)) {
			(*cmd)();
		}
	}

    return 0;
}

