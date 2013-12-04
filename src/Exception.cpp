/*
 * Exception.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: robin
 */

#include "Exception.h"

Exception::Exception() {
	text_ = "An exception without any info has been thrown.";
}
Exception::Exception(std::string s) {
	text_ = s;
}
std::string Exception::what() {
	return text_;
}
Exception::~Exception() throw() {

}
