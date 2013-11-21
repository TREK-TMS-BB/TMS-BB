/*
 * PDA_test.h
 *
 *  Created on: Nov 21, 2013
 *      Author: tom
 */

#ifndef PDA_TEST_H_
#define PDA_TEST_H_

#include <iostream>
#include <map>

#include "../PDA.h"
#include "fileTest.h"
#include <gtest/gtest.h>

namespace tests {

	class PDATest: public testing::Test {
		friend class PDA::PDA;
	protected:
		PDA::PDA pda;
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	};

	TEST_F(PDATest, PDAConstructorTest) {
		CFG cfg("XML-Files/cfg.xml");
		PDA::PDA pda(&cfg);
		PDA::PDAType type = PDA::acceptByEmptyStack;

		std::vector<char> input_alphabet;
		std::vector<std::string> stack_alphabet;

		std::vector<std::string> terminals = cfg.getTerminals();
		std::vector<std::string> variables = cfg.getVariables();
		std::map<std::string, std::vector<std::string>> rules = cfg.getRules();
		std::string startstring = cfg.getStart();

		for (auto terminal : terminals) {
			input_alphabet.push_back(terminal[0]);
			stack_alphabet.push_back(terminal.substr(0, 1));
		}
		for (auto variable : variables) {
			stack_alphabet.push_back(variable.substr(0, 1));
		}

		std::string start_state = "q";
		std::string start_stack = startstring;

		EXPECT_EQ(pda.get_cfg(), &cfg);
		EXPECT_EQ(input_alphabet, pda.get_input_alphabet());
		EXPECT_EQ(stack_alphabet, pda.get_stack_alphabet());
		EXPECT_EQ(start_state, pda.get_start_state());
		EXPECT_EQ(start_stack, pda.get_start_stack());
		EXPECT_EQ(0, pda.get_accept_states().size());

	}

	TEST_F(PDATest, PDAContstructorTest2) {
		CFG cfg("XML-Files/LR1-1.xml");
		PDA::PDA pda(&cfg);
		PDA::PDAType type = PDA::acceptByEmptyStack;

		std::vector<char> input_alphabet;
		std::vector<std::string> stack_alphabet;

		std::vector<std::string> terminals = cfg.getTerminals();
		std::vector<std::string> variables = cfg.getVariables();
		std::map<std::string, std::vector<std::string>> rules = cfg.getRules();
		std::string startstring = cfg.getStart();

		for (auto terminal : terminals) {
			input_alphabet.push_back(terminal[0]);
			stack_alphabet.push_back(terminal.substr(0, 1));
		}
		for (auto variable : variables) {
			stack_alphabet.push_back(variable.substr(0, 1));
		}

		std::string start_state = "q";
		std::string start_stack = startstring;

		EXPECT_EQ(pda.get_cfg(), &cfg);
		EXPECT_EQ(input_alphabet, pda.get_input_alphabet());
		EXPECT_EQ(stack_alphabet, pda.get_stack_alphabet());
		EXPECT_EQ(start_state, pda.get_start_state());
		EXPECT_EQ(start_stack, pda.get_start_stack());
		EXPECT_EQ(0, pda.get_accept_states().size());
	}

	TEST_F(PDATest, PDAToEmptyStackAcceptanceTest) {
		CFG cfg("XML-Files/cfg.xml");
		PDA::PDA pda(&cfg);

		EXPECT_EQ(PDA::acceptByEmptyStack, pda.get_type());
		pda.toFinalStateAcceptance();
		EXPECT_FALSE(PDA::acceptByEmptyStack == pda.get_type());
		pda.toEmptyStackAcceptance();
		EXPECT_TRUE(PDA::acceptByEmptyStack == pda.get_type());
	}

	TEST_F(PDATest, PDAToEmptyStackAcceptanceTest2) {
		CFG cfg("XML-Files/LR1-1.xml");
		PDA::PDA pda(&cfg);

		EXPECT_EQ(PDA::acceptByEmptyStack, pda.get_type());
		pda.toFinalStateAcceptance();
		EXPECT_FALSE(PDA::acceptByEmptyStack == pda.get_type());
		pda.toEmptyStackAcceptance();
		EXPECT_TRUE(PDA::acceptByEmptyStack == pda.get_type());
	}

	TEST_F(PDATest, PDAToFinalStateAcceptanceTest) {
		CFG cfg("XML-Files/cfg.xml");
		PDA::PDA pda(&cfg);

		pda.toFinalStateAcceptance();
		EXPECT_EQ(PDA::acceptByFinalState, pda.get_type());
		EXPECT_FALSE(PDA::acceptByEmptyStack == pda.get_type());
		EXPECT_TRUE(PDA::acceptByFinalState == pda.get_type());
		pda.toEmptyStackAcceptance();
		EXPECT_FALSE(PDA::acceptByFinalState == pda.get_type());
	}

	TEST_F(PDATest, PDAToFinalStateAcceptanceTest2) {
		CFG cfg("XML-Files/LR1-1.xml");
		PDA::PDA pda(&cfg);

		pda.toFinalStateAcceptance();
		EXPECT_EQ(PDA::acceptByFinalState, pda.get_type());
		EXPECT_FALSE(PDA::acceptByEmptyStack == pda.get_type());
		EXPECT_TRUE(PDA::acceptByFinalState == pda.get_type());
		pda.toEmptyStackAcceptance();
		EXPECT_FALSE(PDA::acceptByFinalState == pda.get_type());
	}

	TEST_F(PDATest, PDAToLaTeXTest) {
		CFG cfg("XML-Files/cfg.xml");
		PDA::PDA pda(&cfg);

		pda.toLaTeX("./src/tests/output/cfgES.tex");
		pda.toFinalStateAcceptance();
		pda.toLaTeX("./src/tests/output/cfgFS.tex");
		pda.toEmptyStackAcceptance();
		pda.toLaTeX("./src/tests/output/cfgES2.tex");

		EXPECT_TRUE(FileCompare("src/tests/output/cfgES.tex", "src/tests/expected_output/cfgES.tex"));
		EXPECT_TRUE(FileCompare("src/tests/output/cfgFS.tex", "src/tests/expected_output/cfgFS.tex"));
		EXPECT_TRUE(FileCompare("src/tests/output/cfgES2.tex", "src/tests/expected_output/cfgES2.tex"));
	}

	TEST_F(PDATest, PDAToLaTeXTest2) {
		CFG cfg("XML-Files/LR1-1.xml");
		PDA::PDA pda(&cfg);

		pda.toLaTeX("./src/tests/output/LR1-1ES.tex");
		pda.toFinalStateAcceptance();
		pda.toLaTeX("./src/tests/output/LR1-1FS.tex");
		pda.toEmptyStackAcceptance();
		pda.toLaTeX("./src/tests/output/LR1-1ES2.tex");

		EXPECT_TRUE(FileCompare("src/tests/output/LR1-1ES.tex", "src/tests/expected_output/LR1-1ES.tex"));
		EXPECT_TRUE(FileCompare("src/tests/output/LR1-1FS.tex", "src/tests/expected_output/LR1-1FS.tex"));
		EXPECT_TRUE(FileCompare("src/tests/output/LR1-1ES2.tex", "src/tests/expected_output/LR1-1ES2.tex"));
	}

	TEST_F(PDATest, PDAContainsStringTest) {
		CFG cfg("XML-Files/cfg.xml");
		PDA::PDA pda(&cfg);

		for (int i = 0; i < 10; i++) {
			EXPECT_TRUE(pda.containsString("xxy"));
			pda.toFinalStateAcceptance();
			EXPECT_TRUE(pda.containsString("xxy"));
			pda.toEmptyStackAcceptance();
		}
	}

	TEST_F(PDATest, PDAContainsStringTest2) {
		CFG cfg("XML-Files/LR1-1.xml");
		PDA::PDA pda(&cfg);

		for (int i = 0; i < 10; i++) {
			EXPECT_TRUE(pda.containsString("xxxx"));
			pda.toFinalStateAcceptance();
			EXPECT_TRUE(pda.containsString("xxxx"));
			pda.toEmptyStackAcceptance();
		}
	}



}


#endif /* PDA_TEST_H_ */
