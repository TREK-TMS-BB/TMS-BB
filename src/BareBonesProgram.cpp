/*
 * BareBonesProgram.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#include "BareBonesProgram.h"

namespace BB {

BareBonesProgram::BareBonesProgram(std::vector<std::shared_ptr<BareBonesStatement> > statements)
	: statements_(statements)
{}

BareBonesProgram::~BareBonesProgram() {
	// TODO Auto-generated destructor stub
}

} /* namespace BB */
