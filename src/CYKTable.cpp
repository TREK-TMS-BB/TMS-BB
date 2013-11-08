/*
 * CYKTable.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CYKTable.h"

CYKTable::CYKTable() {
	Collumn tC1, tC2, tC3;

	std::vector<std::string> temp2;

	temp2.push_back("A");
	temp2.push_back("B");
	temp2.push_back("C");

	tC1.push_back(temp2);
	tC2.push_back(temp2);
	tC2.push_back(temp2);
	tC3.push_back(temp2);
	tC3.push_back(temp2);
	tC3.push_back(temp2);
	table.push_back(tC1);
	table.push_back(tC2);
	table.push_back(tC3);
}

CYKTable::~CYKTable() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& out, CYKTable& c) {
	for (int row = 0; row < c.table.size(); row++)
	{
		for (int collumn = 0; collumn < c.table.at(row).size(); collumn++)
		{
			out << "{";
			for (int var = 0; var < c.table.at(row).at(collumn).size(); var++)
			{
				out << c.table.at(row).at(collumn).at(var) << ", ";
			}
			out << "}" << "\t";
		}
		out << std::endl;
	}
	return out;
}

std::vector<std::string> CYKTable::at(unsigned int i, unsigned int j) const{
	int collumn = i-1;
	int row = (j-i);

	if (row >= table.size())
	{
		throw ("ARGUMENT J IS OUT OF BOUNDS");
	}
	else if (collumn >= table.at(row).size())
	{
		throw ("ARGUMENT I IS OUT OF BOUNDS");
	}
	return table.at(row).at(collumn);
}
