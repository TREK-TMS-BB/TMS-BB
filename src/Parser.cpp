/*
 * Parser.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: kristof
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

CFGParser::CFGParser(std::string filename) {
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::cout << doc.ErrorDesc() << std::endl;
		exit(EXIT_FAILURE);
	}

	TiXmlElement* CFG = doc.FirstChildElement();

	if(CFG == NULL) {
		std::cout << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		exit(EXIT_FAILURE);
	}


}

CFGParser::~CFGParser() {
	// TODO Auto-generated destructor stub
}

