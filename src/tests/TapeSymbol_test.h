/*
 * TapeSymbol_test.h
 *
 *  Created on: 18-jan.-2014
 *      Author: erkki
 */

#ifndef TAPESYMBOL_TEST_H_
#define TAPESYMBOL_TEST_H_

#include "../TapeSymbol.h"
#include <gtest/gtest.h>
#include <sstream>

namespace tests {
class TapeSymbolTest: public testing::Test {
			friend class TM::TapeSymbol;
		protected:
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

TEST_F(TapeSymbolTest, TS_constructortest) {
		//	TapeSymbol()
		TM::TapeSymbol tps;
		EXPECT_TRUE(tps.isBlank());
		std::stringstream symbol;
		symbol << tps;
		EXPECT_EQ(symbol.str(), "_");

		//TapeSymbol(unsigned int i );
		TM::TapeSymbol tps2(5);
		EXPECT_TRUE(!tps2.isBlank());
		std::stringstream symbol2;
		symbol2 << tps2;
		EXPECT_EQ(symbol2.str(), 5);

		//TapeSymbol(std::string c);
		TM::TapeSymbol tpsc("A");
		EXPECT_TRUE(!tpsc.isBlank());
		std::stringstream symbol3;
		symbol3 << tpsc;
		EXPECT_EQ(symbol3.str(), "A");
	}

	TEST_F(TapeSymbolTest, MethodTest) {
		TM::TapeSymbol Tps(5);
		TM::TapeSymbol tps2("A");
		TM::TapeSymbol tps3;
		TM::TapeSymbol tps4("B");
		TM::TapeSymbol tps5(8);
		TM::TapeSymbol tps6;
		//Different types
		EXPECT_FALSE(Tps == tps2);
		EXPECT_FALSE(Tps == tps3);
		EXPECT_FALSE(tps2 == tps3);
		//Different values
		EXPECT_FALSE(tps2 == tps4);
		EXPECT_FALSE(Tps == tps5);
		EXPECT_TRUE(tps3 == tps6);


	}



}//End namespace tests

#endif /* TAPESYMBOL_TEST_H_ */
