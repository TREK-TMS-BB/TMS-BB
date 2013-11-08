/*
 * CYKTable.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CYKTable.h"

CYKTable::CYKTable() {
	Collumn temp;
	std::vector<std::string> temp2;

	temp2.push_back("A");
	temp.push_back(temp2);
	temp2.push_back("B");
	temp.push_back(temp2);
	temp2.push_back("C");
	temp.push_back(temp2);
}

CYKTable::~CYKTable() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& out, CYKTable& c) {
	for (Table::iterator it = c.table.begin(); it != c.table.end(); it++)
	{
		for (Collumn::iterator c_it = it->begin(); c_it != it->end(); c_it++ )
		{
			out << "{";
			for (TableEntry::iterator e_it = c_it->begin(); e_it != c_it->end(); e_it++)
			{
				out << *e_it << ", ";
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
