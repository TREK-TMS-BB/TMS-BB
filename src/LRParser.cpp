/*
 * LRParser.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "LRParser.h"

LRParser::LRParser()
	: p_table_(),
	  stack_(),
	  counter_(0)
{}

LRParser::LRParser(CFG grammar)
	: p_table_(grammar),
	 stack_(),
	 counter_(0)
{}

LRParser::LRParser(ParseTable pt)
	: p_table_(pt),
	  stack_(),
	  counter_(0)
{}

LRParser::~LRParser() {
	// TODO Auto-generated destructor stub
}

std::pair<EAction, std::string> LRParser::processSymbol() {
	// Determine our symbol (the counter_'th character of input_)
	std::stringstream ss;
	ss << input_.at(counter_);
	std::string symbol = ss.str();

	// Determine our token (this is the top of the stack)
	int token = std::stoi(stack_.top());

	// Push our symbol to the stack.
	stack_.push(symbol);
	// Get information from parseTable
	return p_table_(token, symbol);
}

bool LRParser::handleReduction(std::string rule) {
	std::string head = rule.substr(0, 1);
	std::string body = rule.substr(1, rule.size());
	std::cout << "Applying production rule -> head = " << head << " | body = " << body << std::endl;

	// match stack content and rule body
	std::string::reverse_iterator it;
	for (it = body.rbegin(); it != body.rend(); it++) {
		std::string top = stack_.top();
		stack_.pop();
		std::cout << top << " == TOP 1" << std::endl;
		if (utilities::isNumber(top)) {
			// Popped a token, next symbol can not be a token.
			top = stack_.top();
			std::cout << top << " == TOP 2 | compare with " << *it << std::endl;
			stack_.pop();
			if (top.at(0) == *it) {
				// All is good, matching stack symbol and rule body character.
				continue;
			}
			else {
				std::cout << "This won't work. Rule does not match stack content." << std::endl;
				return false;
			}
		}
	}

	// Top of stack should now be another token. We should check in our parsetable what we should do on input of our head.
	int token = std::stoi(stack_.top());
	// First we push our head on the stack.
	stack_.push(head);
	// Now we need to check what token we need after our head. (Check our parsetable)
	std::pair<EAction, std::string> jump = p_table_(token, head);
	// This is a jump (-> push the token on the stack.)
	stack_.push(jump.second);

	// Everything did what it had to do. We can return true to let our caller know the reduction operation was successful.
	return true;
}

bool LRParser::performAction(std::pair<EAction, std::string> action) {
	switch (action.first) {
	case shift:
		// push the token on the stack.
		stack_.push(action.second);
		break;
	case reduction:
		// Replace the body of the production rule by the head.
		handleReduction(action.second);
		break;
	case accept:
		return true;
		break;
	case jump:
		stack_.push(action.second);
		break;
	case error:
		return false;
		break;
	case blank:
		return false;
		break;
	default:
		return false;
		break;
	}
	// Error, did not enter switch.
	return true;
}

bool LRParser::parse(std::string input) {
	input_ = input;
	counter_ = 0;

	// Push state 1
	stack_.push("1");

	while (input_.length() != counter_) {
		// As long as not all of the input has been consumed.
		// Read the symbol
		std::pair<EAction, std::string> theAction = processSymbol();
		// Perform the action
		bool accept = performAction(theAction);

		counter_++;

		if (accept && (counter_ == input_.length())) {
			// If we have our startsymbol and we have consumed our whole input: our input is valid.
			return true;
		}
	}

	// Our input has been consumed and we do not have a startsymbol: our input is invalid.
	return false;
}

