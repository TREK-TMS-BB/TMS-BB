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
#include "Information.h"


namespace Grammar {

class CYKTable {
public:
	//! default constructor
	CYKTable();

	//! specified constructor
	/*
	 * sets up the rules and Start symbol but does not yet construct a table
	 */
	/**
	 * @param r map of rules
	 * @param startSymbol the start symbol
	 */
	CYKTable(std::map<std::string, std::vector<std::string> > &r, std::string startSymbol);

	//! specified constructor (used for testing)
	/*
	 * Constructs the CYKTable for a given string and given rules
	 * mostly used for testing
	 */
	/**
	 * @param w string that will be checked
	 * @param r map of rules
	 * @param startSymbol the start symbol
	 */
	CYKTable(std::string w, std::map<std::string, std::vector<std::string> > &r, std::string stS);

	//! A function to check a string
	/*
	 * creates the table for given string w
	 * returns true if given for given string w the top of the triangle contains the startSymbol
	 */
	/**
	 * @param w A string with which the table will be constructed
	 * @return true if string is in CFG, false if not
	 */
	bool operator()(std::string w);

	//! a function return vector of variables on given position (in CYK coordinates)
	/*
	 * access item at column i and row j - i + 1
	 */
	/**
	 * @param i Nr of the collumn
	 * @param j Nr of row + i
	 */
	std::vector<std::string> at(unsigned int i, unsigned int j) const;
	virtual ~CYKTable();

	friend std::ostream& operator<<(std::ostream& out, const CYKTable& c);

	std::map<std::string, std::vector<std::string> > getRules() const;
	std::string getStartSymbol() const;
	Table getTable() const;

private:
	Table table_; //! Table in which the information is stored

	std::map<std::string, std::vector<std::string> > rules_; // map with rules used to create table

	std::string startSymbol_;

	//! Function creating table for given string
	//Used in constructor and operator()
	void createTable(std::string w);


	 //! Function adding a new variable to given position in table
	/**
	 * @param i Nr of the collumn
	 * @param j Nr of row + i
	 */
	void add(unsigned int i, unsigned int j, std::string var);

	//! Function calculating all possible pairs of variables between 2 positions in the table
	/*
	 * used in the constructor
	 */
	/**
	 *
	 * @param i Nr of the collumn for 1st position
	 * @param k Nr of row + i for 1st el, Nr of collumn for 2nd position
	 * @param j Nr of row + k for 2nd position
	 * @return Vector of all pairs with combinations of variables from the 2 positions
	 */

	std::vector<std::pair<std::string, std::string> > calculateCombinations(unsigned int i, unsigned int k, unsigned int j);

};
} /* namespace Grammar */

#endif /* CYKTABLE_H_ */
