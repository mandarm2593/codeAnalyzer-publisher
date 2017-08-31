#pragma once

#include "File2.h"
#include "File3.h"
#include <iostream>

struct  x
{

};
void abc() {}
namespace Test1 {
	void def() {}
	class File1 {
	public:
		void show1();
	private:
		File2 file2;
		Test3::File1 a;
	};

	void File1::show1() {
		std::cout << "\nInside Show Function of File1\n";
		file2.show2();
	}
}
