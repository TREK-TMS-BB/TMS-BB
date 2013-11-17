
#ifndef CYKTEST_H_
#define CYKTEST_H_

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
		EXPECT_TRUE(cyk.getStartSymbol() == "S");
		EXPECT_TRUE(cyk.getRules().size() == 0);

		//CYKTable(std::map<std::string, std::vector<std::string> > &r, std::string startSymbol);
		std::map<std::string, std::vector<std::string> > rules;
		std::string start = "S";

		rules["S"].push_back("BC");
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AA");


		CYKTable c(rules, start);
		EXPECT_EQ(rules, c.getRules());
		EXPECT_EQ(start, c.getStartSymbol());

		//CYKTable(std::string w, std::map<std::string, std::vector<std::string> > &r, std::string stS);
		CYKTable t("aaaa", rules, start);
		EXPECT_EQ(rules, t.getRules());
		EXPECT_EQ(start, t.getStartSymbol());
		EXPECT_EQ(4, t.getTable().size());
		std::vector<std::string> temp = t.at(1,4);
		bool check = false;
		for (std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); it++)
		{
			std::string s = *it;
			std::cout << s << "S" << std::endl;
			if (s == "S")
			{
				check = true;
				break;
			}
		}
		EXPECT_TRUE(check);
	}

	TEST_F(CYKTableTest, operatorTest) {
		std::map<std::string, std::vector<std::string> > rules;
		std::string start = "S";

		rules["S"].push_back("BC");
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AA");


		CYKTable c(rules, start);

		bool check = c("aaaa");
		EXPECT_TRUE(check);
		check = c("aaaaa");
		EXPECT_FALSE(check);
	}

	TEST_F(CYKTableTest, atTest) {
		std::map<std::string, std::vector<std::string> > rules;
		std::string start = "S";

		rules["S"].push_back("BC");
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AA");

		CYKTable c(rules, start);

		c("aaaa");

		std::vector<std::string> temp = c.at(1,4);
		EXPECT_TRUE(temp.size() == 1);
		temp = c.at(1,3);
		EXPECT_TRUE(temp.size() == 0);
		temp = c.at(1, 2);
		EXPECT_TRUE(temp.size() == 2);
	}

	TEST_F(CYKTableTest, outputOperatorTest) {

		std::map<std::string, std::vector<std::string> > rules;
		std::string start = "S";

		rules["S"].push_back("BC");
		rules["A"].push_back("a");
		rules["B"].push_back("AA");
		rules["C"].push_back("AA");

		CYKTable c(rules, start);

		c("aaaa");

		std::ofstream testFile;
		testFile.open("testOutput/CYK_output.txt");

		testFile << c;
		testFile.close();
		EXPECT_TRUE(FileCompare("testOutput/CYK_output.txt", "testOutput/CYK_output.txt"));
	}
}



#endif /* CYKTEST_H_ */
