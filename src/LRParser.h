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

namespace parser {

class LRParser : public Parser{
public:
	//! Default constructor for LRParser. This won't be able to do anything as it has no parse table.
	LRParser();

	//! The CFG defines the CFL. The parse table will be generated from this grammar.
	/**
	 * @param grammar grammar for our LRParser.
	 */
	LRParser(CFG);

	//! The parameter ParseTable will be directly used.
	/**
	 * @param pt ParseTable for our LRParser.
	 */
	LRParser(ParseTable);

	//! Parses the given input string and returns true if it is valid, false if it is invalid.
	/**
	 * @param input input string that will be tested.
	 */
	bool parse(std::string);

	//! Overloaded output operator: shows the stack contents;
	friend std::ostream& operator<<(std::ostream&, LRParser&);

	std::stack<std::string> getStack();

	unsigned int getCounter();

	virtual ~LRParser();

protected:
	ParseTable p_table_;
	std::stack<std::string> stack_;
	std::string input_;
	unsigned int counter_; //! Counter used to track at what character of our input we're at.

	/**
	 * 	Reads a symbol from the input and returns what to do. (from parsetable)
	 * 	Also pushes the read symbol on the stack.
	 * 	@return a pair of what to do (EAction) and possible data needed for the action (string).
	 */
	std::pair<EAction, std::string> processSymbol();

	//! Performs action. If this evaluates to true the function it means that input_ was valid.
	/**
	 * @param action which will be executed.
	 */
	bool performAction(std::pair<EAction, std::string>);

	//! Handles the reduction action.
	/**
	 * @param input is a rule that will be applied from body to head.
	 */
	bool handleReduction(std::string);


};

}

#endif /* LRPARSER_H_ */
