/*
 * Exception.h
 *
 *  Created on: Nov 13, 2013
 *      Author: robin
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception: public std::exception {
public:
	Exception();
	Exception(std::string);
	std::string what();
	~Exception() throw();
private:
	std::string text;
};

#endif /* EXCEPTION_H_ */
