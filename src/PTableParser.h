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
	PTableParser(std::string, std::vector<std::vector<std::string> >);
	virtual ~PTableParser();

private:
	std::vector<std::vector<std::string> > pTable_;

	void parseRow(TiXmlElement*);
};

} /* namespace parser */

#endif /* PTABLEPARSER_H_ */
