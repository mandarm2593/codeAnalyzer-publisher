#pragma once

/////////////////////////////////////////////////////////////////////
// CodePublisher.h - Publish source code files 		               //
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
/*
* - Package operation
this package is an added functionality to the code analyzer project. it includes functions to publish the analysed files as html web pages 
by linking a css style file and a java script file for show/hide buttons.
Public Interface:
=================
createHTMLfiles() --creates HTML files based on the dependency table
createHTMlcontent()--HTML content generator and parser
openMainpage()--open default index page in system browser. 


* - Build Process:
Required files
-dependencytable.h
Build commands
This is a static library builds with code analyzer
- devenv CodeAnalyzerEx.sln

* - Maintenance information
ver 1.0 : 2 April 2017
-	first release
*/


#include<iostream>
#include "../deptable/dependencytable.h"
#include <set>

class CodePublisher
{
	std::string cssloc = "../../styling.css";
	std::string jssloc = "../../jshidebutton.js";
	std::string content;
	std::string lt = "<";
	std::string gt = ">";
	std::string openbrac = "{";
	std::string closebrac = "}";
	std::string HTML_endTags = "</pre> \n</body>\n </html>";
	std::string mystring;
public:
	void CreateHTMLFiles(std::unordered_map<std::string, std::set<std::string>> deptable,std::string x);
	void openMainpage(std::string name);
	std::string createHTMLcontent(std::string content);

};

inline void CodePublisher::CreateHTMLFiles(std::unordered_map<std::string, std::set<std::string>> deptable,std::string x) {
	std::ofstream homepage;
	std::string mainpage;
	if ((x == "") || (x == "*.cpp") || (x == ".*h") || (x == "/m") || (x == "/s") || (x == "/a") || (x == "/r") || (x == "/d") || (x == "/b") || (x == "/f")) 
	mainpage = "../../Mainpage.htm";	
	else mainpage = "../../" + x + ".htm";	
	mainpage = FileSystem::Path::getFullFileSpec(mainpage);
	homepage.open(mainpage);	
	std::string deploc="../../TA-TEST-Project-2/.htm files/";
	deploc = FileSystem::Path::getFullFileSpec(deploc);
	cssloc = FileSystem::Path::getFullFileSpec(cssloc);
	jssloc = FileSystem::Path::getFullFileSpec(jssloc);
	homepage << "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"" + cssloc + "\">" + "\n";
	homepage << "<h3> Index Page</h3>\n <p style=\"font-size:11\"> The name of this page can be given as the last command line argument<br>default name is Mainpage.htm if no argument is given<br>All the HTML files are generated in (projectdirectory)/TA-TEST-Project-2/.htm files/<p>";
	homepage << "\n <a href =\"" + cssloc + "\"><label>styling.css</label></a>,<a href = \"" +jssloc + "\"><label>jshidebutton.js</label> </a></head><body><br><br> List of files : <pre><br>";
	std::string HTMLtags = "<html><head><script src=\""+jssloc+"\"></script><link rel=\"stylesheet\" type=\"text/css\" href=\""+cssloc+"\">"+"\n </head>  \n <body> \n <pre>\n";	
	for (auto it = deptable.begin(); it != deptable.end(); ++it) {
		std::string mycontent = "";
		std::vector<std::string> str;
		for (auto set_it = it->second.begin(); set_it != it->second.end(); ++set_it) {
			 mystring = *set_it;
			size_t posi = mystring.find_last_of("\\");
			mystring = mystring.substr(posi + 1, std::string::npos-1);			
			str.push_back("<a href =\""+deploc+mystring+".htm\">"+"<label>"+mystring+"</label></a>");
		}				
		size_t pos = it->first.find_last_of("\\");
		std::string name = it->first.substr(pos + 1, std::string::npos);
		std::string loc = "../../TA-TEST-Project-2/.htm files/" + name + ".htm";
		loc = FileSystem::Path::getFullFileSpec(loc);
		std::ofstream myfile1(loc);
		myfile1 << HTMLtags;
		myfile1 << "<h3> " + name + "</h3>";
		myfile1 << "<h4>Dependencies:</h4>";
		for (std::string a : str) {
			myfile1 << a<<" ";
		}
		myfile1 << "\n ----------------------------------------------------------------------------------------------------\n\n";
		std::ifstream myfile(it->first);
		while (!myfile.eof())
		{
			getline(myfile, content);			
			mycontent.append(createHTMLcontent(content));
			mycontent.append("\n");				
		}
		myfile1 << mycontent;
		myfile1 << HTML_endTags;				
		homepage << " <a href =\"" + loc + "\">" +"<label>"+ name+"</label>" + "</a><br>";				
	}	
	homepage.close();	
	}


	inline void CodePublisher::openMainpage(std::string name) {
		std::string dest;
		if ((name == "") || (name == "*.cpp") || (name == ".*h") || (name == "/m") || (name == "/s") || (name == "/a") || (name == "/r") || (name == "/d") || (name == "/b") || (name == "/f")) {

			dest= "../../Mainpage.htm";
		}
		else
		{
			dest = "../../" + name + ".htm";
		}		
		std::string command("start \"\" \"" + dest + "\"");
		std::system(command.c_str());
	}


	inline std::string CodePublisher::createHTMLcontent(std::string content) {
		static size_t m = 0;

		std::string temp = "";
		for (int i = 0; i< content.length(); ++i) {
			if (content[i] == '<')
				temp = temp + "&lt;";
			else if (content[i] == '>')
				temp = temp + "&gt;";
			else if (content[i] == '{') {
				temp = temp + "<br> <button onclick = \"hidebutton('" + std::to_string(m) + "')\">+</button> { <Span id=\"" + std::to_string(m) + "\"  > ";
			}
			else if (content[i] == '}') {
				temp = temp + "<br></Span>} ";
			}
			else temp = temp + content[i];
			m++;
		}

		return temp;


	}