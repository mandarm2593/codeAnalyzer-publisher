#pragma once
/////////////////////////////////////////////////////////////////////
// typetable.h - typeanalysis										//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017	 //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Typebased- Dependency Analyzer CSE687 Pr2, Mar-7  //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//																	//
/////////////////////////////////////////////////////////////////////
/*
* - Manual Information
This package just creates a typetableentry member variable to communicate with other packages to do 
typeanalysis and support dependency analysis.

Public Interface:
=================
there are no public interfaces instead there is a getter method.


* - Build Process:

Build commands
This is a static library builds with code analyzer
- devenv CodeAnalyzerEx.sln

* - Maintenance information
ver 1.0 : 4 Mar 2017
-	first release
*/

#include <unordered_map>
#include <iostream>
#include<vector>

class typetable

{
public:

	using mytablecolumns = std::pair<std::string, std::string>;
	using mytableentry = std::unordered_map<std::string, mytablecolumns>;


	mytableentry& getterx() {

		return mymap;
	}

	
private:

	mytableentry  mymap;

};