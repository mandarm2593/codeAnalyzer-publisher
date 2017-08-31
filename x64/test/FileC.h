#pragma once
#include "FileD.h"
#include "FileA.h"
typedef int abc;

void xyz() {}
namespace TestC {
	class FileA{};
	void ygt() {}
	class FileC {
	public:
		void showC();
	private:
		TestA::FileA a;
		FileD d;
	};

	void FileC::showC()
	{
		a.showA();
		d.showD();
		std::cout << "\nInside show function of FileC\n";
	}

}
 