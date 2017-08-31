#pragma once
#include <iostream>

typedef char abcdef;

class FileD {
public:
	void showD();
};

void FileD::showD()
{
	std::cout << "\nInside show function of FileD\n";
}


