/*
 * Exception.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: robin
 */

#include "Exception.h"

Exception::Exception() {
	text = "exception thrown without parameters";
}
Exception::Exception(std::string s) {
	text = s;
}
std::string Exception::what() {
	return text;
}
Exception::~Exception() throw() {

}
