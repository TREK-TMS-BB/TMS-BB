/*
 * PTableParser.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: kristof
 */

#include "PTableParser.h"

namespace parser {

PTableParser::PTableParser(std::string filename, std::vector<std::vector<std::string> > ptable) {

	pTable_ = ptable;

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		std::string errorMessage = doc.ErrorDesc();
		errorMessage += " " + filename;
		throw(Exception(errorMessage));
	}

	TiXmlElement* table = doc.FirstChildElement();

	if(table == NULL) {
		std::cout << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		exit(EXIT_FAILURE);
	}

    for(TiXmlElement* e = table->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
    	std::string ePart = e->Value();
    	if (utilities::isNumber(ePart)) {
    		parseRow(e);
    	}
    }
}

PTableParser::~PTableParser() {
	// TODO Auto-generated destructor stub
}

void PTableParser::parseRow(TiXmlElement* e) {
	int counter = 0;
	std::vector<std::string> row;
	for (TiXmlElement* var = e->FirstChildElement(); var != NULL; var = var->NextSiblingElement()) {
		std::string fieldName = var->Value();
		if(fieldName == pTable_.at(0).at(counter)) {
			 row.push_back(var->Attribute("entry"));
		}
		counter++;
	}
	pTable_.push_back(row);
}

} /* namespace parser */
