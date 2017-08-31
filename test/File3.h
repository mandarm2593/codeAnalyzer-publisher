#pragma once
#include "File4.h"
#include "File1.h"

void xyz() {}
namespace Test3 {
	void x() {}
	class File3 {
	public:
		void show3();
	private:
		Test1::File1 a;
		File4 d;
	};

	void File3::show3()
	{
		a.show1();
		d.show4();
		std::cout << "\nInside show function of File3\n";
	}

}
 