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
	std::cout << states_.size();
	productions_ = parse.getProductions();
}

void TMProgram::renameStates() {
	for (std::vector<StateName>::iterator it = states_.begin(); it != states_.end(); it++) {
		*it = filename_ + "_" +  *it;
		std::cout << *it << std::endl;
	}
	for (std::vector<Production>::iterator it = productions_.begin(); it!= productions_.end(); it++) {
		std::get<0>(*it) = filename_ + "_" + std::get<0>(*it);
		std::get<4>(*it) = filename_ + "_" + std::get<4>(*it);
	}
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
		out << std::get<3>(prod) << " ";
		out << std::get<4>(prod) << " ;\n";
	}
	out << "}";

	return out;
}

TMProgram::~TMProgram() {
	// TODO Auto-generated destructor stub
}

} /* namespace TM */
