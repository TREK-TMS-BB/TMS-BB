/*
 * BBProgram_test.h
 *
 *  Created on: 18-jan.-2014
 *      Author: erkki
 */

#ifndef BBPROGRAM_TEST_H_
#define BBPROGRAM_TEST_H_

#include <iostream>

#include "../BareBonesProgram.h"
#include <gtest/gtest.h>


namespace tests {

class BBProgramTest: public testing::Test {
	friend class BB::BareBonesProgram;
protected:
		Grammar::CYKTable cyk;
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
};

TEST_F(BBProgramTest, BareBonesProgramConstructor) {
	std::shared_ptr <BB::BareBonesStatement> bbptr = BB::BBclear(0);
	std::vector <std::shared_ptr<BB::BareBonesStatement> > body;
	body.push_back(bbptr);
	BB::BareBonesProgram bbp(body, body.size());
	EXPECT_EQ(bbp.used_variables_, body.size());;
	EXPECT_EQ(bbp.statements_, body);
}




#endif /* BBPROGRAM_TEST_H_ */
