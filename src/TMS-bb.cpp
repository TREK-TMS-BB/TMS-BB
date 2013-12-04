//============================================================================
// Name        : TMS-bb.cpp
// Author      : TREK
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CYKTable.h"
#include "CFG.h"
#include "Parser.h"
#include "TMParser.h"
#include "TuringMachine.h"

int main() {
	/*
	std::map<std::string, std::vector<std::string> > rules;
	std::vector<std::string> temp;
	temp.push_back("a");
	rules["A"] = temp;
	rules["B"].push_back("AA");
	rules["C"].push_back("AB");
	rules["D"].push_back("AA");
	Grammar::CYKTable c( rules, "C");
	std::cout << c("aaa") << std::endl;
	std::cout << c << std::endl;*/

	/*parser::TMParser test("TM-Files/Example.tm");
	std::cout << test << std::endl << std::endl;

	parser::TMParser test2("TM-Files/faultyExample.tm");
	std::cout << test2 << std::endl;*/

	TM::TuringMachine t("TM-Files/incr.tm");
	std::cout << t << std::endl;

	std::vector<TM::TapeSymbol> temp;
	temp.push_back(TM::TapeSymbol(1));
	temp.push_back(TM::TapeSymbol(1));
	temp.push_back(TM::TapeSymbol(0));

	try {
		t.simulate(temp);
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << t << std::endl;

	std::cout << "program finished"	 << std::endl;




	//CFGParser CFGP("cfg.xml");
	return 0;
}
