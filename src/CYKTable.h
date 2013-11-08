/*
 * CYKTable.h
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#ifndef CYKTABLE_H_
#define CYKTABLE_H_

#include <vector>
#include <iostream>

typedef std::vector<std::string> TableEntry;
typedef std::vector<TableEntry > Collumn;
typedef std::vector<Collumn > Table;

class CYKTable {
public:
	CYKTable();
	/*
	 * access item at column i and row j - i + 1
	 */
	std::vector<std::string> at(unsigned int i, unsigned int j) const;
	virtual ~CYKTable();

	friend std::ostream& operator<<(std::ostream& out, CYKTable& c);
private:
	Table table;
};


#endif /* CYKTABLE_H_ */
