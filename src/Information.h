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


namespace TM {

enum Type {integer = 0, character, blank};

class TapeSymbol {
public:
	TapeSymbol() : integer_(0), character_(""), select_(blank) {}
	TapeSymbol(unsigned int i ) : integer_(i), character_(""), select_(integer) {}
	TapeSymbol(std::string c) : integer_(0), character_(c), select_(character) {
		if (c.size() != 1) {
			throw(Exception("TAPESYMBOL EXPECTS SINGLE CHARACTER"));
		}
	}
	TapeSymbol& operator=(const TapeSymbol& ts) {
		select_ = ts.select_;
		character_ = ts.character_;
		integer_ = ts.integer_;
		return *this;
	}
	/*TapeSymbol& operator=(std::string& c) {
		if (c.size() != 1) {
			throw(Exception("TAPESYMBOL EXPECTS SINGLE CHARACTER"));
		}
		character_=c;
		select_ = character;
		return *this;
	}
	TapeSymbol& operator= (int& i) {
		integer_ = i;
		select_ = integer;
		return *this;
	}*/

	/*friend bool operator==(TapeSymbol& ts, int& i) {
		switch ( ts.select_) {
		case integer:
			if (ts.integer_ == i) {
				return true;
			}
			else return false;
		}
		return false;
	}
	friend bool operator==(TapeSymbol& ts, std::string& c) {
		if (c.size() != 1) {
			throw(Exception("TAPESYMBOL EXPECTS SINGLE CHARACTER"));
		}
		switch ( ts.select_) {
		case character:
			if (ts.character_ == c) {
				return true;
			}
			else return false;
		}
		return false;
	}*/

	friend bool operator==(TapeSymbol t, TapeSymbol ts) {
		if (t.select_ != ts.select_) {
			return false;
		}
		else switch (t.select_) {
		case integer:
			return (ts.integer_ == t.integer_);
		case character:
			return (ts.character_ == t.character_);
		case blank:
			return true;
		}
	}

	friend std::ostream& operator<< (std::ostream& out, TapeSymbol& ts) {
		switch(ts.select_) {
		case integer:
			out<<ts.integer_;
			break;
		case character:
			out << ts.character_;
			break;
		case blank:
			out << '_';
			break;
		}
		return out;
	}

private:
	unsigned int integer_;		//! integer value;
	std::string character_; 	//! character value
	Type select_;				//! selects which value will be used, if blank -> use blank symbol
};

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
