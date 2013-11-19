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
	//! A standard constructor.
	PDA();

	//! A specified contstructor.
	/**
	 * @param grammar A CFG used to create an equivalent PDA.
	 */
	PDA(CFG* grammar);

	//! A standard destructor.
	virtual ~PDA();

	//! A function changing the PDA to accept by empty stack.
	void toEmptyStackAcceptance();

	//! A function changing the PDA to accept by final state.
	void toFinalStateAcceptance();

	//! A function making a file to print the PDA in LaTeX.
	/**
	 * @param filename The name of the file where the .tex file will be created.
	 */
	void toLaTeX(std::string filename);

	//! A function to print the complete current status of the PDA.
	void print_status();

	bool containsString(std::string input);


private:
	CFG* cfg; //! A pointer to the CFG equivalent with this PDA.

	PDAType type; //! The type of the PDA (acceptByFinalState or acceptByEmptyStack).
	std::vector<State> states; //! A vector containing all the states of the PDA.
	std::vector<char> input_alphabet; //! A vector containing all the symbols that can be used as input.
	std::vector<std::string> stack_alphabet; //! A vector containing all the symbols used on the stack.
	std::string start_state; //! The name of the start state.
	std::string start_stack; //! The symbol that is initially pushed on the stack.
	std::vector<std::string> accept_states; //! A vector containing the names of the accept states.

	std::vector<std::pair<State*, std::stack<std::string> > > cur_states; //! A pair containing a pointer to the current state we are in and its corresponding stack.

private:
	//! Checks wether a certain name is already used in the PDA.
	/**
	 * @param prefix Start of the name you want to give the state.
	 */
	std::string checkStateNames(std::string prefix);

	//! Returns whether a certain state is an accept state.
	/**
	 * @param name Name of the state you want to check.
	 * @return A boolean telling whether it is an accept state.
	 */
	bool isAcceptState(std::string name);

	//! Returns whether a certain state is a start state.
	/**
	 * @param name Name of the state you want to check.
	 * @return A boolean telling whether it is a start state.
	 */
	bool isStartState(std::string name);

};

} /* namespace PDA */

#endif /* PDA_H_ */
