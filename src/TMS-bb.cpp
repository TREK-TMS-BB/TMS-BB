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

int main( int argc, char* argv[]) {

	if (argc != 3) {
		std::cout << "Please specify 1 file to use and a string to test" << std::endl;
		return 0;
	}
	else {
		try {
		Grammar::CNF_CFG cnf(argv[1]);
		bool answer = cnf.check_string(argv[2]);

		const Grammar::CYKTable cyk = cnf.getCYK();
		std::cout <<cyk<< std::endl;

		if (answer) {
			std::cout << "String is in the Grammar" << std::endl;
		}
		else {
			std::cout << "String is not in the Grammar" << std::endl;
		}
		}
		catch (Exception &e) {
			std::cout << e.what() << std::endl;
			return 0;
		}
	}

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

	/*
	TM::TuringMachine t("TM-Files/incr.tm");
	std::cout << t << std::endl;

	std::vector<TM::TapeSymbol> temp;
	temp.push_back(TM::TapeSymbol(1));
	temp.push_back(TM::TapeSymbol(1));
	temp.push_back(TM::TapeSymbol(0));

	try {
		t.simulate(temp);
		t.simulate(t.getOutput());
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}


	std::cout << t << std::endl;

	std::cout << "program finished"	 << std::endl;
	*/



	//CFGParser CFGP("cfg.xml");
	return 0;
}
