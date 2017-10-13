#pragma once
#include <string>
#include <regex>

using namespace std;

class AbstractCommand {
public:
	AbstractCommand(const string & exp) : _exp{exp}, _re{regex("^" + exp + "$")}{}
	virtual void operator()() = 0;
	bool IsMatch(const string & input) {
		return regex_search(input, _matches, _re);
	}
protected:
	smatch _matches;
	string _exp;
	regex _re;
};
