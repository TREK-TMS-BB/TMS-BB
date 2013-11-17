
#ifndef BASICCLASSESTEST_H_
#define BASICCLASSESTEST_H_

#include <iostream>

#include "../CYKTable.h"
#include <gtest/gtest.h>


namespace tests {

	class CYKTableTest: public testing::Test {
			friend class CYKTable;
		protected:
			CYKTable cyk;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	TEST_F(CYKTableTest, CYK_ConstructorTest) {
		//CYKTable()
		EXPECT_TRUE(cyk.startSymbol_ == "S");
		EXPECT_TRUE(cyk.rules_.size() == 0);
		EXPECT_TRUE(cyk.variables_.size() == 0);

		//CYKTable(std::map<std::string, std::vector<std::string> > &r, std::string startSymbol);
		std::map<std::string, std::vector<std::string> > rules;
		std::string start = "S";

		std::map<std::string, std::vector<std::string> > rules;
		std::vector<std::string> temp;
		temp.push_back("a");
		rules["S"].push_back("BC");
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AB");
		rules["D"].push_back("AA");


		CYKTable c(rules, start);
		EXPECT_EQ(rules, c.rules_);
		EXPECT_EQ(start, c.startSymbol_);

	}
}



#endif /* BASICCLASSESTEST_H_ */
