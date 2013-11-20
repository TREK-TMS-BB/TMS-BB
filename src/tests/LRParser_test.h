/*
 * LRParser.h
 *
 *  Created on: Nov 20, 2013
 *      Author: kristof
 */

#ifndef LRPARSER_TEST_H_
#define LRPARSER_TEST_H_

#include "../LRParser.h"
#include "../CFG.h"
#include <gtest/gtest.h>

namespace tests {

	class LRParserTest: public testing::Test {
			friend class LRParser;
		protected:
			LRParser lrp;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	TEST_F(LRParserTest, LRParser_ConstructorTest) {
		//LRParser()
		//LRParser l();
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(CFG)
		CFG c("XML-Files/LR1-1.xml");
		LRParser t(c);
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(ParseTable)
		ParseTable p(c);
		LRParser d(p);
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);
	}

	TEST_F(LRParserTest, LRParser_test) {
		::testing::FLAGS_gtest_death_test_style = "threadsafe";

		// Set up correct LRParser
		CFG c("XML-Files/LR1-1.xml");
		LRParser t(c);

		// Test correct input
		bool accepted = t.parse("xxxxxx");
		EXPECT_TRUE(accepted);
		accepted = t.parse("xYy");
		EXPECT_TRUE(accepted);
		accepted = t.parse("xxxxYyyyy");
		EXPECT_TRUE(accepted);

		// Test wrong input
		accepted = t.parse("xxxxxxYy");
		EXPECT_FALSE(accepted);
		accepted = t.parse("xyxyxyxyxyxyx");
		EXPECT_FALSE(accepted);
		accepted = t.parse("yyyxxx");
		EXPECT_FALSE(accepted);

		 //Test bad input
		accepted = t.parse("xyyxxxy");
		EXPECT_FALSE(accepted);
		accepted = t.parse("YYx");
		EXPECT_FALSE(accepted);
		ASSERT_DEATH(t.parse("1234"), "");
		ASSERT_DEATH(t.parse("abz"), "");
		ASSERT_DEATH(t.parse("xYyz"), "");
	}
}



#endif /* LRPARSER_TEST_H_ */
