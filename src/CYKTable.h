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
	virtual ~CYKTable();
private:
	Table table;
};

#endif /* CYKTABLE_H_ */
