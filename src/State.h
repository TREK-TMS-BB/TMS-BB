/*
 * State.h
 *
 *  Created on: Nov 16, 2013
 *      Author: tom
 */

#ifndef STATE_H_
#define STATE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace PDA {

class State {
public:
	//! A default constructor.
	State();

	//! A specified constructor.
	/**
	 * @param n The name of the state.
	 */
	State(std::string n);

	//! Default destructor.
	virtual ~State();

	//! A function giving the name of the state.
	/**
	 * @return It returns a string with the name of the state.
	 */
	std::string get_name();

	//! A function used to add a transition to a state.
	/**
	 * @param input The input symbol on which the state should transition.
	 * @param top_of_stack The symbol that should be on top of the stack when transitioning.
	 * @param state The name of the state you want to transition to.
	 * @param stack_operations A vector containing operations that should be run on the stack.
	 */
	void add_transition(char input, std::string top_of_stack, std::string state, std::vector<std::string> stack_operations);

	//! A function returning all the states you can transition to and their stacks given a certain input.
	/**
	 * @param input The char that is read to transition.
	 * @param top_of_stack The current top of the stack.
	 * @return A vector containing pairs with the name of the state you can go to and the operations of the stack you should run then.
	 */
	std::vector<std::pair<std::string, std::vector<std::string>>> simulate(char input, std::string top_of_stack);

	//! A function neatly printing out the transitions.
	void print_transitions();

	//! A function returning the whole transition map.
	/**
	 * @return A multimap containing the input symbols and corresponding transition info.
	 */
	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> get_transitions();

private:
	std::string statename; //! A string with the name of the state.
	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> transitions; //! A multimap containing input pairs and their corresponding transition info.
};

} /* namespace PDA */

#endif /* STATE_H_ */
