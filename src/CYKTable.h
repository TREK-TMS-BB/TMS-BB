/*
 * CYKTable.h
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#ifndef CYKTABLE_H_
#define CYKTABLE_H_

#include <vector>
typedef std::vector<std::vector<std::vector<std::string> > > Table;
class CYKTable {
public:
	CYKTable();
	/*
	 * access item at column i and row j - i + 1
	 */
	std::vector<std::string> at(int i, int j);
	virtual ~CYKTable();
private:
	Table table;
};

#endif /* CYKTABLE_H_ */
