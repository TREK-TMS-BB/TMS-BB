/*
 * TM_test.h
 *
 *  Created on: 20-jan.-2014
 *      Author: erkki
 */


#ifndef TM_TEST_H_
#define TM_TEST_H_

#include "../TuringMachine.h"
#include <gtest/gtest.h>
#include <sstream>

namespace tests {
class TMTest: public testing::Test {
			friend class TM::TuringMachine;
		protected:
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

TEST_F(TMTest, TM_constructortest) {
	//	TuringMachine()
	TM::TuringMachine tm;
	TM::Tape tape = TM::Tape (100, TM::TapeSymbol());	// set the tape_ to size 100 and fill with Blanks
	TM::Tape::iterator head = tape.begin();
	TM::StateName curState = "halt";
	EXPECT_EQ(tm.tape_, tape);
	EXPECT_EQ(tm.curState_, curState);
	//TuringMachine(filename)
	TM::TuringMachine tm2("./TM-Files/example2.tm");
	parser::TMParser tmpar("./TM-Files/example2.tm");
	EXPECT_EQ(tm2.tape_, tape);
	EXPECT_EQ(tm2.productions_, tmpar.productions_);
	EXPECT_EQ(tm2.curState_, tmpar.states_.at(0));
}


}//End namespace tests

#endif /* TM_TEST_H_ */


