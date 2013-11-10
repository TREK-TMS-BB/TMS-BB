/*
 * CFG.h
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "CYKTable.h"

#ifndef CFG_H_
#define CFG_H_


class CFG {
public:
	/*
	 * Constructs a default CFG with no Rules, 1 Variable : S (= start symbol) and no terminals
	 */
	CFG();
	/*
	 * Constructs a CFG with the given parameters
	 */
	CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s );
	/*
	 * TODO Constructs a CFG by parsing the description written in the file
	 */
	CFG(std::string file);

	/*
	 * Copy constructor
	 * copies the atributes from copy to this
	 */
	CFG(CFG& copy);

	/*
	 * Transforms a CFG to Chomsky Normal Form:
	 * only has translations of the form:
	 * A → BC or A → a
	 */
	void toCNF();

	std::vector<std::string> getVariables() const;
	std::vector<std::string> getTerminals() const;
	std::map<std::string, std::vector<std::string> > getRules() const;
	std::string getStart() const;

	virtual ~CFG();
protected:
	std::vector<std::string> variables;
	std::vector<std::string> terminals;
	std::map<std::string, std::vector<std::string> > rules;
	std::string startSymbol;
};

class CNF_CFG : public CFG {
public:
	/*
	 * Default constructor:
	 * same as CFG
	 */
	CNF_CFG();

	/*
	 * Create a CNF CFG with given parameters
	 * constructs a CFG and then CNF CFG
	 * Check if the rules are in the right format and throw exception if not.
	 */
	CNF_CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s);

	/*
	 * Create a CNF based on a CFG
	 * Check if the rules are of the right form and throw exception if not
	 */
	CNF_CFG(CFG& cfg);

	/*
	 * Load a CFG from given file
	 */
	CNF_CFG(std::string file);

	/*
	 * Check if a given string w is in the CFG
	 * using the CYK algorythm
	 */
	bool check_string(std::string w);
protected:

	/*
	 * used to check if given string is in CFG
	 */
	CYKTable cyk;

	/*
	 * keeps track of all the strings that have already been checked on this CFG with the CYK algorithm
	 * TODO: integrate CYK in this class
	 */
	// std::map<std::string, bool> checked;
	/*
	 * checks the rules of the CFG to see if they are in CNF form
	 * throws exception if they do not
	 * does nothing when the rules are ok
	 */
	void checkRules();
};

#endif /* CFG_H_ */
