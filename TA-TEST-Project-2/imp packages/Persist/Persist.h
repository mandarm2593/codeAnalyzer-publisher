#pragma once

/////////////////////////////////////////////////////////////////////
// Persist.h - XML persistence										//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017	//
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr2, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//																	//
/////////////////////////////////////////////////////////////////////
/*
* - Manual Information
This package creates a public interface to writing the database contents in a XML format. we need to create and save a databse 
before invoking this function.

Public Interface:
=================
makexml()   /prints database contents in a xml format


* - Build Process:
Required files
XMLDocument.h,XmlElement.h,NoSqlDb.h
Build commands
This is a static library builds with code analyzer
- devenv CodeAnalyzerEx.sln

* - Maintenance information
ver 1.0 : 11 Mar 2017
-	first release
*/



#include "../XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include <iostream>
#include "../NoSqlDb/NoSqlDb.h"
using namespace XmlProcessing;

class X {

	
public :
	std::string makexml(NoSqlDb<std::string> db);


};


inline std::string X::makexml(NoSqlDb<StrData> db) {


	using sPtr = std::shared_ptr < AbstractXmlElement >;

	sPtr root = makeTaggedElement("Dependency Table");

	for (unsigned int i = 0; i < db.keys().size(); ++i)
	{

		sPtr pKeyElem = makeTaggedElement("File Name");
		root->addChild(pKeyElem);
		sPtr pkElem = makeTextElement(db.keys().at(i));
		pKeyElem->addChild(pkElem);


		sPtr pChildren = makeTaggedElement("Dependencies");
		root->addChild(pChildren);


		for (unsigned int m = 0; m < db.value(db.keys().at(i)).child.size(); ++m)
		{
			sPtr pchild = makeTextElement(db.value(db.keys().at(i)).child.at(m));
			pChildren->addChild(pchild);
		}


	}


	sPtr docEl = makeDocElement(root);
	std::cout << "  " << docEl->toString();
	std::cout << "\n\n";
	return docEl->toString();
}

