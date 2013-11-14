/*
 * Exception.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: robin
 */

#include "Exception.h"

Exception::Exception() {
	text_ = "exception thrown without parameters";
}
Exception::Exception(std::string s) {
	text_ = s;
}
std::string Exception::what() {
	return text_;
}
Exception::~Exception() throw() {

}
