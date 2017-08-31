
/////////////////////////////////////////////////////////////////////
// StrComp.h - directed graph using tarzan's algorithm//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017   //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr2, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//	referenced from : www.geekdforgeeks.com				  		//
/////////////////////////////////////////////////////////////////////


#include "StrComp.h"
using namespace strong;

#ifdef STRCOMP_TEST



int main() {

	Graph g;
	g.setgraphsize(3);
	g.addEdge(1,0);
	g.addEdge(2, 0);
	g.addEdge(1, 3);
	g.SCC();

	


}
#endif // STRCOMP_TEST
