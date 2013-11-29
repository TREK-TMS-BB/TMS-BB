/*
 * utilities.cpp
 *
 *  Created on: Nov 15, 2013
 *      Author: kristof
 */

#include "utilities.h"

bool utilities::isNumber(std::string input) {
	for (auto e : input) {
		if (!std::isdigit(e)) {
			return false;
		}
	}
	return true;
}

std::string utilities::charToString(char input) {
	std::stringstream ss;
	ss << input;
	return ss.str();
}

