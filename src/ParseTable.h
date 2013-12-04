/*
 * ParseTable.h
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#ifndef PARSETABLE_H_
#define PARSETABLE_H_

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <cctype>
#include <sstream>
#include "Information.h"

#include "CFG.h"
#include "PTableParser.h"

namespace parser {


class ParseTable {
public:
	//! Default constructor. Our ParseTable will be empty as it has no CFG.
	ParseTable();

	//! Our ParseTable will be constructed using the CFG provided as parameter.
	/**
	 * @param grammar The grammar which the ParseTable will be based on.
	 * @param ptableXML The filename where our parsetable info can be found.
	 */
	ParseTable(Grammar::CFG, std::string);

	//! Returns the contents of the parse table (and what action should happen) depending on the input.
	/**
	 * @param token ParseTable row
	 * @param symbol ParseTable column
	 * @return Pair of an action (EAction) and possible information needed to complete the action (string)
	 */
	std::pair<EAction, std::string> operator() (int, std::string) const;

	virtual ~ParseTable();

private:
	//! The actual parse table
	std::vector<std::vector<std::string> > table;

	//! Maps column index and input string. This is a private method used to quickly find what column index you have to look in.
	std::map<std::string, int> lookup;

	//! Extracts info from input.
	/**
	 * @param entry A table entry
	 * @return A pair of what needs to be done (EAction) and a string with info needed to perform the action.
	 */
	std::pair<EAction, std::string> extractInfo(std::string) const;
};

}

#endif /* PARSETABLE_H_ */
