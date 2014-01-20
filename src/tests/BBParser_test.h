/*
 * BBParser_test.h
 *
 *  Created on: 20-jan.-2014
 *      Author: erkki
 */

#ifndef BBPARSER_TEST_H_
#define BBPARSER_TEST_H_

#include "../BareBonesProgram.h"
#include <gtest/gtest.h>


namespace tests {

class BBParserTest: public testing::Test {
	friend class parser::BBParser;
protected:
		Grammar::CYKTable cyk;
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
};

TEST_F(BBParserTest, BareBonesParserConstructor) {
	parser::BBParser bbp;
	BB::BareBonesProgram bbprog = bbp.parseBB("./BB-Files/test.bb");
	EXPECT_EQ(bbp.statements_, bbprog.statements_);

}




#endif /* BBPARSER_TEST_H_ */
