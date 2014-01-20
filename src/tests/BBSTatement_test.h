/*
* BBSTatement_test.h
*
*  Created on: 20-jan.-2014
*      Author: erkki
*/

#ifndef BBSTATEMENT_TEST_H_
#define BBSTATEMENT_TEST_H_

#include <iostream>

#include "../BareBonesStatement.h"
#include <gtest/gtest.h>


namespace tests {

class BBStatementTest: public testing::Test {
	friend class BB::BBclear;
	friend class BB::BBcopy;
	friend class BB::BBdecr;
	friend class BB::BBincr;
	friend class BB::BBwhile;

protected:
		Grammar::CYKTable cyk;
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
};

TEST_F(BBStatementTest, BBclear) {
	BB::BBclear bbc(5);
	EXPECT_EQ(bbc.variable_, 5);
	EXPECT_EQ(bbc.statementNr_, BB::BareBonesStatement::count_);
}

TEST_F(BBStatementTest, BBcopy) {
	BB::BBcopy bbc(5, 8);
	EXPECT_EQ(bbc.original_, 5);
	EXPECT_EQ(bbc.copy_, 8);
	EXPECT_EQ(bbc.statementNr_, BB::BareBonesStatement::count_);
}
TEST_F(BBStatementTest, BBdecr) {
	BB::BBdecr bbc(5);
	EXPECT_EQ(bbc.variable_, 5);
	EXPECT_EQ(bbc.statementNr_, BB::BareBonesStatement::count_);
}
TEST_F(BBStatementTest, BBincr) {
	BB::BBincr bbc(5);
	EXPECT_EQ(bbc.variable_, 5);
	EXPECT_EQ(bbc.statementNr_, BB::BareBonesStatement::count_);
}
TEST_F(BBStatementTest, BBwhile) {
	std::shared_ptr<BB::BareBonesStatement> bbprt = new BB::BBincr(1);
	std::vector<std::shared_ptr<BB::BareBonesStatement> > body;
	body.push_back(bbprt);
	BB::BBwhile bbc(5, body);
	EXPECT_EQ(bbc.body_, body);
	EXPECT_EQ(bbc.compVar_, 5);
	EXPECT_EQ(bbc.statementNr_, BB::BareBonesStatement::count_);
}


}





#endif /* BBSTATEMENT_TEST_H_ */
