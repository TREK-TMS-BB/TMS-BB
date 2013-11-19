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
	State();
	State(std::string n);
	virtual ~State();

	std::string get_name();

	void add_transition(char input, std::string top_of_stack, std::string state, std::vector<std::string> stack_operations);

	std::vector<std::pair<std::string, std::vector<std::string>>> simulate(char input, std::string top_of_stack);

	void print_transitions();

	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> get_transitions();

private:
	std::string statename;
	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> transitions;
};

} /* namespace PDA */

#endif /* STATE_H_ */
