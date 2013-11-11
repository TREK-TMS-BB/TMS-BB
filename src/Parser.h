/*
 * Parser.h
 *
 *  Created on: Nov 11, 2013
 *      Author: kristof
 */

#ifndef PARSER_H_
#define PARSER_H_
#define TIXML_USE_STL

#include <string>
#include <iostream>
#include "tinyXML/tinyxml.h"

class Parser {
public:
	Parser();
	virtual ~Parser();
};

class CFGParser : public Parser {
public:
	CFGParser(std::string);
	virtual ~CFGParser();
private:
	std::vector<std::string> variables;
	std::vector<std::string> terminals;
	std::map<std::string, std::vector<std::string> > rules;
	std::string startSymbol;
};

#endif /* PARSER_H_ */
