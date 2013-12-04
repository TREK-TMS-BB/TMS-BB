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
#include "Parser.h"
#include "Exception.h"
#include <sstream>

#ifndef CFG_H_
#define CFG_H_

namespace Grammar  {

class CFG {
public:
	//! Default constructor
	/*
	 * Constructs a default CFG with no Rules, 1 Variable : S (= start symbol) and no terminals
	 */
	CFG();
	//! specified constructor
	/**
	 * @param v vector with variables
	 * @param t vector with terminals
	 * @param r map with rules of the form <Variable>, vector<terminals,Variables>
	 * @param s the start symbol for the CFG
	 */
	/*
	 * Constructs a CFG with the given parameters
	 */
	CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s );
	//! Constructor from a given file
	/**
	 * @param file the path to a file where the CFG is described
	 */
	/*
	 * Constructs a CFG by parsing the description written in the file
	 */
	CFG(std::string file);

	//! Copy constructor
	/**
	 * @param copy a CFG object which is going to be copied
	 */
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

	//! output operator
	/*
	 * Prints out the variables, terminals, startSymbol and rules of given CFG
	 */
	friend std::ostream& operator<< (std::ostream& out, CFG& c);

	std::vector<std::string> getVariables() const;
	std::vector<std::string> getTerminals() const;
	std::map<std::string, std::vector<std::string> > getRules() const;
	std::string getStart() const;

	virtual ~CFG();
protected:
	std::vector<std::string> variables_;	//! vector with the variables of the CFG
	std::vector<std::string> terminals_;	//! vector with the terminals of the CFG
	std::map<std::string, std::vector<std::string> > rules_;	//! a map with all the rules. rules are of the form <Variable>, vector<Variables, terminals>
	std::string startSymbol_;	//! the start symbol of the CFG

	//!checks whether all attributes are ok
	/* - the StartSymbol can be found in variables
	 * - variable and terminal vector are fully distinct
	 * - left side of a rule has to be a variable
	 * - variables and terminals in the right side have to be found in corresponding vectors
	 * - All variables have a replacement rule
	 */
	void checkAttributes();
};

class CNF_CFG : public CFG {
public:
	//! Default constructor
	/*
	 * Default constructor:
	 * same as CFG
	 */
	CNF_CFG();

	//! specified constructor
	/**
	 * @param v vector with variables
	 * @param t vector with terminals
	 * @param r map with rules of the form <Variable>, vector<terminals,Variables>
	 * @param s the start symbol for the CFG
	 */
	/*
	 * Create a CNF CFG with given parameters
	 * constructs a CFG and then CNF CFG
	 * Check if the rules are in the right format and throw exception if not.
	 */
	CNF_CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s);

	//! constructor based on a CFG and copy constructor
	/**
	 * @param cfg a CFG that is in CNF form or a CNF_CFG
	 */
	/*
	 * Create a CNF based on a CFG
	 * Check if the rules are of the right form and throw exception if not
	 */
	CNF_CFG(CFG& cfg);

	//! constructor with information file
	/*
	 * Load a CFG from given file
	 */
	CNF_CFG(std::string file);

	//! checks if given string is in the CNF_CFG
	/**
	 * @param w string to check
	 * @return bool : true if in language, false if not in language
	 */
	/*
	 * Check if a given string w is in the CFG
	 * 1st check if the string has already been checked
	 * 2nd using the CYK algorythm
	 */
	bool check_string(std::string w);
	//! function used for testing
	/**
	 * @param w string to check
	 * @return bool : true if already checked, false if not in language
	 */
	/*
	 * returns true if given string has already been checked;
	 */
	bool already_checked(std::string w);

	const CYKTable& getCYK() const;
protected:

	CYKTable cyk_;	//! used to check if given string is in CFG

	 std::map<std::string, bool> checked; 	 //! map keeps track of all the strings that have already been checked on this CFG with the CYK algorithm

	//!checks the rules of the CFG to see if they are in CNF form
	/* throws exception if they do not
	 * does nothing when the rules are ok
	 */
	void checkRules();
};

} /* namespace Grammar */

#endif /* CFG_H_ */
