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

void linkFiles(std::vector<std::string> input, std::string output) {
	try {
		TMProgram p1(input.at(0));
		p1.renameStates();
		input.erase(input.begin());
		std::vector<TMProgram> progs;
		for (auto a : input) {
			TMProgram temp(a);
			temp.renameStates();
			progs.push_back(temp);
		}
		p1.linkWith(progs);
		std::ofstream out;
		out.open(output);
		out << p1;
	}
	catch (std::out_of_range& e) {
		Exception exc("You have to give at least 1 file to link");
		throw exc;
	}

}

}


