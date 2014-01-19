/*
 * TMParser_test.h
 *
 *  Created on: 19-jan.-2014
 *      Author: erkki
 */

#ifndef TMPARSER_TEST_H_
#define TMPARSER_TEST_H_

#include "../TMParser.h"

#include <gtest/gtest.h>
#include <sstream>

namespace tests {
class TMparserTest: public testing::Test {
			friend class parser::TMParser;
		protected:
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

TEST_F(TMparserTest, TMP_constructortest) {
		parser::TMParser tmp("./TM-Files/example2.tm");
		std::vector<TM::TapeSymbol> symbols;
		symbols.push_back(TM::TapeSymbol(0));
		symbols.push_back(TM::TapeSymbol(0));
		symbols.push_back(TM::TapeSymbol(0));
		symbols.push_back(TM::TapeSymbol(0));
		symbols.push_back(TM::TapeSymbol(1));
		symbols.push_back(TM::TapeSymbol(1));
		symbols.push_back(TM::TapeSymbol(0));
		symbols.push_back(TM::TapeSymbol(0));
		EXPECT_EQ(tmp.initInput_, symbols);
		std::vector<TM::StateName> states;
		states.push_back("0");
		states.push_back("1");
		states.push_back("halt");
		EXPECT_EQ(tmp.states_, states);
		std::vector<TM::Production> productions;
		TM::TapeSymbol B;
		TM::TapeSymbol Z(0);
		TM::TapeSymbol One(1);
		TM::Production prod ("0", B, B, TM::Direction::left, "1");
		TM::Production prod2 ("0", Z, One, TM::Direction::right, "0");
		TM::Production prod3 ("0", One, Z, TM::Direction::right, "0");
		TM::Production prod4 ("1", B, B, TM::Direction::right, "halt");
		productions.push_back(prod);
		productions.push_back(prod2);
		productions.push_back(prod3);
		productions.push_back(prod4);
		EXPECT_EQ(tmp.productions_, productions);

}

TEST_F(TMparserTest, MethodTest) {
	parser::TMParser tmp("./TM-Files/example2.tm");
	EXPECT_EQ(tmp.getInitInput(), tmp.initInput_);
	EXPECT_EQ(tmp.getProductions(), tmp.productions_);
	EXPECT_EQ(tmp.getStates(), tmp.states_);
}



}//End namespace tests





#endif /* TMPARSER_TEST_H_ */
