#pragma once
/////////////////////////////////////////////////////////////////////
// StrComp.h - directed graph using tarzan's algorithm//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017	   //
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr2, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//	referred from www.geeksforgeeks.com								//
/////////////////////////////////////////////////////////////////////
/*
* - Manual Information
This package creates the strong component graph using tarzan's algorithm.

Public Interface:
=================
void addEdge(int v, int w);																		// function to add an edge to graph
void setGraphSize(int a);																		// to set the graph size
void setFileGraphPath(std::unordered_map<int, std::string> setVal) {get_MapVal=setVal;}			//to get the files from key
void SCC();																						// prints strongly connected components


* - Build Process:
Required files
- StrComp.h,StrComp.cpp
Build commands
This is a static library builds with code analyzer
- devenv CodeAnalyzerEx.sln

* - Maintenance information
ver 1.0 : 11 Mar 2017
-	first release
*/

#include <string>
#include<iostream>
#include <list>
#include <stack>
#include <algorithm>
#include "../NoSqlDb/NoSqlDb.h"
#include<unordered_map>
#define NIL -1
using namespace std;
using Key = std::string;
using StrData = std::string;
using Keys = std::vector<std::string>;
// A class that represents an directed graph
namespace strong
{
	class Graph
	{
		int V;    // No. of vertices
		list<int> *adj;    // A dynamic array of adjacency lists
		std::unordered_map<int, std::string> get_MapVal;
		// A Recursive DFS based function used by SCC()
		void SCCUtil(int u, int disc[], int low[],
			stack<int> *st, bool stackMember[]);
		NoSqlDb<StrData> dbStrong;
		
	public:
		Graph();   // Constructor
		void addEdge(int v, int w);   // function to add an edge to graph
		void setgraphsize(int a);
		void setFileGraphPath(std::unordered_map<int, std::string> setVal) { get_MapVal = setVal; }
		void displayStrongComponentDB();
		void SCC();    // prints strongly connected components
		

	};

	inline Graph::Graph()
	{
	}

	inline void Graph::addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}

	inline void Graph::setgraphsize(int a)
	{
		this->V = a;
		adj = new list<int>[a];
	}

	// A recursive function that finds and prints strongly connected
	// components using DFS traversal
	inline void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
		bool stackMember[])
	{
		static int time = 0;
		// Initialize discovery time and low value
		disc[u] = low[u] = ++time;
		st->push(u);
		stackMember[u] = true;

		// Go through all vertices adjacent to this
		list <string> strongComponents;
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = *i;  // v is current adjacent of 'u'
						 // If v is not visited yet, then recur for it
			if (disc[v] == -1)
			{
				SCCUtil(v, disc, low, st, stackMember);
				low[u] = min(low[u], low[v]);
			}
			else if (stackMember[v] == true)
				low[u] = min(low[u], disc[v]);
		}
		int w = 0;  // To store stack extracted vertices
		if (low[u] == disc[u])
		{
			while (st->top() != u)
			{
				w = (int)st->top();
				std::cout << get_MapVal[w] << "  ";
				stackMember[w] = false;
				st->pop();
			}
			w = (int)st->top();
			std::cout << get_MapVal[w] << "  " << "\n";
			stackMember[w] = false;
			st->pop();
		}
	}

	inline void Graph::displayStrongComponentDB()
	{

		std::string name;
		Element<std::string> elem;
		std::cout << "-------------------- Displaying Strong Componenents in NoSql Database -------------------------- \n";
		for (auto it : get_MapVal) {
			name = "Strong Component";
			elem.name = name;
			elem.child.push_back(it.second + "\n");
		}
		dbStrong.save(elem.name, elem);
		Keys keys = dbStrong.keys();
		for (Key itm : keys) {
			std::cout << " " << itm;
			std::cout << " " << dbStrong.value(itm).show();
		}
		std::cout << "-------------------- Persisting Strong Componenents of NoSql Database in Xml File -------------------------- \n";
		
	}

	inline void Graph::SCC()
	{
		int *disc = new int[V];
		int *low = new int[V];
		bool *stackMember = new bool[V];
		stack<int> *st = new stack<int>();

		// Initialize disc and low, and stackMember arrays
		for (int i = 0; i < V; i++)
		{
			disc[i] = NIL;
			low[i] = NIL;
			stackMember[i] = false;
		}

		// Call the recursive helper function to find strongly
		// connected components in DFS tree with vertex 'i'
		for (int i = 0; i < V; i++)
			if (disc[i] == NIL)
				SCCUtil(i, disc, low, st, stackMember);
	}

}