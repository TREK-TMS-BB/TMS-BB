/*
 * LRParser.h
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#ifndef LRPARSER_H_
#define LRPARSER_H_

#include <stack>
#include <string>

#include "CFG.h"
#include "ParseTable.h"
#include "Parser.h"

class LRParser : public Parser{
public:
	LRParser();
	// Default constructor for LRParser. This won't be able to do anything as it has no parse table.

	LRParser(CFG);
	// The CFG defines the CFL. The parse table will be generated from this grammar.

	LRParser(ParseTable);
	// The parameter ParseTable will be directly used.

	virtual ~LRParser();

private:
	ParseTable p_table;
	std::stack<std::string> stack;
};

#endif /* LRPARSER_H_ */
