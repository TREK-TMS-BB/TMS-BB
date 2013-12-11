/*
 * LinkTM.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: robin
 */

#include "LinkTM.h"

namespace TM {

void renameStates(std::string input, std::string output) {
	TMProgram inputP (input);
	inputP.renameStates();
	std::ofstream out;
	out.open(output);
	out << inputP;
}

void linkFiles(std::string input1, std::string input2, std::string output) {
	TMProgram inputP1 (input1);
	TMProgram inputP2 (input2);
	inputP1.renameStates();
	inputP2.renameStates();

	inputP1.linkWith(inputP2);
	std::ofstream out;
	out.open(output);
	out << inputP1;

}

}


