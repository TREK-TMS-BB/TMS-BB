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

/*
 * Contains random useful functions
 */

namespace utilities {
	bool isNumber(std::string);
	std::string charToString(char);
}


#endif /* UTILITIES_H_ */
