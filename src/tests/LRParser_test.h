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

//using parser::LRParser;

namespace tests {

	class LRParserTest: public testing::Test {
			friend class LRParser;
		protected:
			parser::LRParser lrp;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	TEST_F(LRParserTest, LRParser_ConstructorTest) {
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(CFG)
		Grammar::CFG c("XML-Files/LR1-1.xml");
		parser::LRParser t(c, "XML-Files/LR1-1-ptable.xml");
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(ParseTable)
		parser::ParseTable p(c, "XML-Files/LR1-1-ptable.xml");
		parser::LRParser d(p);
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(CFG)
		Grammar::CFG f("XML-Files/LR1-2.xml");
		parser::LRParser g(f, "XML-Files/LR1-2-ptable.xml");
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);

		//LRParser(ParseTable)
		parser::ParseTable h(f, "XML-Files/LR1-2-ptable.xml");
		parser::LRParser i(h);
		EXPECT_TRUE(lrp.getCounter() == 0);
		EXPECT_TRUE(lrp.getStack().size() == 0);


	}

	TEST_F(LRParserTest, LRParser_test) {
		::testing::FLAGS_gtest_death_test_style = "threadsafe";

		// Set up correct LRParser
		Grammar::CFG c("XML-Files/LR1-1.xml");
		parser::LRParser t(c, "XML-Files/LR1-1-ptable.xml");

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

		// Set up correct LRParser
		Grammar::CFG c2("XML-Files/LR1-2.xml");
		parser::LRParser t2(c2, "XML-Files/LR1-2-ptable.xml");

		// Test correct input
		accepted = t2.parse("zzzz");
		EXPECT_TRUE(accepted);
		accepted = t2.parse("zazabzbz");
		EXPECT_TRUE(accepted);
		accepted = t2.parse("zazazz");
		EXPECT_TRUE(accepted);

		// Test wrong input
		accepted = t2.parse("zz");
		EXPECT_FALSE(accepted);
		accepted = t2.parse("zzbzzzb");
		EXPECT_FALSE(accepted);
		accepted = t2.parse("zbzzbzbzbzbzzza");
		EXPECT_FALSE(accepted);

		 //Test bad input
		accepted = t2.parse("zzbzzzM");
		EXPECT_FALSE(accepted);
		accepted = t2.parse("zzaaaaaaaaaaaabz");
		EXPECT_FALSE(accepted);
		ASSERT_DEATH(t2.parse("1234"), "");
		ASSERT_DEATH(t2.parse("rabrzr"), "");
		ASSERT_DEATH(t2.parse("xYyz"), "");
	}
}



#endif /* LRPARSER_TEST_H_ */
