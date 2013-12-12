/*
 * TMProgram.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: robin
 */

#include "TMProgram.h"

namespace TM {

TMProgram::TMProgram() {
	states_.push_back("S");
}

TMProgram::TMProgram(std::string filename) : filename_(filename) {
	parser::TMParser parse(filename_);
	states_ = parse.getStates();
	productions_ = parse.getProductions();
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


void TMProgram::linkWith(const TMProgram& prog) {

	// add transition from "halt" to start of 2nd

	Production link(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, prog.states_.at(0));
	productions_.push_back(link);
	// add all the states
	for (auto e: prog.states_) {
		states_.push_back(e);
	}
	// add all productions
	for (auto e : prog.productions_) {
		productions_.push_back(e);
		std::cout << "added production "<< std::get<0>(e) << "with read symbol: " << std::get<1>(e)<<"\n";
	}
	// add halt production:
	Production endLink(*(prog.states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, "halt");
	productions_.push_back(endLink);
	states_.push_back("halt");
}

void TMProgram::linkWith(std::vector<TMProgram> const& progs) {
	for (auto p : progs) {
		// add transition from "halt" to start of next
		Production link(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, p.states_.at(0));
		productions_.push_back(link);
		// add all the states
		for (auto e: p.states_) {
			states_.push_back(e);
		}
		// add all productions
		for (auto e : p.productions_) {
			productions_.push_back(e);
			std::cout << "added production "<< std::get<0>(e) << "with read symbol: " << std::get<1>(e)<<"\n";
		}
	}
	// add halt production:
	Production endLink(*(states_.end()-1), TapeSymbol("*"), TapeSymbol("*"), none, "halt");
	productions_.push_back(endLink);
	states_.push_back("halt");

}

std::ostream& operator<< (std::ostream& out, const TMProgram &program) {
	out << "INITIAL_INPUT=0 \n"
			"\n"
			"STATES = {" ;
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
