/*
 * PTableParser.h
 *
 *  Created on: Dec 2, 2013
 *      Author: kristof
 */

#ifndef PTABLEPARSER_H_
#define PTABLEPARSER_H_

#include <string>
#include <iostream>
#include <vector>
#include "Exception.h"
#include "Parser.h"
#include "utilities.h"
#include "tinyXML/tinyxml.h"

namespace parser {

class PTableParser : public Parser {
public:
	//! Default constructor.
	PTableParser();

	virtual ~PTableParser();

	//! This parses the Parse Table XML file and fills in the parse table.
	std::vector<std::vector<std::string> > parse(std::string, std::vector<std::vector<std::string> >);

private:
	std::vector<std::vector<std::string> > pTable_;

	//! Parses one row of the XML file and fills it in the table.
	void parseRow(TiXmlElement*);
};

} /* namespace parser */

#endif /* PTABLEPARSER_H_ */
