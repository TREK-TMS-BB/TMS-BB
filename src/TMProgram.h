/*
 * TMProgram.h
 *
 *  Created on: Dec 11, 2013
 *      Author: robin
 */

#ifndef TMPROGRAM_H_
#define TMPROGRAM_H_
#include "Information.h"
#include "TMParser.h"
#include <iostream>


namespace TM {

class TMProgram {
public:
	TMProgram();
	TMProgram(std::string filename);
	virtual ~TMProgram();
	//! a function renaming the states to filename_stateName
	void renameStates();
	friend std::ostream& operator<<(std::ostream& out,const TMProgram &p);
private:
	std::string filename_;					//! the name of the file the program came from
	std::vector<StateName> states_;			//! vector containing all states
	std::vector<Production> productions_;	//! vector with all productions
};

} /* namespace TM */

#endif /* TMPROGRAM_H_ */
