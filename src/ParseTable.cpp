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

}

ParseTable::~ParseTable() {
	// TODO Auto-generated destructor stub
}

std::pair<EAction, std::string> ParseTable::operator() (int token, std::string symbol) const {

}
