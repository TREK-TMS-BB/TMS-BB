/*
 * LRParser.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#include "LRParser.h"

LRParser::LRParser()
	: p_table()
	  //stack()
{}

LRParser::LRParser(CFG grammar)
	: p_table(grammar)
	 //stack()

{}

LRParser::LRParser(ParseTable pt)
	: p_table(pt)
{}

LRParser::~LRParser() {
	// TODO Auto-generated destructor stub
}

