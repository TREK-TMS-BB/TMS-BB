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
#include <utility>
#include <sstream>
#include <iostream>
#include "utilities.h"
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

	bool parse(std::string);
	// Parses the given input string and returns true if it is valid, false if it is invalid.

	friend std::ostream& operator<<(std::ostream&, LRParser&);
	// Overloaded output operator: shows the stack contents;

	virtual ~LRParser();

private:
	ParseTable p_table_;
	std::stack<std::string> stack_;
	std::string input_;
	unsigned int counter_;

	std::pair<EAction, std::string> processSymbol();
	// Reads a symbol from the input and returns what to do. (from parsetable)
	// Also pushes the read symbol on the stack.

	bool performAction(std::pair<EAction, std::string>);
	// Performs action. If this evaluates to true the function it means that input_ was valid.

	bool handleReduction(std::string);
	// Handles the reduction action.

};

#endif /* LRPARSER_H_ */
