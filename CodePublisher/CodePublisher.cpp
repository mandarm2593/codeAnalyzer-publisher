/////////////////////////////////////////////////////////////////////
// CodePublisher.cpp - Publish source code files 		               //
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017   //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr3, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//	source : Jim Fawcett, Syracuse University, CST 4-187           //
//              jfawcett@twcny.rr.com   							//
/////////////////////////////////////////////////////////////////////
#include "CodePublisher.h"

#ifdef TEST_CodePublisher



int main() {

	CodePublisher cp;
	dependencytable dp;
	std::string name = "filename.htm";
	cp.CreateHTMLFiles(dp.getter_(),name);
	cp.openMainpage(name);




}

#endif // TEST_CodePublisher