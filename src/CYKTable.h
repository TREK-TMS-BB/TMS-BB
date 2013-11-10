/*
 * CYKTable.h
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#ifndef CYKTABLE_H_
#define CYKTABLE_H_
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <utility>

typedef std::vector<std::string> TableEntry;
typedef std::vector<TableEntry > Collumn;
typedef std::vector<Collumn > Table;

class CYKTable {
public:
	CYKTable();
	CYKTable(std::string w, std::map<std::string, std::vector<std::string> > &rules);
	/*
	 * access item at column i and row j - i + 1
	 */
	std::vector<std::string> at(unsigned int i, unsigned int j) const;
	virtual ~CYKTable();

	friend std::ostream& operator<<(std::ostream& out, CYKTable& c);
private:
	Table table;
	void add(unsigned int i, unsigned int j, std::string var);
	std::vector<std::pair<std::string, std::string> > calculateCombinations(unsigned int i, unsigned int k, unsigned int j);

};


#endif /* CYKTABLE_H_ */
