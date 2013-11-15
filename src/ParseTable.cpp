/*
 * ParseTable.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "ParseTable.h"

ParseTable::ParseTable()
	: table()
{}

ParseTable::ParseTable(CFG grammar) {
	// Not final yet. This is the hardcoded construction of LR1-1's parsetable.
	std::vector<std::vector<std::string> > p_table;
	std::vector<std::string> row1;
	std::vector<std::string> terminals = grammar.getTerminals();
	std::vector<std::string> variables = grammar.getVariables();
	// Construct Row1 and push it in our table.

	for (unsigned int i = 0; i < terminals.size(); i++) {
		row1.push_back(terminals.at(i));
	}
	row1.push_back("EOS");
	for (unsigned int i = 0; i < variables.size(); i++) {
		row1.push_back(variables.at(i));
	}
	p_table.push_back(row1);

	// Construct the rest
	std::vector<std::string> row2;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			row2.push_back("shift 2");
			break;
		case 2:
			row2.push_back("S->epsilon");
			break;
		case 3:
			row2.push_back("9");
			break;
		case 4:
			row2.push_back("8");
			break;
		case 5:
			row2.push_back("7");
			break;
		default:
			row2.push_back("");
		}
	}
	p_table.push_back(row2);

	std::vector<std::string> row3;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			row3.push_back("shift 2");
			break;
		case 1:
			row3.push_back("shift 6");
			break;
		case 2:
			row3.push_back("X->x");
			break;
		case 4:
			row3.push_back("3");
			break;
		case 5:
			row3.push_back("4");
			break;
		default:
			row3.push_back("");
		}
	}
	p_table.push_back(row3);

	std::vector<std::string> row4;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row4.push_back("X->xX");
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
			row5.push_back("shift 5");
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
			row6.push_back("Y->xYy");
			break;
		case 2:
			row6.push_back("Y->xYy");
			break;
		default:
			row6.push_back("");
		}
	}
	p_table.push_back(row6);

	std::vector<std::string> row7;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 1:
			row7.push_back("Y->xy");
			break;
		case 2:
			row7.push_back("Y->xy");
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
			row8.push_back("S->Y");
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
			row9.push_back("S->X");
			break;
		default:
			row9.push_back("");
		}
	}
	p_table.push_back(row8);

	std::vector<std::string> row10;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 2:
			row10.push_back("accept");
			break;
		default:
			row10.push_back("");
		}
	}
	p_table.push_back(row10);

	table = p_table;

	// Construct lookup map
	for (unsigned int i = 0; i < table.at(0).size(); i++	) {
		std::cout << table.at(0).at(i) << " " << i << std::endl;
		lookup[table.at(0).at(i)] = i;
	}
	std::cout << "Hello" << std::endl;
}

ParseTable::~ParseTable() {
	// TODO Auto-generated destructor stub
}

std::pair<EAction, std::string> ParseTable::extractInfo(std::string entry) {
	std::string::iterator found;
	std::string::iterator it;
	std::string number;
	EAction action;
	/*found = entry.find("shift ");
	if (found != std::string::npos) {
		found += 6;
		if (isdigit(*it)) {
			return (shift, *it);
		}
		else {
			// Wrong entry
		}
	}*/
	//if ()
}

std::pair<EAction, std::string> ParseTable::operator() (int token, std::string symbol) const {
	std::string entry = table.at(token).at(lookup.at(symbol));


	std::pair<EAction, std::string> test(shift, "hello");
	return test;
}
