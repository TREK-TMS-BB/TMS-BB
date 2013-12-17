/*
 * TMProgram.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: robin
 */

#include "TMProgram.h"

namespace TM {

TMProgram::TMProgram() {
	states_.push_back("Start");
}

TMProgram::TMProgram(std::string filename) : filename_(filename) {
	parser::TMParser parse(filename_);
	states_ = parse.getStates();
	productions_ = parse.getProductions();
	//input_ = parse.getInitInput();
}

TMProgram::TMProgram(	std::vector<StateName> states, std::vector<Production> productions, std::string filename) : states_(states), productions_(productions) , filename_(filename){

}


std::string TMProgram::getStart() {
	return states_.at(0);
}

void TMProgram::renameStates() {
	for (std::vector<StateName>::iterator it = states_.begin(); it != states_.end(); it++) {
		*it = filename_ + "_" +  *it;
	}
	for (std::vector<Production>::iterator it = productions_.begin(); it!= productions_.end(); it++) {
		std::get<0>(*it) = filename_ + "_" + std::get<0>(*it);
		std::get<4>(*it) = filename_ + "_" + std::get<4>(*it);
	}
}


void TMProgram::linkWith(const TMProgram& prog, bool halt) {

	// add transition from "halt" to start of 2nd

	Production link(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, prog.states_.at(0));
	productions_.push_back(link);
	// add all the states
	for (auto e: prog.states_) {
		bool dupl = false;
		// check for duplicates:
		for (auto s : states_) {
			if (s == e) {
				dupl = true;
				break;
			}
		}
		if(!dupl) {
			states_.push_back(e);
		}
	}
	// add all productions
	for (auto e : prog.productions_) {
		productions_.push_back(e);
		std::cout << "added production "<< std::get<0>(e) << "with read symbol: " << std::get<1>(e)<<"\n";
	}
	if (halt) {
		// add halt production:
		Production endLink(*(prog.states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, "halt");
		productions_.push_back(endLink);
		states_.push_back("halt");
	}
}

void TMProgram::linkWith(std::vector<TMProgram> const& progs, bool halt ) {
	if (progs.size() == 0) {
		return;
	}
	for (auto p : progs) {
		// add transition from "halt" to start of next
		Production link(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, p.states_.at(0));
		productions_.push_back(link);
		// add all the states
		for (auto e: p.states_) {
			bool dupl = false;
			// check for duplicates:
			for (auto s : states_) {
				if (s == e) {
					dupl = true;
					break;
				}
			}
			if(!dupl) {
				states_.push_back(e);
			}
		}
		// add all productions
		for (auto e : p.productions_) {
			productions_.push_back(e);
			std::cout << "added production "<< std::get<0>(e) << "with read symbol: " << std::get<1>(e)<<"\n";
		}
	}

	if (halt)
	{
		// add halt production:
		Production endLink(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, "halt");
		productions_.push_back(endLink);
		states_.push_back("halt");
	}

}

void TMProgram::setInput(std::vector<TapeSymbol> input) {
	input_.clear();
	input_.insert(input_.begin(), input.begin(), input.end());
}

std::ostream& operator<< (std::ostream& out, const TMProgram &program) {
	out << "INITIAL_INPUT=";
	for (auto e : program.input_) {
		out << e;
	}
	out << "\n\n";
	out << "STATES = {" ;
	out << program.states_.at(0);
	for (int i = 1; i < program.states_.size();i++) {
		out <<","<< program.states_.at(i);
	}
	out << "} \n"
			"\n"
			"PRODUCTIONS { \n";
	for (auto prod : program.productions_) {
		out << std::get<0>(prod) << " ";
		out << std::get<1>(prod) << " ";
		out << std::get<2>(prod) << " ";
		switch (std::get<3>(prod) ) {
		case left:
			out << "l ";
			break;
		case right:
			out << "r ";
			break;
		case none:
			out << "n ";
			break;
		}
		out << std::get<4>(prod) << " ;\n";
	}
	out << "}";

	return out;
}

TMProgram::~TMProgram() {
	// TODO Auto-generated destructor stub
}

} /* namespace TM */
