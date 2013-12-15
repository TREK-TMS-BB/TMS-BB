/*
 * BBParser.h
 *
 *  Created on: Dec 12, 2013
 *      Author: kristof
 */

#ifndef BBPARSER_H_
#define BBPARSER_H_

#include <cctype>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <map>
#include "Parser.h"
#include "BareBonesProgram.h"
#include "BareBonesStatement.h"
#include "utilities.h"


namespace parser {

class BBParser : public Parser{
public:
	BBParser();
	virtual ~BBParser();

	BB::BareBonesProgram parseBB(std::string);

private:
	std::vector<std::shared_ptr<BB::BareBonesStatement> > statements_;
	std::stack<std::pair<std::vector<std::shared_ptr<BB::BareBonesStatement> >, int> > whileStack_;
	std::map<std::string, int> varMap_;

	int readVar(std::string::iterator&);


};

} /* namespace parser */

#endif /* BBPARSER_H_ */
