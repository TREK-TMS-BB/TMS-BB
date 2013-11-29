/*
 * TapeSymbol.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#include "TapeSymbol.h"

namespace TM {

TapeSymbol::TapeSymbol() : integer_(0), character_(""), select_(blank) {}

TapeSymbol::TapeSymbol(unsigned int i ) : integer_(i), character_(""), select_(integer) {}

TapeSymbol::TapeSymbol(std::string c) : integer_(0), character_(c), select_(character) {
	if (c.size() != 1) {
		throw(Exception("TAPESYMBOL EXPECTS SINGLE CHARACTER"));
	}
}

TapeSymbol& TapeSymbol::operator=(const TapeSymbol& ts) {
	select_ = ts.select_;
	character_ = ts.character_;
	integer_ = ts.integer_;
	return *this;
}

bool operator==(TapeSymbol t, TapeSymbol ts) {
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

std::ostream& operator<< (std::ostream& out, TapeSymbol& ts) {
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


} /* namespace TM */
