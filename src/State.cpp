/*
 * State.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: tom
 */

#include "State.h"
#include <iostream>

namespace PDA {

State::State(): statename("uninitialized"){
}

State::State(std::string n): statename(n) {
}

State::~State() {

}

std::string State::get_name() {
	return this->statename;
}

void State::add_transition(char input, std::string top_of_stack, std::string state, std::vector<std::string> stack_operations){
	std::pair<char, std::string> input_pair;
	std::pair<std::string, std::vector<std::string>> output_pair;
	input_pair.first = input;
	input_pair.second = top_of_stack;
	output_pair.first = state;
	output_pair.second = stack_operations;
	this->transitions.insert(std::pair<std::pair<char, std::string>,
			std::pair<std::string, std::vector<std::string>>>(input_pair, output_pair));
}

void State::print_transitions() {
	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>::iterator it;
	for (it = this->transitions.begin(); it != this->transitions.end(); it++) {
		std::cout << "(" << this->statename << ", " << it->first.first << ", " << it->first.second << ") --> (" << it->second.first << ")" << std::endl;
		std::cout << "STACK OPERATIONS: ";
		for (auto op : it->second.second) {
			std::cout << op << ", ";
		}
		std::cout << std::endl << std::endl;
	}
}

std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> State::get_transitions() {
	return this->transitions;
}

std::vector<std::pair<std::string, std::vector<std::string>>> State::simulate(char input, std::string top_of_stack) {
	std::vector<std::pair<std::string, std::vector<std::string>>> return_vec;
	std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>::iterator it;
	for (it = this->transitions.begin(); it != this->transitions.end(); it++) {
		if (input == it->first.first && top_of_stack == it->first.second) {
			return_vec.push_back(it->second);
		}
	}
	return return_vec;
}




} /* namespace PDA */
