/*
 * LRParser.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "LRParser.h"

namespace parser {

LRParser::LRParser()
	: p_table_(),
	  stack_(),
	  counter_(0)
{}

LRParser::LRParser(Grammar::CFG grammar, std::string ptableXML)
	: p_table_(grammar, ptableXML),
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

std::ostream& operator<<(std::ostream& o, LRParser& parser) {
	std::stack<std::string> stackCopy = parser.stack_;
	o << "LRParser stack contents: ";
	if (stackCopy.empty()) {
		o << "empty";
	}
	else {
		 while (!stackCopy.empty()) {
		     o << stackCopy.top() << " ";
		     stackCopy.pop();
		 }
	}
	return o;
}

std::pair<EAction, std::string> LRParser::processSymbol() {
	// Determine our symbol (the counter_'th character of input_)
	std::string symbol;
	if (counter_ != (input_.size())) {
		std::stringstream ss;
		ss << input_.at(counter_);
		symbol = ss.str();
	}
	else {
		symbol = "EOS";
	}

	// Determine our token (this is the top of the stack)
	int token = std::stoi(stack_.top());

	// Get our parsetable entry
	std::pair<EAction, std::string> action = p_table_(token, symbol);

	// Push our symbol to the stack. (as long as it is not a reduction)
	if (action.first != reduction && (symbol != "EOS")) {
		counter_++;
		stack_.push(symbol);
	}
	// Get information from parseTable
	return action;
}

bool LRParser::handleReduction(std::string rule) {
	std::string head = rule.substr(0, 1);
	std::string body = rule.substr(1, rule.size());
	// match stack content and rule body
	std::string::reverse_iterator it;
	for (it = body.rbegin(); it != body.rend(); it++) {
		// Pop token
		std::string top = stack_.top();
		stack_.pop();
		if (utilities::isNumber(top)) {
			// Popped a token, next symbol can not be a token.
			top = stack_.top();
			stack_.pop();
			if (top.at(0) == *it) {
				// All is good, matching stack symbol and rule body character.
				continue;
			}
			else {
				std::cout << "Rule: " << rule << " does not match stack content." << std::endl;
				return false;
			}
		}
	}
	// Top of stack should now be another token. We should check in our parsetable what we should do on input of our head.
	int token = std::stoi(stack_.top());
	// First we push our head on the stack.
	stack_.push(head);
	// Now we need to check what token we need after our head. (Check our parsetable)
	std::pair<EAction, std::string> nextAction = p_table_(token, head);
	// This is a jump (-> push the token on the stack.)
	stack_.push(nextAction.second);
	// Everything did what it had to do. We can return true to let our caller know the reduction operation was successful.
	return true;
}

bool LRParser::performAction(std::pair<EAction, std::string> action) {
	switch (action.first) {
	case shift:
		// push the token on the stack.
		stack_.push(action.second);
		//std::cout << *this << std::endl;
		break;
	case reduction:
		// Replace the body of the production rule by the head.
		handleReduction(action.second);
		break;
	case accept:
		// EMPTY STACK
		//std::cout << *this << std::endl;
		while (!stack_.empty()) {
			stack_.pop();
		}
		return true;
		break;
	case jump:
		// Pretty much the same thing as a shift.
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

	while (input_.length()+1 != counter_) {
		// As long as not all of the input has been consumed.
		// Read the symbol
		std::pair<EAction, std::string> theAction = processSymbol();
		// Perform the action
		bool accept = performAction(theAction);

		// If we ended up in a blank entry or another error our input is invalid.
		if (!accept) {
			return false;
		}
		// If we had the accept action and we have consumed our whole input: our input is valid.
		else if (stack_.empty() && accept && (counter_ == input_.length())) {
			//std::cout << *this << std::endl;
			return true;
		}
	}
	// Our input has been consumed and we do not have a startsymbol: our input is invalid.
	return false;
}


std::stack<std::string> LRParser::getStack() {
	return stack_;
}

unsigned int LRParser::getCounter() {
	return counter_;
}

}
