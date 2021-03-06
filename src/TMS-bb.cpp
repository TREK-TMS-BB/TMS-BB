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
#include "ParseTable.h"
#include "TuringMachine.h"
#include "LRParser.h"
#include "PDA.h"
#include "LinkTM.h"
#include "BareBonesStatement.h"
#include "BBParser.h"

int main( int argc, char* argv[]) {

	/*
	 * ROBIN PHASE 1
	 */
//	if (argc != 3) {
//		std::cout << "Please specify 1 file to use and a string to test" << std::endl;
//		return 0;
//	}
//	else {
//		try {
//		Grammar::CNF_CFG cnf(argv[1]);
//		bool answer = cnf.check_string(argv[2]);
//
//		const Grammar::CYKTable cyk = cnf.getCYK();
//		std::cout <<cyk<< std::endl;
//
//		if (answer) {
//			std::cout << "String is in the Grammar" << std::endl;
//		}
//		else {
//			std::cout << "String is not in the Grammar" << std::endl;
//		}
//		}
//		catch (Exception &e) {
//			std::cout << e.what() << std::endl;
//			return 0;
//		}
//	}

	/*
	 * KRISTOF PHASE 1
	 */
	/*
	if (argc != 4) {
		std::cout << "Usage: ./*program-name* *CFG-file* *ParseTable file* *input string*" << std::endl;
		return 0;
	}
	else {
		try {
			std::cout << "--- Program: Kristof's LR1Parser ---" << std::endl << std::endl;

			Grammar::CFG grammar(argv[1]);
			parser::LRParser lrp(grammar, argv[2]);

			std::string input = argv[3];
			if (lrp.parse(input)) {
				std::cout << "Inputstring \"" << input << "\" has been accepted!" << std::endl;
			}
			else {
				std::cout << "Inputstring \"" << input << "\" has not been accepted!" << std::endl;
			}
		}
		catch (Exception &e) {
			std::cout << e.what() << std::endl;
			return 0;
		}
	}


	std::map<std::string, std::vector<std::string> > rules;
	std::vector<std::string> temp;
	temp.push_back("a");
	rules["A"] = temp;
	rules["B"].push_back("AA");
	rules["C"].push_back("AB");
	rules["D"].push_back("AA");
	Grammar::CYKTable c( rules, "C");
	std::cout << c("aaa") << std::endl;
	std::cout << c << std::endl;
	*/

	/*parser::TMParser test("TM-Files/Example.tm");
	std::cout << test << std::endl << std::endl;

	parser::TMParser test2("TM-Files/faultyExample.tm");
	std::cout << test2 << std::endl;*/

	//
	// TM use for development

	/*TM::TMProgram t("TM-Files/clear.tm");
	*/

	//t.renameStates();

	//TM::renameStates("TM-Files/clear.tm", "TM-Files/clearRen.tm");

	parser::BBParser BBp;;
	BB::BareBonesProgram prog = BBp.parseBB("BB-Files/test.bb");
	prog.createTMFile("TM-Files/test.tm");
	/*std::vector<std::shared_ptr<BB::BareBonesStatement>> vect;
	std::shared_ptr<BB::BareBonesStatement> ptr (new BB::BBdecr(1));
	std::shared_ptr<BB::BareBonesStatement> ptr2 (new BB::BBincr(2));

	vect.push_back(ptr);
	vect.push_back(ptr2);
	BB::BBwhile test(1, vect);
	TM::TMProgram testP = test.createCode();
	std::ofstream out;
	out.open("TM-Files/test.tm");
	out << testP << std::endl;*/

	/*std::vector<std::string> progs = {"TM-Files/incr2.tm","TM-Files/decr.tm", "TM-Files/incr.tm"};

	//TM::linkFiles("TM-Files/incr2.tm","TM-Files/decr.tm", "TM-Files/test.tm" );
	TM::linkFiles(progs, "TM-Files/test.tm");*/
	TM::TuringMachine t;

	TM::TMProgram tmp("TM-Files/test.tm");


	std::cout << t << std::endl;



	try {
		t.simulate(tmp);
		//t.simulate(t.getOutput());
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}


//	std::cout << t << std::endl;
	std::cout << "program finished"	 << std::endl;


	// =====================================
	// 			PDA DEMO CHANGETYPE
	// =====================================
	/*
	std::cout << "=================" << std::endl;
	std::cout << "RUNNING TYPE DEMO" << std::endl;
	std::cout << "=================" << std::endl << std::endl;

	try {
		Grammar::CFG Grammar(argv[1]);
		PDA::PDA pda(&Grammar);
		std::cout << "- SETUP PDA FROM CFG FILE: " << argv[1] << std::endl;

		pda.toLaTeX("./LaTeX/stackAcceptance1.tex");
		std::cout << "- CURRENT PDA PRINTED TO LaTeX: ./LaTeX/stackAcceptance1.tex" << std::endl;
		pda.toFinalStateAcceptance();
		std::cout << "- CHANGED TO FINAL STATE ACCEPTANCE." << std::endl;
		pda.toLaTeX("./LaTeX/stateAcceptance.tex");
		std::cout << "- CURRENT PDA PRINTED TO LaTeX: ./LaTeX/stateAcceptance.tex" << std::endl;
		pda.toEmptyStackAcceptance();
		std::cout << "- CHANGED TO EMPTY STACK ACCEPTANCE." << std::endl;
		pda.toLaTeX("./LaTeX/stackAcceptance2.tex");
		std::cout << "- CURRENT PDA PRINTED TO LaTeX: ./LaTeX/stackAcceptance2.tex" << std::endl;

		std::cout << std::endl << "========================" << std::endl;
		std::cout << "PROGRAM FINISHED RUNNING" << std::endl;
		std::cout << "========================" << std::endl;
	}

	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}
	*/
	// =====================================
	//		  PDA DEMO CONTAINSSTRING
	// =====================================
	/*
	std::cout << "===================" << std::endl;
	std::cout << "RUNNING STRING DEMO" << std::endl;
	std::cout << "===================" << std::endl << std::endl;

	try {
		Grammar::CFG Grammar(argv[1]);
		PDA::PDA pda(&Grammar);
		std::cout << "- SETUP PDA FROM CFG FILE: " << argv[1] << std::endl;

		bool contains = pda.containsString(argv[2]);
		std::cout << "- TESTING WHETHER STRING \"" << argv[2] << "\" IS ACCEPTED." << std::endl;
		if (contains) {
			std::cout << "\tThe PDA accepts the string \"" << argv[2] << "\"." << std::endl;
		}
		else {
			std::cout << "\tThe PDA does not accept the string \"" << argv[2] << "\"." << std::endl;
		}

		std::cout << std::endl << "========================" << std::endl;
		std::cout << "PROGRAM FINISHED RUNNING" << std::endl;
		std::cout << "========================" << std::endl;
	}

	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}
	*/


	//CFGParser CFGP("cfg.xml");
	return 0;
}
