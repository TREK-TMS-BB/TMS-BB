/*
 * TuringMachine.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: robin
 */

#include "TuringMachine.h"

namespace TM {

TuringMachine::TuringMachine() {
	tape_ = Tape (100, (TapeSymbol)'B');	// set the tape_ to size 100 and fill with Blanks
	head_ = tape_.begin();
}

TuringMachine::TuringMachine(std::string filename) {
	// TODO parse the TuringMachine
}

TuringMachine::~TuringMachine() {
	// TODO Auto-generated destructor stub
}

void TuringMachine::simulate(std::vector<TapeSymbol> input) {

	// TODO check input for bad symbols

	if (input.size() > tape_.size()) {
		// Have to make tape_ of appropriate size
		for (int i = tape_.size()-1; i < input.size(); i++) {
			tape_.push_back((TapeSymbol)'B');
		}
	}
	// Put all input on the tape
	for (int i = 0; i< input.size(); i++) {
		tape_.at(i) = input.at(i);
	}

	head_ = tape_.begin();

	// TODO:
	// Write Simulation
}


void TuringMachine::move(Direction dir) {
	switch (dir) {
	case left:
		if (head_ == tape_.begin()) {
			// have to add new item up front
			tape_.insert(tape_.begin(), (TapeSymbol)'B');
			head_=tape_.begin();
		}
		else {
			head_--;
		}
		break;
	case right:
		if (head_ == tape_.end()-1) {
			// have to pushBack new item
			tape_.push_back((TapeSymbol)'B');
			head_= tape_.end()-1;
		}
		else {
			head_++;
		}
		break;
	case none:
		// Stay where you are
		break;
	}
}

std::ostream& operator<< (std::ostream& out, TuringMachine& tm) {

	// print the productions:
	out << "Productions: " << std::endl;
	for (int i = 0; i < tm.productions_.size(); i++) {
		out << std::get<0>(tm.productions_.at(i)) << "\t";			// Current State
		out << (char)std::get<1>(tm.productions_.at(i)) << "\t";	// read symbol
		out << (char)std::get<2>(tm.productions_.at(i)) << "\t";	// write symbol
		Direction dir = std::get<3>(tm.productions_.at(i));			// move head
		switch (dir) {
		case right:
			out << "r";
			break;
		case left:
			out << "l";
			break;
		case none:
			out << "n";
		}
		out << "\t";
		out << std::get<4>(tm.productions_.at(i)) << std::endl;		// nexgt state
	}
	out << std::endl;

	out << "tape:" << std::endl;

	for (int i = 0; i < tm.tape_.size(); i++) {
		out << tm.tape_.at(i) << "  ";
	}
	out << std::endl;
	return out;
}


TapeSymbol TuringMachine::getHead() const {
	return *head_;
}

void TuringMachine::writeHead(TapeSymbol input) {
	*head_ = input;
}
} /* namespace TM */
