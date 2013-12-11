/*
 * TMParser.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: kristof
 */

#include "TMParser.h"

namespace parser {

TMParser::TMParser(std::string file) {
	try {
		std::ifstream fs;
		fs.open(file);
		if (fs.is_open()) {
			while (!fs.eof()) {
				// As long as there is input.
				std::string line;
				getline(fs, line);
				std::size_t found;

				// Check for States.
				found = line.find("STATES = {");
				if (found != std::string::npos) {
					// We found the States.
					this->parseStates(line, found);
					continue;
				}

				// Check for Initial Input.
				found = line.find("INITIAL_INPUT = ");
				if (found != std::string::npos) {
					// We found the initInput.
					this->parseInitInput(line, found);
					continue;
				}

				// Check for Productions
				found = line.find("PRODUCTIONS {");
				if (found != std::string::npos) {
					// We found the productions.
					getline(fs, line);
					while(line == "" || line.at(0) != '}') {
						if (line == "") {
							getline(fs, line);
						}
						else {
							this->parseProduction(line);
							getline(fs, line);
						}
					}
				}
			}
		}
		else {
			throw Exception("Something went wrong when opening the file.");
		}
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void TMParser::parseProduction(std::string line) {
	try {
		TM::StateName curState;
		TM::TapeSymbol readSymbol;
		TM::TapeSymbol writeSymbol;
		TM::Direction move;
		TM::StateName newState;

		// Read the current state.
		std::string::iterator it2 = line.begin();
		while (*it2 != ' ') {
			curState += *it2;
			it2++;
		}
		// Check if the state is a valid state.
		std::vector<TM::StateName>::iterator its;
		its = std::find(states_.begin(), states_.end(), curState);
		if (its == states_.end() && curState != "halt") {
			// Invalid state.
			throw Exception(curState + " is not a valid state. This production will not be added.");
		}

		// At this point our iterator is on ' '
		it2++;

		// Read our read symbol.
		if (*it2  == 'B') {
			readSymbol = TM::TapeSymbol();
		}
		else if (isdigit(*it2)) {
			readSymbol = TM::TapeSymbol(*it2-'0');
		}
		else {
			std::string temp = utilities::charToString(*it2);
			readSymbol = TM::TapeSymbol(temp);
		}

		//
		this->iteratorCheck(it2, ' ');

		// Read our write symbol.
		if (*it2  == 'B') {
			writeSymbol = TM::TapeSymbol();
		}
		else if (isdigit(*it2)) {
			writeSymbol = TM::TapeSymbol(*it2-'0');
		}
		else {
			writeSymbol = TM::TapeSymbol(utilities::charToString(*it2));
		}


		this->iteratorCheck(it2, ' ');

		// Read our move.
		switch (*it2) {
		case 'r':
			move = TM::right;
			break;
		case 'l':
			move = TM::left;
			break;
		case 'n':
			move = TM::none;
			break;
		default:
			throw Exception("Unknown move direction. This production will not be added.");
		}

		this->iteratorCheck(it2, ' ');

		// Read the new state.
		while (*it2 != ' ') {
			newState += *it2;
			it2++;
		}

		// Check if the state is a valid state.
		its = std::find(states_.begin(), states_.end(), newState);
		if (its == states_.end() && newState != "halt") {
			// Invalid state.
			throw Exception(newState + " is not a valid state. This production will not be added.");
		}

		TM::Production production(curState, readSymbol, writeSymbol, move, newState);

		productions_.push_back(production);
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}

}


void TMParser::parseStates(std::string line, std::size_t found) {
	std::string::iterator it;
	for (it = line.begin() + found + 10; it != line.end(); it++) {
		switch(*it) {
		case ',':
			break;
		case ' ':
			// Do nothing
			break;
		case '}':
			// We're done parsing.
			return;
			break;
		default:
			// This is where we'll read our states.
			std::string::iterator it2 = it;
			TM::StateName state = "";
			int counter = 0;
			while (*it2 != ',' && *it2 != '}' && *it2 != ' ') {
				state += *it2;
				it2++;
				counter++;
			}
			it += counter-1;
			std::cout << state << std::endl;
			states_.push_back(state);
			break;
		}
	}

	std::cout << "jajaj" << std::endl;
}

void TMParser::parseInitInput(std::string line, std::size_t found) {
	std::string::iterator it;
	std::string initInput = "";
	for (it = line.begin() + found + 18; it != line.end(); it++) {
		if (*it != ' ' && *it != '#') {
			initInput += *it;
		}
		else {
			initInput_ = initInput;
			return;
		}
	}
}

void TMParser::iteratorCheck(std::string::iterator& it2, char c) const {
	try {
		// Get our iterator to the next correct spot.
		it2++;
		if (*it2 != c) {
			throw Exception("There is a fault in a production. It will not be added. Are your sure there are spaces between your production parts?");
		}
		else {
			it2++;
		}
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
	}
}


TMParser::~TMParser() {
	// TODO Auto-generated destructor stub
}

std::string TMParser::getInitInput() const {
	return initInput_;
}

std::vector<TM::StateName> TMParser::getStates() const {
	return states_;
}

std::vector<TM::Production> TMParser::getProductions() const {
	return productions_;
}

std::ostream& operator<<(std::ostream& out, TMParser& tmp) {
	out << "Initial input = " << tmp.initInput_ << std::endl;
	out << "States = { ";
	for (auto e : tmp.states_) {
		out << e << " | ";
	}
	out << "}" << std::endl;
	out << "Productions { " << std::endl;
	for (auto e : tmp.productions_) {
		out << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << " " << std::get<3>(e) << " " << std::get<4>(e) << std::endl;
	}
	out << "}" << std::endl;
	return out;
}


} /* namespace parser */
