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

ParseTable::ParseTable(Grammar::CFG grammar, std::string ptableXML) {
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

	PTableParser ptableParser;
	p_table = ptableParser.parse(ptableXML, p_table);

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
