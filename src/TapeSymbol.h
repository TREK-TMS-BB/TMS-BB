/*
 * TapeSymbol.h
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#ifndef TAPESYMBOL_H_
#define TAPESYMBOL_H_

#include <iostream>
#include <string>
#include "Exception.h"

namespace TM {
enum Type {integer = 0, character, blank};

class TapeSymbol {
public:
	//! Default constructor: makes a blank TapeSymbol
	TapeSymbol();
	//! Constructor making an int TapeSymbol
	TapeSymbol(unsigned int i );
	//! Constructor making a character TapeSymbol
	TapeSymbol(std::string c);
	//! Assignment operator
	TapeSymbol& operator=(const TapeSymbol& ts) ;
	//! Comparison operator
	friend bool operator==(TapeSymbol t, TapeSymbol ts) ;
	//! output operator
	friend std::ostream& operator<< (std::ostream& out, TapeSymbol& ts);

private:
	unsigned int integer_;		//! integer value;
	std::string character_; 	//! character value
	Type select_;				//! selects which value will be used, if blank -> use blank symbol
};

} /* namespace TM */

#endif /* TAPESYMBOL_H_ */
