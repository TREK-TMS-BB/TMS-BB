/*
 * ParseTable.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "ParseTable.h"

namespace parser {

ParseTable::ParseTable()
	: table()
{}

ParseTable::ParseTable(Grammar::CFG grammar) {
	// Not final yet. This is the hardcoded construction of LR1-1's parsetable.

	std::vector<std::vector<std::string> > p_table;
	std::vector<std::string> row0;
	std::vector<std::string> terminals = grammar.getTerminals();
	std::vector<std::string> variables = grammar.getVariables();
	// Construct row0 and push it in our table.

	for (unsigned int i = 0; i < terminals.size(); i++) {
		row0.push_back(terminals.at(i));
	}
	row0.push_back("EOS");
	for (unsigned int i = 0; i < variables.size(); i++) {
		row0.push_back(variables.at(i));
	}
	p_table.push_back(row0);

	// Construct the rest
	std::vector<std::string> row1;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			row1.push_back("shift 2");
			break;
		case 2:
			row1.push_back("S->");
			break;
		case 3:
			row1.push_back("9");
			break;
		case 4:
			row1.push_back("8");
			break;
		case 5:
			row1.push_back("7");
			break;
		default:
			row1.push_back("");
		}
	}
	p_table.push_back(row1);

	std::vector<std::string> row2;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			row2.push_back("shift 2");
			break;
		case 1:
			row2.push_back("shift 6");
			break;
		case 2:
			row2.push_back("X->x");
			break;
		case 4:
			row2.push_back("3");
			break;
		case 5:
			row2.push_back("4");
			break;
		default:
			row2.push_back("");
		}
	}
	p_table.push_back(row2);

	std::vector<std::string> row3;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row3.push_back("X->xX");
			break;
		default:
			row3.push_back("");
		}
	}
	p_table.push_back(row3);

	std::vector<std::string> row4;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 1:
			row4.push_back("shift 5");
			break;
		default:
			row4.push_back("");
		}
	}
	p_table.push_back(row4);


	std::vector<std::string> row5;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 1:
			row5.push_back("Y->xYy");
			break;
		case 2:
			row5.push_back("Y->xYy");
			break;
		default:
			row5.push_back("");
		}
	}
	p_table.push_back(row5);

	std::vector<std::string> row6;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 1:
			row6.push_back("Y->xy");
			break;
		case 2:
			row6.push_back("Y->xy");
			break;
		default:
			row6.push_back("");
		}
	}
	p_table.push_back(row6);

	std::vector<std::string> row7;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row7.push_back("S->Y");
			break;
		default:
			row7.push_back("");
		}
	}
	p_table.push_back(row7);

	std::vector<std::string> row8;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row8.push_back("S->X");
			break;
		default:
			row8.push_back("");
		}
	}
	p_table.push_back(row8);

	std::vector<std::string> row9;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row9.push_back("accept");
			break;
		default:
			row9.push_back("");
		}
	}
	p_table.push_back(row9);

	table = p_table;

	// Construct lookup map
	for (unsigned int i = 0; i < table.at(0).size(); i++	) {
		lookup[table.at(0).at(i)] = i;
	}
}

ParseTable::~ParseTable() {
	// TODO Auto-generated destructor stub
}

std::pair<EAction, std::string> ParseTable::extractInfo(std::string entry) const {
	std::string::iterator it;
	std::stringstream ss;

	// Check if entry was blank.
	if (entry == "") {
		return std::pair<EAction, std::string>(blank, "blank");
	}

	// Check if entry was accept
	if (entry.find("accept") != std::string::npos) {
		return std::pair<EAction, std::string>(accept, "accept");
	}

	// Check if only stack token
	std::string number;
	for (it = entry.begin(); it != entry.end(); it++) {
		if (isdigit(*it) && (it == entry.end()-1)) {
			number += *it;
			return std::pair<EAction, std::string>(jump, number);
		}
		else if (isdigit(*it)) {
			number += *it;
			continue;
		}
		else {
			break;
		}
	}

	// Check if shift operation
	std::size_t found = entry.find("shift ");
	if (found != std::string::npos) {
		found += 6;
		it = entry.begin() + found;
		if (isdigit(*it)) {
			// Flush the stringstream & convert chars to string
			ss.str("");
			for (it; it != entry.end(); it++) {
				ss << *it;
			}
			return (std::pair<EAction, std::string>(shift, ss.str()));
		}
		else {
			// Return error
			return std::pair<EAction, std::string>(error, "error");
		}
	}

	// Check if reduction operation
	if (isupper(*(entry.begin()))) {
		std::string body;
		// Flush ss & convert char to string
		ss.str("");
		ss << *(entry.begin());
		std::string head = ss.str();
		bool readingBody = false;
		while (it != entry.end()) {
			if (readingBody) {
				body += *it;
			}
			else if ((*it == '-') && (*(++it) == '>')) {
				readingBody = true;
			}
			it++;
		}
		std::string rule = head + body;
		return (std::pair<EAction, std::string>(reduction, rule));
	}

	// Return error
	return std::pair<EAction, std::string>(error, "error");
}

std::pair<EAction, std::string> ParseTable::operator() (int token, std::string symbol) const{
	try {
		std::string entry = table.at(token).at(lookup.at(symbol));
		return extractInfo(entry);
	}
	catch (std::out_of_range& e) {
		std::cout << "Bad input: it is not part of the CFL." << std::endl;
		exit(1);
	}
}

}
