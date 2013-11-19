/*
 * PDA.h
 *
 *  Created on: Nov 16, 2013
 *      Author: tom
 */

#ifndef PDA_H_
#define PDA_H_

#include "CFG.h"
#include <vector>
#include <stack>
#include <ostream>
#include <sstream>
#include "State.h"
#include "utilities.h"
#include <cstdlib>
#include <fstream>

namespace PDA {

enum PDAType {acceptByEmptyStack, acceptByFinalState};

class PDA {
public:
	PDA();
	PDA(CFG* grammar);
	virtual ~PDA();

	void toEmptyStackAcceptance();
	void toFinalStateAcceptance();

	void toLaTeX(std::string filename);

	void print_status();

private:
	CFG* cfg;

	PDAType type;
	std::vector<State> states;
	std::vector<char> input_alphabet;
	std::vector<std::string> stack_alphabet;
	std::string start_state;
	std::string start_stack;
	std::vector<std::string> accept_states;

	std::vector<std::pair<State*, std::stack<std::string> > > cur_states;

private:
	std::string checkStateNames(std::string prefix);
	bool isAcceptState(std::string name);
	bool isStartState(std::string name);

};

} /* namespace PDA */

#endif /* PDA_H_ */
