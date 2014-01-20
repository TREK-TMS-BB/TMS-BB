/*
 * TMProgram_test.h
 *
 *  Created on: 20-jan.-2014
 *      Author: erkki
 */

#ifndef TMPROGRAM_TEST_H_
#define TMPROGRAM_TEST_H_

#include "../TMProgram.h"

#include <gtest/gtest.h>
#include <sstream>

namespace tests {
class TMProgramTest: public testing::Test {
	friend class TM::TMProgram;
protected:
	virtual void SetUp() {
	}
	virtual void TearDown() {
	}
};

TEST_F(TMProgramTest, TMP_constructortest) {
	//Default constructor
	TM::TMProgram tmp;
	EXPECT_EQ(tmp.getStart(), "Start" );
	//Constuct from a given file.
	TM::TMProgram tmp2("./TM-Files/example2.tm");
	parser::TMParser tmpar("./TM-Files/example2.tm");
	EXPECT_EQ(tmp2.input_, tmpar.getInitInput());
	EXPECT_EQ(tmp2.productions_, tmpar.getProductions());
	EXPECT_EQ(tmp2.states_, tmpar.getStates());
	//Contruct with vector
	std::vector<TM::StateName> states = tmpar.getStates();
	std::vector<TM::Production> productions= tmpar.getProductions();
	std::string filename = "./TM-Files/example2.tm";
	TM::TMProgram tmp3(states, productions, filename);
	tmp3.setInput(tmpar.getInitInput());
	EXPECT_EQ(tmp3.input_, tmpar.getInitInput());
	EXPECT_EQ(tmp3.productions_, tmpar.getProductions());
	EXPECT_EQ(tmp3.states_, tmpar.getStates());
}





}//End namespace tests





#endif /* TMPROGRAM_TEST_H_ */
