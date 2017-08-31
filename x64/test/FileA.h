#pragma once

#include "FileB.h"
#include "FileC.h"
#include <iostream>

typedef int abc;
struct  x
{

};
void abc() {}
namespace TestA {
	void def() {}
	class FileA {
	public:
		void showA();
	private:
		FileB fileB;
		TestC::FileA a;
	};

	void FileA::showA() {
		std::cout << "\nInside Show Function of FileA\n";
		fileB.showB();
	}
}
