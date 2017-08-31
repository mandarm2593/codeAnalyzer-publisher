#pragma once
/////////////////////////////////////////////////////////////////////
// DepAnal.h - type-based adependency analysis		               //
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017   //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr2, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//	source : Jim Fawcett, Syracuse University, CST 4-187           //
//              jfawcett@twcny.rr.com   							//
/////////////////////////////////////////////////////////////////////
/*
* - Package operation
This package performs almost all the operations of the Codeanalyzer project.It performs type analysis of the set of files and 
displays it in the form of a type table. then, dependency analysis is performed on the typetable and a dependency table is created
from which we store it in the database and make xml file. the xml file is stored as Project2.txt as default in the project directory.

Public Interface:
=================
-dotypeAnal() //does type analysis and prints the type table on a set of files
-ASTDist()    //calls functions that do dependency analysis, make xml file, find out the strong components and print them.


* - Build Process:
Required files
-StrComp.h, ActionsAndRules.h, typetabe.h, dependencytable.h
Build commands
This is a static library builds with code analyzer
- devenv CodeAnalyzerEx.sln

* - Maintenance information
ver 1.0 : 7 Mar 2017
-	first release
*/
#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <functional>
#include "../StrongComp/StrComp.h"
#include "../typetable/typetable.h"
#include "../deptable/dependencytable.h"
#include "../CodePublisher/CodePublisher.h"
#pragma warning (disable : 4101)  // disable warning re unused variable x, below
 //using namespace FileSystem;
using namespace strong;
using mytablecolumns = std::pair<std::string, std::string>;
using mytableentry = std::unordered_map<std::string, mytablecolumns>;
using deptableentry = std::unordered_map<std::string, std::set<std::string>>;
namespace CodeAnalysis
{


	class TypeAnal
	{
	public:
		using SPtr = std::shared_ptr<ASTNode*>;
		using mytablecolumns = std::pair<std::string, std::string>;
		using mytableentry = std::unordered_map<std::string, mytablecolumns>;
		TypeAnal();
		void doTypeAnal();
		void ASTDisp(std::string x);
	private:
		std::unordered_map<std::string, int> mymap;
		void DFS(ASTNode* pNode);
		NoSqlDb <std::string> DBnew;
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;
		typetable mytypetable;
		std::set<std::string> my_vector;
		dependencytable depT;
		FileSystem::Directory my_dir;
		FileSystem::Path my_ext;
		Graph g;
	};

	inline TypeAnal::TypeAnal() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
		// This is here to test detection of lambdas.
	}                                              // It doesn't do anything useful for dep anal.

	inline bool doDisplay(ASTNode* pNode)
	{
		static std::string toDisplay[] = {
		  "function", "lambda", "class", "struct", "enum", "alias", "typedef","namespace"
		};
		for (std::string type : toDisplay)
		{
			if (pNode->type_ == type)
				return true;
		}
		return false;
	}
	inline void TypeAnal::DFS(ASTNode* pNode)
	{
		static std::string path = "";
		if (pNode->path_ != path)
		{
			//std::cout << "\n    -- " << pNode->path_ << "\\" << pNode->package_;
			path = pNode->path_;
		}
		if (doDisplay(pNode))
		{
			//std::cout << "\n  " << pNode->name_;
			//std::cout << ", " << pNode->type_;
		}
		//typetable generation
		if ((pNode->type_ == "class") || (pNode->type_ == "struct") || (pNode->type_ == "enum") || (pNode->type_ == "namespace")) {
			mytablecolumns mytablecolumns_;
			std::pair<std::string, std::string> temp;
			mytablecolumns_.first = pNode->type_;
			mytablecolumns_.second = pNode->path_;
			mytypetable.getterx().insert(std::make_pair(pNode->name_, mytablecolumns_));
		}
		my_vector.insert(pNode->path_);
		for (auto pChild : pNode->children_)
			DFS(pChild);
	}

	//displays typetable of a set of files
	inline void TypeAnal::doTypeAnal()
	{
		std::cout << "\n  starting type analysis:\n";
		ASTNode* pRoot = ASTref_.root();
		DFS(pRoot);
		std::cout << endl;
		std::cout << std::endl;
		std::cout << "----------------------------------------------------DISPLAYING TYPETABLE REQUIREMENT #4-----------------------------------------------------------\n";
		std::cout << std::setw(20) << "Name" << std::setw(40) << "Type" << std::setw(40) << "File\n";
		for (auto it = mytypetable.getterx().begin(); it != mytypetable.getterx().end(); ++it) {
			std::cout << std::setw(30) << it->first;
			std::cout << std::setw(30) << it->second.first<<std::setw(10)<<" ";
			std::cout << std::setw(50) << it->second.second << std::setw(30) << std::endl;;
		}
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
	}


	//does dependency analysis and provides a mechanism for xml file generation and Data base creation
	inline void TypeAnal::ASTDisp(std::string x) {
		std::cout << "===================================================DISPLAYING DEPENDENCY TABLE REQUIREMENT #5 ========================================================================================";
		for (auto iter = my_vector.begin(); iter != my_vector.end(); ++iter) {
			DBnew = depT.makedeptable(mytypetable, *iter, x);
		}
		std::cout << "==========================================STORING DEPENDENCIES IN NOSQL DATABASE FROM PROJECT 1============================================================";
		for (auto iter = my_vector.begin(); iter != my_vector.end(); ++iter) {
			depT.makedatabase(*iter);
		}
		
		
		CodePublisher c;
		c.openMainpage(x);
		std::unordered_map<int, std::string> setVal;
		std::unordered_map<std::string, int> graph_map;
		Graph graph;
		graph.setgraphsize((int)DBnew.keys().size()); int k = 0;
		for (std::string key : DBnew.keys())
		{
			graph_map[key] = k;
			setVal[k] = key;
			k++;
		}
		for (std::string key : DBnew.keys())
		{
			Element<StrData> dependencies = DBnew.value(key);
			std::vector<std::string> myVec = dependencies.child;
			//starting strong component analysis		
			for (std::string child : myVec)
			{
				if (!(key == child))
				{
					graph.addEdge(graph_map[key], graph_map[child]);
				}
			}
		}
		graph.setFileGraphPath(setVal);
		cout << "\n===========================================DISPLAYING STRONG COMPONENTS REQUIREMENT #6===========================================\n";
		graph.SCC();
		if ((x == "") || (x == "*.cpp") || (x == ".*h") || (x == "/m") || (x == "/s") || (x == "/a") || (x == "/r") || (x == "/d") || (x == "/b") || (x == "/f")) {
			x = "Project2.txt";
		}
		else
		{
			x = x;
		}
		//depT.makexml(x);
	}
}

