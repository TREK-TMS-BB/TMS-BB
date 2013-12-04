/*
 * PTableParser.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: kristof
 */

#include "PTableParser.h"

namespace parser {

PTableParser::PTableParser()
	: pTable_()
{}

PTableParser::~PTableParser() {
	// TODO Auto-generated destructor stub
}

std::vector<std::vector<std::string> > PTableParser::parse(std::string filename, std::vector<std::vector<std::string> > ptable) {
	try {
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
				if (ePart == "row") {
					parseRow(e);
				}
				else {
					throw Exception(ePart + " is not a valid tag in the parse table xml.");
				}
		}
    return pTable_;
	}
	catch (Exception& e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
}

void PTableParser::parseRow(TiXmlElement* e) {
	int counter = 0;
	std::vector<std::string> row;
	for (TiXmlElement* var = e->FirstChildElement(); var != NULL; var = var->NextSiblingElement()) {
		try {
			std::string fieldName = var->Value();
			if(fieldName == pTable_.at(0).at(counter)) {
				if (var->Attribute("entry") != "empty") {
					 row.push_back(var->Attribute("entry"));
				}
				else {
					row.push_back("");
				}
			}
			else {
				throw Exception("Tag name " + fieldName + " should be " + pTable_.at(0).at(counter) + " in the parseTable file.");
			}
			counter++;
		}
		catch(Exception& e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	pTable_.push_back(row);
}

} /* namespace parser */
