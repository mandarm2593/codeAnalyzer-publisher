/////////////////////////////////////////////////////////////////////
// dependencytable.cpp - dependency analysis and database creation	//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017  //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   TypeBased-Dependency Analyzer CSE687 Pr2, Mar-7 //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//																	//
/////////////////////////////////////////////////////////////////////
#include "../CodePublisher/CodePublisher.h"
#include "dependencytable.h"
dependencytable::dependencytable() :
	ASTref_(Repository::getInstance()->AST())

{
}

//making database from project 1
int dependencytable::makedatabase(std::string filespec) {
	if (filespec != "") {
		std::cout << "\n" << DB.value(filespec).show();
	}

	return 0;
}

//database contents to XML string
 int dependencytable::makexml(std::string xml) {
	std::ofstream myfile;

	myfile.open(xml);

	std::cout << "\n==========================================================SAVING DATABASE CONTENTS IN XML FORMAT TO A SPECIFIED FILE(default : projectdirectory/x64/release/Project2.txt) REQUIREMENT #7===============================\n";
	X x;
	myfile << x.makexml(DB);
	myfile.close();

	return 0;
}

 //starting dependency analysis on a set of files 
 NoSqlDb<StrData> dependencytable::makedeptable(typetable& x, std::string filespec, std::string xmlname) {
	if (filespec != "") {
		static std::string path = "";
		try {
			std::ifstream in(filespec);
			if (!in.good())
			{
				std::cout << "cant open";
				return DB;
			}else
			{	Toker toker;
				toker.returnComments();	toker.attach(&in);
				mytableentry my = x.getterx();std::set<std::string> tempvector;
				do
				{
					std::string tok = toker.getTok();
					for (auto tt : my) {
						if (tok == tt.first) {
							tempvector.insert(tt.second.second);
						}
					}
				} while (in.good());
				elementadd.name = filespec;
				while (!elementadd.child.empty())
				{
					elementadd.child.pop_back();
				}
				for (auto iter = tempvector.begin(); iter != tempvector.end(); ++iter) {
					elementadd.child.push_back(*iter);
				}
				DB.save(elementadd.name, elementadd);
				deptableentry_.insert(std::make_pair(filespec, tempvector));
			}
			
			CodePublisher cp;
			cp.CreateHTMLFiles(deptableentry_,xmlname);
			
			
			std::cout << std::endl;
			std::cout << std::setw(60) << std::left << filespec<<"\t\tDEPENDS ON =>";
			for (auto set_it = deptableentry_[filespec].begin(); set_it != deptableentry_[filespec].end(); ++set_it) {
				std::cout << std::endl;
				std::cout <<std::setw(100)<<" "<< *set_it << "\n";
			}
		} catch (std::logic_error& ex)
		{
			std::cout << "\n  " << ex.what();
		}
		std::cout << "\n\n";
	}
	return DB;
}


#ifdef DEPENDENCYTABLE_TEST


 int main() {


	 d.makexml("filename.txt");
	 //other interface are not included in this test stub because they are dependent on multiple files to suppy the arguments 
	 //just like DepAnal.cpp
	 
	 
	 //testing tependency table;


 }







#endif 
