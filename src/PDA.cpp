/*
 * PDA.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: tom
 */

#include "PDA.h"

namespace PDA {


PDA::PDA() {}


PDA::PDA(CFG* grammar) {
	cfg = grammar;
	type = acceptByEmptyStack;

	std::vector<std::string> terminals = cfg->getTerminals();
	std::vector<std::string> variables = cfg->getVariables();
	std::map<std::string, std::vector<std::string>> rules = cfg->getRules();
	std::string startstring = cfg->getStart();

	for (auto terminal : terminals) {
		input_alphabet.push_back(terminal[0]);
		stack_alphabet.push_back(terminal.substr(0, 1));
	}
	for (auto variable : variables) {
		stack_alphabet.push_back(variable.substr(0, 1));
	}



	start_state = "q";
	start_stack = startstring;

	accept_states.clear();

	State q("q");
	for (auto variable : variables) {
		std::vector<std::string> transitions = rules[variable];
		for (auto transition : transitions){
			std::vector<std::string> stack_instructions;
			stack_instructions.push_back("pop");
			while(transition != "") {
				stack_instructions.push_back("push");
				stack_instructions.push_back(transition.substr(transition.size()-1, transition.size()));
				transition.pop_back();
			}

			q.add_transition('e', variable, "q", stack_instructions);
		}
	}

	for (auto terminal : terminals) {
		std::vector<std::string> stack_instructions;
		stack_instructions.push_back("pop");
		char terminal_ch = terminal[0];
		q.add_transition(terminal_ch, terminal, "q", stack_instructions);
	}

	states.push_back(q);
	resetPDA();

}

PDA::~PDA() {}

void PDA::toFinalStateAcceptance() {
	if (type == acceptByFinalState) {
		return;
	}
	else if (type == acceptByEmptyStack) {
		std::string finalstate_name = checkStateNames("q");
		std::string startstate_name = checkStateNames("p");
		std::string bottom_name;
		std::string name;
		bool correct_name = false;
		int postfix_number = 0;
		correct_name = false;
		while(!correct_name) {
			correct_name = true;
			std::stringstream ss;
			ss << "X" << postfix_number;
			name = ss.str();
			for(auto stacksymbol : stack_alphabet) {
				if (stacksymbol == name){
					correct_name = false;
				}
			}
			postfix_number++;
		}
		bottom_name = name;
		type = acceptByFinalState;
		accept_states.push_back(finalstate_name);
		State finalstate(finalstate_name);
		stack_alphabet.push_back(bottom_name);
		for(auto& state : states) {
			std::vector<std::string> stack_instructions;
			stack_instructions.push_back("pop");
			state.add_transition('e', bottom_name, finalstate_name, stack_instructions);
		}
		states.push_back(finalstate);
		State startstate(startstate_name);
		std::vector<std::string> stack_instructions;
		stack_instructions.push_back("push");
		stack_instructions.push_back(start_stack);
		startstate.add_transition('e', bottom_name, start_state, stack_instructions);
		states.push_back(startstate);
		start_state = startstate_name;
		start_stack = bottom_name;

		resetPDA();
	}
}

void PDA::toEmptyStackAcceptance() {
	if (type == acceptByEmptyStack) {
		return;
	}
	else if (type == acceptByFinalState) {
		std::string finalstate_name = checkStateNames("q");
		std::string startstate_name = checkStateNames("p");
		std::string bottom_name;
		std::string name;
		bool correct_name = false;
		int postfix_number = 0;
		postfix_number = 0;
		correct_name = false;
		while(!correct_name) {
			correct_name = true;
			std::stringstream ss;
			ss << "X" << postfix_number;
			name = ss.str();
			for(auto stacksymbol : stack_alphabet) {
				if (stacksymbol == name){
					correct_name = false;
				}
			}
			postfix_number++;
		}
		bottom_name = name;
		type = acceptByEmptyStack;
		State finalstate(finalstate_name);
		stack_alphabet.push_back(bottom_name);
		for(auto stacksymbol : stack_alphabet) {
			std::vector<std::string> stack_instructions;
			stack_instructions.push_back("pop");
			finalstate.add_transition('e', stacksymbol, finalstate_name, stack_instructions);
		}
		states.push_back(finalstate);
		State startstate(startstate_name);
		std::vector<std::string> stack_instructions;
		stack_instructions.push_back("push");
		stack_instructions.push_back(start_stack);
		startstate.add_transition('e', bottom_name, start_state, stack_instructions);
		states.push_back(startstate);
		for(auto a_state : accept_states){
			for (auto state : states) {
				if (state.get_name() == a_state) {
					for(auto stacksymbol : stack_alphabet) {
						std::vector<std::string> stack_instructions;
						stack_instructions.push_back("pop");
						finalstate.add_transition('e', stacksymbol, finalstate_name, stack_instructions);
					}
				}
			}
		}
		accept_states.clear();
		start_state = startstate_name;
		start_stack = bottom_name;

		resetPDA();
	}
}

void PDA::print_status() {
	std::cout << "STATES = (";
	for (auto state : states) {
		std::cout << state.get_name() << ", ";
	}
	std::cout << ")" << std::endl;

	std::cout << "INPUT ALPHABET = (";
	for (auto ia : input_alphabet) {
		std::cout << ia << ", ";
	}
	std::cout << ")" << std::endl;

	std::cout << "STACK ALPHABET = (";
	for (auto sa : stack_alphabet) {
		std::cout << sa << ", ";
	}
	std::cout << ")" << std::endl;
	std::cout << "STARTSTATE = " << start_state << std::endl;
	std::cout << "STARTSTACK = " << start_stack << std::endl;
	std::cout << "ACCEPT STATES = (";
	for (auto ac : accept_states) {
		std::cout << ac << ", ";
	}
	std::cout << ")" << std::endl;
	for (auto state : states) {
		std::cout << state.get_name() << " transitions :" << std::endl;
		state.print_transitions();
	}

}

std::string PDA::checkStateNames(std::string prefix) {
	std::string name;
	bool correct_name = false;
	int postfix_number = 0;
	while(!correct_name) {
		correct_name = true;
		std::stringstream ss;
		ss << prefix << postfix_number;
		name = ss.str();
		for(auto state : states) {
			if (state.get_name() == name){
				correct_name = false;
			}
		}
		postfix_number++;
	}
	return name;
}

void PDA::toLaTeX(std::string filename) {
	std::ofstream fout(filename.c_str());
	fout << "\\documentclass{article}" << std::endl;
	fout << "\\usepackage{tikz}" << std::endl;
	fout << "\\usetikzlibrary{automata, positioning}" << std::endl;
	fout << "\\begin{document}" << std::endl;
	fout << "\\begin{tikzpicture} [->,auto,node distance=5cm, line width=0.4mm]" << std::endl;
	std::string last_state = "";
	for(auto state : states) {
		if (isAcceptState(state.get_name()) && isStartState(state.get_name())) {
			fout << "\\node[state, initial, accepting] (" << state.get_name() << ") ";
			fout << "{" << state.get_name() << "};" << std::endl;
			last_state = state.get_name();
			break;
		}
		else if (isStartState(state.get_name())) {
			fout << "\\node[state, initial] (" << state.get_name() << ") ";
			fout << "{" << state.get_name() << "};" << std::endl;
			last_state = state.get_name();
			break;
		}
	}
	for(auto state : states){
		if (!(isAcceptState(state.get_name()) || isStartState(state.get_name()))) {
			fout << "\\node[state] (" << state.get_name() << ") ";
			if (last_state != "") {
				fout << "[right =of " << last_state << "] ";
			}
			fout << "{" << state.get_name() << "};" << std::endl;
			last_state = state.get_name();
			continue;;
		}
	}
	for(auto state : states){
		if (isAcceptState(state.get_name())) {
			fout << "\\node[state, accepting] (" << state.get_name() << ") ";
			if (last_state != "") {
				fout << "[right =of " << last_state << "] ";
			}
			fout << "{" << state.get_name() << "};" << std::endl;
			last_state = state.get_name();
			continue;;
		}
	}
	fout << "\\path" << std::endl;
	for (auto state : states){
		std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> transitions = state.get_transitions();
		for (auto s : states){
			std::vector<char> input_symbols;
			std::vector<std::string> top_of_stack_symbols;
			std::vector<std::vector<std::string>> stack_ops;
			std::vector<std::string> stackresults;
			std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>::iterator it;
			for(it = transitions.begin(); it != transitions.end(); it++){
				if (it->second.first == s.get_name()){
					input_symbols.push_back(it->first.first);
					top_of_stack_symbols.push_back(it->first.second);
					stack_ops.push_back(it->second.second);
				}
			}
			std::vector<std::string> sim_stack;
			for (unsigned int i = 0; i < stack_ops.size(); i++) {
				sim_stack.push_back(top_of_stack_symbols[i]);
				for(unsigned int j = 0; j < stack_ops[i].size(); j++) {
					if (stack_ops[i][j] == "pop") {
						sim_stack.pop_back();
					}
					else if (stack_ops[i][j] == "push"){
						sim_stack.push_back(stack_ops[i][j+1]);
					}
					else {
						continue;
					}
				}
				std::string stackstring = "";
				while (sim_stack.size() != 0) {
					stackstring += sim_stack.back();
					sim_stack.pop_back();

				}
				stackresults.push_back(stackstring);
				sim_stack.clear();
			}
			if (input_symbols.size() == 0) {
				continue;
			}
			else if (state.get_name() == s.get_name()){
				fout << "(" << state.get_name() << ") edge [loop above] node[text width=1cm, align=center] {";
				for (unsigned int i = 0; i < input_symbols.size(); i++) {
					fout << "$" << input_symbols[i] << ", " << top_of_stack_symbols[i] << " | ";
					if (stackresults[i] == "") {
						fout << "e";
					}
					else {
						fout << stackresults[i];
					}
					fout << "$";
					fout << " \\\\ ";
				}
				fout << "} (" << s.get_name() << ")" << std::endl;
			}
			else {
				fout << "(" << state.get_name() << ") edge [bend left] node[text width=1cm, align=center] {";
				for (unsigned int i = 0; i < input_symbols.size(); i++) {
					fout << "$" <<input_symbols[i] << ", " << top_of_stack_symbols[i] << " | ";
					if (stackresults[i] == "") {
						fout << "e";
					}
					else {
						fout << stackresults[i];
					}
					fout << "$";
					fout << " \\\\ ";
				}
				fout << "} (" << s.get_name() << ")" << std::endl;
			}
		}
	}
	fout << ";" << std::endl;
	fout << "\\end{tikzpicture}" << std::endl;
	fout << "\\end{document}" << std::endl;
	fout.close();
}

bool PDA::isAcceptState(std::string name) {
	for (auto accept : accept_states) {
		if (name == accept) {
			return true;
		}
	}
	return false;
}

bool PDA::isStartState(std::string name) {
	return (name == start_state);
}

bool PDA::containsString(std::string input) {
	resetPDA();

	// SETUP THE PDA FROM THE START
	std::vector<std::pair<std::pair<State*, std::vector<std::string>>, std::string>> state_stack_input;
	std::pair<std::pair<State*, std::vector<std::string>>, std::string> initial_pair;
	initial_pair.first.first = cur_states[0].first;
	initial_pair.first.second = cur_states[0].second;
	initial_pair.second = input;
	state_stack_input.push_back(initial_pair);

	while(state_stack_input.size() != 0) {
		// CHECK IF THE WHOLE STRING IS READ AND ACCEPTED
		for (auto ssi : state_stack_input) {
			if (type == acceptByFinalState) {
				if (ssi.second == "" && isAcceptState(ssi.first.first->get_name())){
					resetPDA();
					return true;
				}
			}
			else if (type == acceptByEmptyStack) {
				if (ssi.second == "" && ssi.first.second.size() == 0) {
					resetPDA();
					return true;
				}
			}
		}
		// DO THE TRANSITIONS AND PUSH THEM IN A VECTOR
		std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> return_vector;
		std::vector<std::string> remaining_string_vector;
		for (unsigned int k = 0; k < state_stack_input.size(); k++) {
			std::string stacksymbol;
			if (state_stack_input[k].first.second.size() != 0) {
				stacksymbol = state_stack_input[k].first.second.back();
			}
			else {
				stacksymbol = "e";
			}
			if (state_stack_input[k].second != ""){
				// There is still input;
				return_vector.push_back(state_stack_input[k].first.first->simulate(state_stack_input[k].second[0], stacksymbol));
				std::string inputstr = state_stack_input[k].second;
				inputstr = inputstr.substr(1, inputstr.size());
				remaining_string_vector.push_back(inputstr);
			}
			// Try an epsilon transition.
			return_vector.push_back(state_stack_input[k].first.first->simulate('e', stacksymbol));
			std::string inputstr = state_stack_input[k].second;
			remaining_string_vector.push_back(inputstr);
		}

		// USE THE INFORMATION FROM THE TRANSITIONS TO UPDATE EVERYTHING
		unsigned int counter = 0;
		unsigned int string_counter = 0;
		std::vector<std::pair<std::pair<State*, std::vector<std::string>>, std::string>> new_ssi_vector;
		for (auto v : return_vector) {
			// LOOP OVER ALL THE POSSIBLE TRANSITIONS FROM 1 STATE
			for (unsigned int i = 0; i < v.size(); i++) {
				std::string statename = v[i].first;
				State* stateptr = nullptr;
				std::vector<std::string> new_stack;
				for(auto str : state_stack_input[counter].first.second) {
					new_stack.push_back(str);
				}
				// DO THE STACK OPERATIONS
				for(unsigned int j = 0; j < v[i].second.size(); j++) {
					if (v[i].second[j] == "pop") {
						if (new_stack.size() != 0){
							new_stack.pop_back();
						}
					}
					else if(v[i].second[j] == "push") {
						new_stack.push_back(v[i].second[j+1]);
					}
					else {
						continue;
					}
				}
				// FIND THE CORRECT STATEPTR
				std::vector<State>::iterator it;
				for(it = states.begin(); it != states.end(); it++) {
					if(it->get_name() == statename) {
						stateptr = &(*it);
					}
				}
				std::pair<std::pair<State*, std::vector<std::string>>, std::string> new_pair;
				new_pair.first.first = stateptr;
				new_pair.first.second = new_stack;
				new_pair.second = remaining_string_vector[string_counter];
				new_ssi_vector.push_back(new_pair); // PUSH BACK THE NEW CURRENT STATE PAIR
			}
			if (v.size() != 0){
				counter++;
			}
			string_counter++;
		}
		state_stack_input = new_ssi_vector;
	}

	resetPDA();
	return false;
}

void PDA::resetPDA() {
	std::pair<State*, std::vector<std::string> > cur_pair;
	State* state_ptr = nullptr;
	std::vector<State>::iterator it;
	for (it = states.begin(); it != states.end(); it++){
		if (it->get_name() == start_state){
			state_ptr = &(*it);
		}
	}
	std::vector<std::string> initial_stack;
	initial_stack.push_back(start_stack);
	cur_pair.first = state_ptr;
	cur_pair.second = initial_stack;

	cur_states.clear();
	cur_states.push_back(cur_pair);
}

} /* namespace PDA */

// TODO: Clean the code
// TODO: Check if in alphabet
