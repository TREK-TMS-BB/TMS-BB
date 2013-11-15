/*
 * LRParser.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "LRParser.h"

LRParser::LRParser()
	: p_table_(),
	  stack_()
{}

LRParser::LRParser(CFG grammar)
	: p_table_(grammar),
	 stack_()

{}

LRParser::LRParser(ParseTable pt)
	: p_table_(pt)
{}

LRParser::~LRParser() {
	// TODO Auto-generated destructor stub
}

