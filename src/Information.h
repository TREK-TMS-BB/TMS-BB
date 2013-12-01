/*
 * Information.h
 *
 *  Created on: Nov 24, 2013
 *      Author: robin
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_

/*
 * This .h file contains all typedefs, enumerations, ... needed in the program
 */

#include "Exception.h"
#include "TapeSymbol.h"
#include <tuple>


namespace TM {


	typedef std::string StateName;
	enum Direction {left = 0, right, none};
	typedef std::vector<TapeSymbol> Tape;
	/* Productions are of the form:
	 * (<Current State> , <ReadSymbol>, <WriteSymbol>, <MoveDirection>, <Next State>)
	 */
	typedef std::tuple<StateName, TapeSymbol, TapeSymbol, Direction, StateName> Production;

}

namespace PDA {
	enum PDAType {acceptByEmptyStack, acceptByFinalState};
}

namespace parser {
	enum EAction {shift, reduction, accept, jump, blank, error};
}

namespace Grammar {
	typedef std::vector<std::string> TableEntry;
	typedef std::vector<TableEntry > Collumn;
	typedef std::vector<Collumn > Table;
}


#endif /* INFORMATION_H_ */
