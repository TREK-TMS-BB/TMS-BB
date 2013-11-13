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
	std::vector<std::string>::iterator it;
	std::vector<std::vector<std::string> > p_table;
	std::vector<std::string> row1;

	// Construct Row1 and push it in our table.
	for (it = grammar.getTerminals().begin(); it != grammar.getVariables().end(); it++) {
		std::cout << *it << "OVER HERE" << std::endl;
		// Why does this return capital letters?
		row1.push_back(*it);
	}

	row1.push_back("EOS");
	for (it = grammar.getVariables().begin(); it != grammar.getVariables().end(); it++) {
		row1.push_back(*it);
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
}


ParseTable::~ParseTable() {
	// TODO Auto-generated destructor stub
}

std::pair<EAction, std::string> ParseTable::operator() (int token, std::string symbol) const {

}
