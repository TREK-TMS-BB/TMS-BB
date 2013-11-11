/*
 * LRParser.h
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#ifndef LRPARSER_H_
#define LRPARSER_H_

#include <stack>

#include "CFG.h"
#include "ParseTable.h"

class LRParser {
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
	//std::stack stack;
};

#endif /* LRPARSER_H_ */