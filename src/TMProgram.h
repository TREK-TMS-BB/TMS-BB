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
	TMProgram(	std::vector<StateName> states, std::vector<Production> productions, std::string filename);

	virtual ~TMProgram();
	std::string getStart();
	friend std::ostream& operator<<(std::ostream& out,const TMProgram &p);
	friend void renameStates(std::string, std::string);
	friend void linkFiles(std::string, std::string, std::string);
	friend void linkFiles(std::vector<std::string>, std::string);
	//! a function renaming the states to filename_stateName
	void renameStates();
	//! a function linking the program to the next (expecting all names of states to be different)
	/**
	 * @param halt if true halt states is added in the end else it is skipped
	 */
	void linkWith(const TMProgram& prog, bool halt = true);
	//! a function linking the program to a vector of programs
	/**
	 * @param halt if true halt states is added in the end else it is skipped
	 */
	void linkWith(std::vector<TMProgram>const & progs, bool halt = true);
	//! a function adding a state on the before last place
	void addState(StateName);
	//! a function adding a Production
	void addProduction(Production const &);
private:

	std::string filename_;					//! the name of the file the program came from
	std::vector<StateName> states_;			//! vector containing all states
	std::vector<Production> productions_;	//! vector with all productions
};

} /* namespace TM */

#endif /* TMPROGRAM_H_ */
