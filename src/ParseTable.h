/*
 * ParseTable.h
 *
 *  Created on: Nov 8, 2013
 *      Author: kristof
 */

#ifndef PARSETABLE_H_
#define PARSETABLE_H_

#include <vector>
#include <string>
#include <utility>

#include "CFG.h"

enum EAction {shift, reduction, blank};

class ParseTable {
public:
	ParseTable();
	// Default constructor. Our parsetable will be empty as it has no CFG.

	ParseTable(CFG);
	// Our parsetable will be constructed using the CFG provided as parameter.

	std::pair<EAction, std::string> operator() (int, std::string) const;
	// Returns the contents of the parse table (and what action should happen) depending on the input.

	virtual ~ParseTable();

private:
	std::vector<std::vector<std::string> > table;
};

#endif /* PARSETABLE_H_ */