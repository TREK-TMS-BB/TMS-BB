/*
 * Parser.h
 *
 *  Created on: Nov 11, 2013
 *      Author: kristof
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "tinyXML/tinyxml.h"

class Parser {
public:
	Parser();
	virtual ~Parser();
};

class CFGParser : public Parser {
public:
	CFGParser(std::string);
	// Default constructor: will parse the entire CFG.

	virtual ~CFGParser();
private:
	std::vector<std::string> variables;
	std::vector<std::string> terminals;
	std::map<std::string, std::vector<std::string> > rules;
	std::string startSymbol;

	void parseVariables(TiXmlElement*);
	// Parses the variables of the CFG.

	void parseTerminals(TiXmlElement*);
	// Parses the terminals of the CFG.

	void parseRules(TiXmlElement*);
	// Parses the rules of the CFG.

	void parseStart(TiXmlElement*);
	// Parses the start symbol of the CFG.
};

#endif /* PARSER_H_ */
