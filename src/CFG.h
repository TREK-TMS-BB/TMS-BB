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

	/*
	 * Constructs a default CFG with no Rules, 1 Variable : S (= start symbol) and no terminals
	 */
	CFG();
	/*
	 * Constructs a CFG with the given parameters
	 */
	CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string>> &r, std::string s );
	/*
	 * TODO Constructs a CFG by parsing the description written in the file
	 */
	CFG(std::string file);
	virtual ~CFG();
private:
	std::vector<std::string> variables;
	std::vector<std::string> terminals;
	std::map<std::string, std::vector<std::string>> rules;
	std::string startSymbol;

};

#endif /* CFG_H_ */
