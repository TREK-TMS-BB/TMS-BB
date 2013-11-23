/*
 * ParseTable_test.h
 *
 *  Created on: Nov 20, 2013
 *      Author: kristof
 */

#ifndef PARSETABLE_TEST_H_
#define PARSETABLE_TEST_H_

#include "../ParseTable.h"
#include <gtest/gtest.h>
#include <iostream>

using parser::ParseTable;

namespace tests {

	class ParseTableTest: public testing::Test {
			friend class ParseTable;
		protected:
			ParseTable pt;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	TEST_F(ParseTableTest, ParseTable_functor_test) {
		::testing::FLAGS_gtest_death_test_style = "threadsafe";

		// Test whether it extracts info correctly.
		Grammar::CFG cfg("XML-Files/LR1-1.xml");
		ParseTable pt(cfg);
		std::pair<parser::EAction, std::string> output;

		output = pt(3, "x");
		EXPECT_TRUE(output.first == parser::blank);
		EXPECT_TRUE(output.second == "blank");

		output = pt(9, "EOS");
		EXPECT_TRUE(output.first == parser::accept);
		EXPECT_TRUE(output.second == "accept");

		output = pt(2, "X");
		EXPECT_TRUE(output.first == parser::jump);
		EXPECT_TRUE(output.second == "3");

		output = pt(2, "x");
		EXPECT_TRUE(output.first == parser::shift);
		EXPECT_TRUE(output.second == "2");

		output = pt(3, "EOS");
		EXPECT_TRUE(output.first == parser::reduction);
		EXPECT_TRUE(output.second == "XxX");

		// Some wrong input
		ASSERT_DEATH(pt(15, "droog"), "");
	}
}



#endif /* PARSETABLE_TEST_H_ */
