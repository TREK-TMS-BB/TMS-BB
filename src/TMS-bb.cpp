//============================================================================
// Name        : TMS-bb.cpp
// Author      : TREK
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CYKTable.h"
#include "CFG.h"
int main() {
	std::cout << "This is going to be awesome! Haha. Test #3" << std::endl;
	std::map<std::string, std::vector<std::string> > rules;
	std::vector<std::string> temp;
	temp.push_back("a");
	rules["A"] = temp;
	rules["B"].push_back("AA");
	rules["C"].push_back("AB");
	rules["D"].push_back("AA");
	CYKTable c( rules, "C");
	std::cout << c("aaaa") << std::endl;
	return 0;
}
