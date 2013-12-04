/*
 * TuringMachine.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: robin
 */

#include "TuringMachine.h"

namespace TM {

TuringMachine::TuringMachine() {
	tape_ = Tape (100, TapeSymbol());	// set the tape_ to size 100 and fill with Blanks
	head_ = tape_.begin();
	curState_ = "halt";
}

TuringMachine::TuringMachine(std::string filename) {
	parser::TMParser tmp(filename) ;
	for (int i = 0; i < tmp.getStates().size();i++) {
		states_.push_back(tmp.getStates().at(i));
	}
	states_.push_back("Error");
	for (int i = 0; i < tmp.getProductions().size();i++) {
		productions_.push_back(tmp.getProductions().at(i));
	}
	tape_ = Tape(100, TapeSymbol());
	head_ = tape_.begin();
	curState_ = states_.at(0);
}

TuringMachine::~TuringMachine() {
	// TODO Auto-generated destructor stub
}

void TuringMachine::simulate(std::vector<TapeSymbol> input) {


	// TODO check input for bad symbols
	resetTape();
	curState_ = states_.at(0);
	head_ = tape_.begin();
	int temp = input.size();

	if (input.size() > tape_.size()) {
		// Have to make tape_ of appropriate size
		for (unsigned int i = tape_.size()-1; i < input.size(); i++) {
			tape_.push_back(TapeSymbol());
		}
	}
	// Put all input on the tape
	for (int i = 0; i< temp; i++) {
		tape_.at(i) = input.at(i);
	}

	head_ = tape_.begin();

	while (true) {
		this->simulateCycle();
		if (curState_ == "halt") {
			break;
		}
		else if (curState_ == "error") {
			std::string error = "SIMULATION CAME IN ERROR STATE, SIMULATION STOPPED: IN STATE " + curState_;
			throw(Exception(error));
		}
	}

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
	for (unsigned int i = 0; i < tm.productions_.size(); i++) {
		out << std::get<0>(tm.productions_.at(i)) << "\t";			// Current State
		out << std::get<1>(tm.productions_.at(i)) << "\t";	// read symbol
		out << std::get<2>(tm.productions_.at(i)) << "\t";	// write symbol
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

	for (unsigned int i = 0; i < tm.tape_.size(); i++) {
		out << tm.tape_.at(i) << "  ";
	}
	out << std::endl;
	return out;
}

std::vector<TapeSymbol> TuringMachine::getOutput() const {

	int placeNonBlank = -1; // the place of the 1st nonBlank
	int placeBlank = -1; // The place where the first blank of the remaining blanks stands

	for (int i = 0; i < tape_.size(); i++) {
		if ((placeBlank == -1) && (tape_.at(i).isBlank())) {
			placeBlank = i;
		}
		else if (!tape_.at(i).isBlank()) {
			placeBlank = -1;
			if (placeNonBlank == -1) {
				placeNonBlank = i;
			}
		}
	}
	std::vector<TapeSymbol> ret;

	for (int j = placeNonBlank; j < placeBlank; j++) {
		ret.push_back(tape_.at(j));
	}

	return ret;
}


TapeSymbol TuringMachine::getHead() const {
	return *head_;
}

void TuringMachine::writeHead(TapeSymbol input) {
	*head_ = input;
}

void TuringMachine::simulateCycle() {
	bool correct = false;


	for(auto c : productions_) {
		if (std::get<0>(c) == curState_) {
			if ((std::get<1>(c) == TM::TapeSymbol(getHead())))  {
			// Found correct transition:
			writeHead(std::get<2>(c));
			move(std::get<3>(c));
			curState_ = std::get<4>(c);
			correct = true;
			break;
			}
			else if ( std::get<1>(c) == TapeSymbol(utilities::charToString('*'))) {
				if (std::get<2>(c) == TapeSymbol(utilities::charToString('*'))) {
					// do nothing to tape
				}
				else {
						writeHead(std::get<2>(c));
				}
				move(std::get<3>(c));
				curState_ = std::get<4>(c);
				correct = true;
				break;
			}
		}
	}
	if (!correct) {
		std::cout << "CurState = " << curState_ << std::endl;
			curState_ = "error";
	}
}

void TuringMachine::resetTape() {
	tape_.clear();
	tape_ = Tape(100,TapeSymbol());
}
} /* namespace TM */
