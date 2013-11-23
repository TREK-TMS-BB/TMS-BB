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
#include "Exception.h"

#include "tinyXML/tinyxml.h"

namespace parser {

class Parser {
public:
	Parser();
	virtual ~Parser();
};

class CFGParser : public Parser {
public:
	//! Default constructor: will parse the entire CFG.
	/**
	 * @param filename XML file that describes the to be parsed CFG.
	 */
	CFGParser(std::string);

	virtual ~CFGParser();

	//! Returns the CFG variables.
	/**
	 * @return A vector containing the variables (strings).
	 */
	std::vector<std::string> getVariables() const;

	//! Returns the CFG terminals.
	/**
	 * @return A vector containing the terminals (strings).
	 */
	std::vector<std::string> getTerminals() const;

	//! Returns the CFG rules.
	/**
	 * @return A map in the form of (head, body)
	 */
	std::map<std::string, std::vector<std::string> > getRules() const;

	//! Returns the start of the CFG.
	/**
	 * @return The start variable (string)
	 */
	std::string getStart() const;

private:
	std::vector<std::string> variables;
	std::vector<std::string> terminals;
	std::map<std::string, std::vector<std::string> > rules;
	std::string startSymbol;

	//! Parses the variables of the CFG.
	void parseVariables(TiXmlElement*);

	//! Parses the terminals of the CFG.
	void parseTerminals(TiXmlElement*);

	//! Parses the rules of the CFG.
	void parseRules(TiXmlElement*);

	//! Parses the start symbol of the CFG.
	void parseStart(TiXmlElement*);
};

}

#endif /* PARSER_H_ */
