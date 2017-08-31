#pragma once

#include <iostream>
#include "FileC.h"
typedef int abc;


class FileB {
public:
	void showB();
private:
	TestC::FileC c;

};

void FileB::showB() {
	std::cout << "\nInside File B show Function\n";
	c.showC();
}


