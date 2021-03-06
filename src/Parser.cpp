/*
 * Parser.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: kristof
 */

#include "Parser.h"

#define TIXML_USE_STL

namespace parser {

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

CFGParser::CFGParser(std::string filename) {
	try {
		TiXmlDocument doc;
		if(!doc.LoadFile(filename.c_str())) {
			std::cout << doc.ErrorDesc() << std::endl;
			std::string errorMessage = doc.ErrorDesc();
			errorMessage += " " + filename;
			throw(Exception(errorMessage));
		}

		TiXmlElement* CFG = doc.FirstChildElement();

		if(CFG == NULL) {
			std::cout << "Failed to load file: No root element." << std::endl;
			doc.Clear();
			exit(EXIT_FAILURE);
		}

		for(TiXmlElement* g = CFG->FirstChildElement(); g != NULL; g = g->NextSiblingElement()) {
			std::string gPart = g->Value();
			if (gPart == "variables") {
				parseVariables(g);
			}
			else if (gPart == "terminals") {
				parseTerminals(g);
			}
			else if (gPart == "rules") {
				parseRules(g);
			}
			else if (gPart == "start") {
				parseStart(g);
			}
			else {
				// Invalid CFG
				doc.Clear();
				exit(EXIT_FAILURE);
			}
		}
	}
	catch (Exception &e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
}

CFGParser::~CFGParser() {
	// TODO Auto-generated destructor stub
}

void CFGParser::parseVariables(TiXmlElement* g) {
	for (TiXmlElement* var = g->FirstChildElement(); var != NULL; var = var->NextSiblingElement()) {
		std::string fieldName = var->Value();
		if(fieldName == "var") {
			 TiXmlText* text = var->FirstChild()->ToText();
			 if (text == NULL) {
				 continue;
			 }
			 variables.push_back(text->Value());
		}
	}
}

void CFGParser::parseTerminals(TiXmlElement* g) {
	for (TiXmlElement* ter = g->FirstChildElement(); ter != NULL; ter = ter->NextSiblingElement()) {
		std::string fieldName = ter->Value();
		if(fieldName == "t") {
			 TiXmlText* text = ter->FirstChild()->ToText();
			 if (text == NULL) {
				 continue;
			 }
			 terminals.push_back(text->Value());
		}
	}
}

void CFGParser::parseRules(TiXmlElement* g) {
	for (TiXmlElement* r = g->FirstChildElement(); r != NULL; r = r->NextSiblingElement()) {
		std::string fieldName = r->Value();
		if(fieldName == "r") {
			 std::string head = r->Attribute("var");
			 std::string body = r->Attribute("body");
			 if (body == "empty") body = "";
			 rules[head].push_back(body);
		}
	}
}

void CFGParser::parseStart(TiXmlElement* g) {
	TiXmlText* text = g->FirstChild()->ToText();
	startSymbol = text->Value();
}

std::vector<std::string> CFGParser::getVariables() const {
	return variables;
}

std::vector<std::string> CFGParser::getTerminals() const {
	return terminals;
}

std::map<std::string, std::vector<std::string> > CFGParser::getRules() const {
	return rules;
}

std::string CFGParser::getStart() const {
	return startSymbol;
}

}
