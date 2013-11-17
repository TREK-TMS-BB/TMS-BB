/*
 * CFG_test.h
 *
 *      Author: Robin
 */

#ifndef BASICCLASSESTEST_H_
#define BASICCLASSESTEST_H_

#include <iostream>

#include "../CFG.h"
#include <gtest/gtest.h>


namespace tests {

	class CFGTest: public testing::Test {
			friend class CFG;
		protected:
			CFG cfg;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	class CNF_CFGTest: public testing::Test {
		friend class CFG;
	protected:
		CNF_CFG cnf;
		virtual void SetUp() {
		}
		virtual void tearDown() {
		}
	};

	TEST_F(CFGTest, CFG_ConstructorTest) {
		/*
		 * Test all the constructors for CFG
		 */
//Tests with correct input
	// DEFAULT
		std::vector<std::string> var = cfg.getVariables();
		EXPECT_EQ(var.size(), 1);
		EXPECT_EQ(var.at(0), "S");
		std::vector<std::string> term = cfg.getTerminals();
		EXPECT_EQ(term.size(), 0);
		EXPECT_EQ(cfg.getStart(), "S");

	// 	CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s );
		std::map<std::string, std::vector<std::string> > rules;
		std::vector<std::string> temp;
		temp.push_back("a");
		rules["A"] = temp;
		rules["B"].push_back("AA");
		rules["C"].push_back("AB");
		rules["D"].push_back("AA");

		std::vector<std::string> v;
		v.push_back("A");
		v.push_back("B");
		v.push_back("C");
		v.push_back("D");

		std::vector<std::string> ter;
		ter.push_back("a");

		CFG q(v, ter, rules, "C");
		EXPECT_EQ(v, q.getVariables());
		EXPECT_EQ(ter, q.getTerminals());
		EXPECT_EQ(rules, q.getRules());
		EXPECT_EQ("C", q.getStart());

	//	CFG(std::string file);
		CFG grammar("XML-Files/LR1-1.xml");

		rules.clear();
		temp.clear();
		temp.push_back("a");
		rules["S"].push_back("X");
		rules["S"].push_back("Y");
		rules["S"].push_back("");
		rules["X"].push_back("xX");
		rules["X"].push_back("x");
		rules["Y"].push_back("xYy");
		rules["Y"].push_back("xy");

		v.clear();
		v.push_back("S");
		v.push_back("X");
		v.push_back("Y");

		ter.clear();
		ter.push_back("x");
		ter.push_back("y");

		EXPECT_EQ(v, grammar.getVariables());
		EXPECT_EQ(ter, grammar.getTerminals());
		EXPECT_EQ(rules, grammar.getRules());
		EXPECT_EQ("S", grammar.getStart());

	// CFG::CFG(CFG& copy)
		CFG q2(q);
		EXPECT_EQ(q2.getVariables(), q.getVariables());
		EXPECT_EQ(q2.getTerminals(), q.getTerminals());
		EXPECT_EQ(q2.getRules(), q.getRules());
		EXPECT_EQ(q2.getStart(), q.getStart());

// TESTS WITH BAD INPUT
	// 	all tests using file, is the same as with arguments;
		std::string errorMessage;
		// Bad_CFG.xml = file with empty variables
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "VARIABLES SHOULD NOT BE EMPTY");

		// Bad_CFG0.xml = file with empty terminals
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG0.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG0.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "TERMINALS SHOULD NOT BE EMPTY");
		// Bad_CFG1.xml = file with startSymbol that is not found in the variables
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG1.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG1.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "INVALID START SYMBOL");

		// Bad_CFG2.xml = file with non distinct variables and terminals
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG2.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG2.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "TERMINAL X IS ALSO FOUND IN VARIABLES");

		// Bad_CFG3.xml = file with a rule with a terminal on right side of transition
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG3.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG3.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "SYMBOL x NOT FOUND IN VARIABLES VECTOR");

		// Bad_CFG4.xml = file with an invalid symbol on the right side
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG4.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG4.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "SYMBOL Q NOT FOUND IN VARIABLES NOR TERMINALS VECTOR");

		// Bad_CFG5.xml = file with a variable with no corresponding rules
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CFG q("XML-Files/Bad_CFG5.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CFG q("./../XML-Files/Bad_CFG5.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "VARIABLE X HAS NO MATCHING RULE");


	}

	TEST_F(CNF_CFGTest, CNF_CFG_ConstructorTest) {
		/*
		 * Test all the constructors for CNF_CFG
		 */
//Tests with correct input
	// DEFAULT
		std::vector<std::string> var = cnf.getVariables();
		EXPECT_EQ(var.size(), 1);
		EXPECT_EQ(var.at(0), "S");
		std::vector<std::string> term = cnf.getTerminals();
		EXPECT_EQ(term.size(), 0);
		EXPECT_EQ(cnf.getStart(), "S");

	// 	CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s );
		std::map<std::string, std::vector<std::string> > rules;
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AB");
		rules["D"].push_back("AA");

		std::vector<std::string> v;
		v.push_back("A");
		v.push_back("B");
		v.push_back("C");
		v.push_back("D");

		std::vector<std::string> ter;
		ter.push_back("a");

		CNF_CFG q(v, ter, rules, "C");
		EXPECT_EQ(v, q.getVariables());
		EXPECT_EQ(ter, q.getTerminals());
		EXPECT_EQ(rules, q.getRules());
		EXPECT_EQ("C", q.getStart());

	//	CFG(std::string file);
		CNF_CFG grammar("XML-Files/cnf.xml");

		rules.clear();
		rules["S"].push_back("XY");
		rules["X"].push_back("XX");
		rules["X"].push_back("x");
		rules["Y"].push_back("YY");
		rules["Y"].push_back("y");

		v.clear();
		v.push_back("S");
		v.push_back("X");
		v.push_back("Y");

		ter.clear();
		ter.push_back("x");
		ter.push_back("y");

		EXPECT_EQ(v, grammar.getVariables());
		EXPECT_EQ(ter, grammar.getTerminals());
		EXPECT_EQ(rules, grammar.getRules());
		EXPECT_EQ("S", grammar.getStart());

	// CFG::CFG(CFG& copy)
		CNF_CFG q2(q);
		EXPECT_EQ(q2.getVariables(), q.getVariables());
		EXPECT_EQ(q2.getTerminals(), q.getTerminals());
		EXPECT_EQ(q2.getRules(), q.getRules());
		EXPECT_EQ(q2.getStart(), q.getStart());

// TESTS WITH BAD INPUT
	// 	all tests using file, is the same as with arguments, only easier to write;
		std::string errorMessage;
		// Bad_CNF0.xml = file with a rule with only 1 variable
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CNF_CFG q("XML-Files/Bad_CNF0.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CNF_CFG q("./../XML-Files/Bad_CNF0.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "BECAUSE OF RULE: S -> X WHERE X IS NOT A TERMINAL. THIS CFG IS NOT IN CHOMSKY NORMAL FORM");

		// Bad_CNF1.xml = file with a rule with 1 variable and 1 terminal
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CNF_CFG q("XML-Files/Bad_CNF1.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CNF_CFG q("./../XML-Files/Bad_CNF1.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "BECAUSE OF RULE: X -> Xx WHERE xIS NOT A VARIABLE. THIS CFG IS NOT IN CHOMSKY NORMAL FORM");

		// Bad_CNF2 = file with a rule with 1 terminal and 1 variable
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CNF_CFG q("XML-Files/Bad_CNF2.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CNF_CFG q("./../XML-Files/Bad_CNF2.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "BECAUSE OF RULE: X -> xX WHERE x IS NOT A VARIABLE. THIS CFG IS NOT IN CHOMSKY NORMAL FORM");

		// Bad_CNF3.xml = file with a rule with 2 terminals
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CNF_CFG q("XML-Files/Bad_CNF3.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CNF_CFG q("./../XML-Files/Bad_CNF3.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "BECAUSE OF RULE: X -> xx WHERE x AND x ARE NO VARIABLES. THIS CFG IS NOT IN CHOMSKY NORMAL FORM");

		// Bad_CNF4.xml = file with a rule with more than 2 variables on the right side
		try
		{
			if (DirectoryExists("XML-Files"))
			{
				CNF_CFG q("XML-Files/Bad_CNF4.xml");
			}
			else if (DirectoryExists("./../XML-Files"))
			{
				CNF_CFG q("./../XML-Files/Bad_CNF4.xml");
			}
		}
		catch (Exception &e)
		{
			errorMessage = e.what();
		}
		EXPECT_EQ(errorMessage, "BECAUSE OF RULE: S -> XYXY WHERE SIZE OF RIGHT SIZE > 2. THIS CFG IS NOT IN CHOMSKY NORMAL FORM");
	}

	TEST_F(CFGTest, CFG_OutputTest) {
		std::ofstream testFile;
		testFile.open("testOutput/CFG_output.txt");
		CFG g("XML-Files/LR1-1.xml");
		testFile << g;
		testFile.close();
		EXPECT_TRUE(FileCompare("testOutput/CFG_output.txt", "testOutput/CFG_outputComp.txt"));
	}

	TEST_F(CNF_CFGTest, CNF_CFG_check_stringTest) {

		CNF_CFG c("XML-Files/cnf.xml");
		bool check = c.check_string("xxyy");
		EXPECT_TRUE(check);
		check = c.check_string("xxxyy");
		EXPECT_TRUE(check);
		check = c.check_string("xyx");
		EXPECT_FALSE(check);
	}
}



#endif /* BASICCLASSESTEST_H_ */
