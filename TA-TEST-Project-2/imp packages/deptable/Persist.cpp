/////////////////////////////////////////////////////////////////////
// Persist.h - persisting data in xml format						//
//  Mandar Mathure, CSE687 - Object Oriented Design, Spring 2017	//
//																   //
//  Language:      Visual C++ 2015		                           //
//  Platform:      Lenovo y700, Windows 10						   //
//  Application:   Dependency Analyzer CSE687 Pr2, Mar-7           //
//  Author:        Mandar Mathure, CST 4-187, Syracuse University  //
//                 (315) 949-8682, mmathure@syr.edu                //
//																	//
/////////////////////////////////////////////////////////////////////

#include "Persist.h"
std::string X::makexml(NoSqlDb<StrData> db) {


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




#ifdef PERSIST_TEST

/*-------------------------------------------------------test stub for persist package--------------------------------------------------------------------------*/

int main() {

	


}


#endif // PERSIST_TEST
