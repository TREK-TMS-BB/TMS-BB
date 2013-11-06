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
	 * Check if the rules are in the right format
	 */
	CNF_CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s);

	/*
	 * Create a CNF based on a CFG
	 * TODO: 2 Options:
	 * 		→ Check if the rules are of the right form and throw exception if not
	 * 		→ Check if the rules are of the right form and run toCNF on cfg and make CNF CFG
	 */
	CNF_CFG(CFG& cfg);

	/*
	 * Check if a given string w is in the CFG
	 * using the CYK algorythm
	 */
	bool check_string(std::string w);
protected:
	std::map<std::string, bool> checked;	// keeps track of all the strings that have already been checked on this CFG
	bool checkRules();
};

#endif /* CFG_H_ */
