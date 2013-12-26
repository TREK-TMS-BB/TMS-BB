/*
 * TMParser.h
 *
 *  Created on: Nov 24, 2013
 *      Author: kristof
 */

#ifndef TMPARSER_H_
#define TMPARSER_H_

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "Exception.h"
#include "TapeSymbol.h"
#include "Information.h"
#include "utilities.h"
#include "TapeSymbol.h"

namespace parser {

class TMParser {
public:
	//! Main constructor for TMParser. This will parse the parameter file and save the info in its members.
	/**
	 * @param file The file that needs to be parsed.
	 */
	TMParser(std::string);

	virtual ~TMParser();

	/**
	 * @return initial input for the TuringMachine.
	 */
	std::vector<TM::TapeSymbol> getInitInput() const;

	/**
	 * @return all states for the TuringMachine.
	 */
	std::vector<TM::StateName> getStates() const;

	/**
	 * @return all productions for the TuringMachine.
	 */
	std::vector<TM::Production> getProductions() const;

	friend std::ostream& operator<<(std::ostream& out, TMParser& tmp);

private:
	//! Initial input for the Turing Machine.
	std::vector<TM::TapeSymbol> initInput_;

	//! All states for the Turing Machine.
	std::vector<TM::StateName> states_;

	//! All productions for the Turing Machine.
	std::vector<TM::Production> productions_;

	/**
	 * @param line The string that contains the states.
	 * @param found The index where the string "STATES = {" begins.
	 */
	void parseStates(std::string, std::size_t);

	/**
	 * @param line The string that contains the initial input.
	 * @param found The index where the string "INITIAL_INPUT = " begins.
	 */
	void parseInitInput(std::string, std::size_t);

	/**
	 * @param line The string that contains a production.
	 */
	void parseProduction(std::string);

	/**
	 * @param it2& The iterator we need to use in our check.
	 * @param c The char the iterator needs to pass.
	 */
	void iteratorCheck(std::string::iterator&, char) const;
};

} /* namespace parser */

#endif /* TMPARSER_H_ */
