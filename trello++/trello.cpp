// trello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <typename T>
void println(T t) {
	cout << t << endl;
}

int main()
{
	println("hello world!");
    return 0;
}

