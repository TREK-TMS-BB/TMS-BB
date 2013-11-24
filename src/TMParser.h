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
#include "Exception.h"
#include "TuringMachine.h"

namespace parser {

class TMParser {
public:
	//! Main constructor for TMParser. This will parse the parameter file and save the info in its members.
	/**
	 * @param file The file that needs to be parsed.
	 */
	TMParser(std::string);

	virtual ~TMParser();

	std::string getInitInput() const;

	std::vector<TM::StateName> getStates() const;

	std::vector<TM::Production> getProductions() const;

	friend std::ostream& operator<<(std::ostream& out, TMParser& tmp);

private:
	std::string initInput_;

	std::vector<TM::StateName> states_;

	std::vector<TM::Production> productions_;

	void parseStates(std::string, std::size_t);

	void parseInitInput(std::string, std::size_t);

	void parseProduction(std::string);

	void iteratorCheck(std::string::iterator&, char) const;
};

} /* namespace parser */

#endif /* TMPARSER_H_ */
