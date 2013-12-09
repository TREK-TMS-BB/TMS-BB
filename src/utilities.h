/*
 * utilities.h
 *
 *  Created on: Nov 15, 2013
 *      Author: kristof
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cctype>
#include <string>
#include <sstream>
#include <locale>
#include <algorithm>

/*
 * Contains random useful functions
 */

namespace utilities {
	bool isNumber(std::string);
	std::string charToString(char);
	std::string lowToUp(std::string);
	std::string upToLow(std::string);
	std::string replacestring(std::string, std::string, std::string);
	std::string nextstring(std::string);
}


#endif /* UTILITIES_H_ */
