/*
 * test_main.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: robin
 */

#include <iostream>
#include "CYKTable.h"
#include "CFG.h"


int main() {
	std::cout << "TESTS FOR CFG" << std::endl;

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
	}
}

