/*
 * test_main.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: robin
 */

#include <iostream>

#include "gtest/gtest.h"
#include "tests/fileTest.h"
#include "tests/CFG_test.h"
#include "tests/CYK_test.h"
#include "tests/LRParser_test.h"
#include "tests/ParseTable_test.h"
#include "tests/State_test.h"
#include "tests/PDA_test.h"

#include <string>
#include "utilities.h"
#include "CYKTable.h"
#include "CFG.h"
#include "Parser.h"
#include "Exception.h"
#include "ParseTable.h"
#include "LRParser.h"
#include "PDA.h"

int main(int argc, char **argv) {
	/*std::cout << "TESTS FOR CFG" << std::endl;

	std::map<std::string, std::vector<std::string> > rules;
	std::vector<std::string> temp;
	temp.push_back("a");
	rules["A"] = temp;
	rules["B"].push_back("AA");
	rules["C"].push_back("AB");
	rules["D"].push_back("AA");

	std::vector<std::string> var;
	var.push_back("A");
	var.push_back("B");
	var.push_back("C");
	var.push_back("D");

	std::vector<std::string> ter;
	ter.push_back("a");

	CFG q(var, ter, rules, "C");

	std::cout << q << std::endl;

	std::cout << "TESTS FOR CYK" << std::endl;
	// test empty string
	// test strings in the language
	// test strings not in the language

	// test string in easy language
	CYKTable c( rules, "C");
	bool a = c("aaa");
	if (a == true)
	{
		std::cout << "\t Test successful" << std::endl;
	}
	else
	{
		std::cout << "\t test unsuccessful" << std::endl;
	}

	// test string not in same language
	bool b= c("b");
	if (b == false)
	{
		std::cout <<"\t test successful" << std::endl;
	}
	else
	{
		std::cout << "\t test unsuccessful" <<std::endl;
	}*/

	/*try {
	CFG grammar("./../XML-Files/LR1-1.xml");
	ParseTable t(grammar);
	LRParser lrp(grammar);

	std::string input = "";
	if (lrp.parse(input)) {
		std::cout << "Inputstring \"" << input << "\" has been accepted!" << std::endl;
	}
	else {
		std::cout << "Inputstring \"" << input << "\" has not been accepted!" << std::endl;
	}

	std::cout << "END OF PROGRAM" << std::endl;
	}
	catch(Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}*/

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

	//CFG grammar("XML-Files/LR1-1.xml");
	//PDA::PDA pda(&grammar);
	//pda.toLaTeX("./LaTeX/LR1-1.tex");
	//std::cout << pda.containsString("xxxxx") << std::endl;

	//CFG grammar("XML-Files/LR1-1.xml");
	//PDA::PDA pda(&grammar);
	//std::cout << pda.containsString("xxx") << std::endl;

	std::cout << "program finished"	 << std::endl;
}

