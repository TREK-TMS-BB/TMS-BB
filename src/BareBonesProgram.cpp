/*
 * BareBonesProgram.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#include "BareBonesProgram.h"

namespace BB {

BareBonesProgram::BareBonesProgram(std::vector<std::shared_ptr<BareBonesStatement> > statements, unsigned int nrVariables)
	: statements_(statements), used_variables_(nrVariables)
{}

BareBonesProgram::~BareBonesProgram() {
	// TODO Auto-generated destructor stub
}

void BareBonesProgram::createTMFile(std::string output) {

	TM::TMProgram prog;
	std::vector<TM::TMProgram> progs;
	for(auto a : statements_) {
		TM::TMProgram temp= a->createCode();
		temp.renameStates();
		progs.push_back(temp);
	}
	prog.linkWith(progs, false);
	// add halt transition
	std::vector<TM::StateName> states;
	std::vector<TM::Production> prods;
	states.push_back("halt");
	TM::TMProgram end(states, prods, "end");
	prog.linkWith(end, false);

	std::vector<TM::TapeSymbol> input;
	for (int i = 0; i < used_variables_; i++) {
		input.push_back(TM::TapeSymbol(0));
	}
	prog.setInput(input);
	std::ofstream out;
	out.open(output);
	out << prog << std::endl;

}
} /* namespace BB */
