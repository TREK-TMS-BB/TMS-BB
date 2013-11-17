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

	TEST_F(CFGTest, ConstructorTest) {
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
}

#endif /* BASICCLASSESTEST_H_ */
