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
#include "Exception.h"

typedef std::vector<std::string> TableEntry;
typedef std::vector<TableEntry > Collumn;
typedef std::vector<Collumn > Table;

class CYKTable {
public:
	CYKTable();
	/*
	 * sets up the rules and Start symbol but does not yet construct a table
	 */
	CYKTable(std::map<std::string, std::vector<std::string> > &r, std::string startSymbol);

	/*
	 * Constructs the CYKTable for a given string and given rules
	 */
	CYKTable(std::string w, std::map<std::string, std::vector<std::string> > &r, std::string stS);

	/*
	 * creates the table for given string w
	 * returns true if given for given string w the top of the triangle contains the startSymbol
	 */
	bool operator()(std::string w);
	/*
	 * access item at column i and row j - i + 1
	 */
	std::vector<std::string> at(unsigned int i, unsigned int j) const;
	virtual ~CYKTable();

	friend std::ostream& operator<<(std::ostream& out, CYKTable& c);
private:
	/*
	 * Table in which the information is stored
	 */
	Table table;

	/*
	 * used to create the table
	 */
	std::map<std::string, std::vector<std::string> > rules;

	std::string startSymbol;

	/*
	 * create table for given string
	 * Used in constructor and operator()
	 */
	void createTable(std::string w);

	/*
	 * Add a new variable to given position in table
	 * i an j are not actual coordinates, but CYK table coordinates
	 */
	void add(unsigned int i, unsigned int j, std::string var);
	/*
	 * Calculates all possible pairs of variables between 2 positions in the table
	 * used in the constructor
	 */
	std::vector<std::pair<std::string, std::string> > calculateCombinations(unsigned int i, unsigned int k, unsigned int j);

};


#endif /* CYKTABLE_H_ */
