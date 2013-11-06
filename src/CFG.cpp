/*
 * CFG.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CFG.h"

CFG::CFG() : variables("S"), startSymbol("S") {

}

CFG::CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string>> &r, std::string s )
: variables(v), terminals(t), rules(r), startSymbol(s)
{
	/*
	 * Is this a valid CFG?
	 * the startSymbol can be found in variables
	 */
	bool start = false;
	for (std::vector<std::string>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		if (*it == s)
		{
			start = true;
			break;
		}
	}
	if (start == true)
	{
		throw("INVALID START SYMBOL");
	}

	/*
	 * Variable and terminal vector are fully distinct
	 */

	for (std::vector<std::string>::iterator v_it = variables.begin(); v_it != variables.end(); v_it++)
	{
		for (std::vector<std::string>::iterator t_it = terminals.begin(); t_it != terminals.end(); t_it++)
		{
			if (*t_it == *v_it)
			{
				std::string errorMess = "TERMINAL " + *t_it + " IS ALSO FOUND IN VARIABLES";
				throw (errorMess);
			}
		}
	}

	/*
	 * Left side of rule has to be a variable
	 * all variables and terminals in rules can also be found in the variables and terminals vector.
	 */

	for (std::map<std::string, std::vector<std::string>>::iterator it = rules.begin(); it != rules.end(); it++)
	{
		// Checking Left variable
		bool Lvar = false;
		for (std::vector<std::string>::iterator v_it = variables.begin(); v_it != variables.end(); v_it++)
		{
			if (it->first == *v_it)
			{
				Lvar = true;
				break;
			}
		}
		if (Lvar == false)
		{
			std::string errorMess = "SYMBOL " + it->first + " NOT FOUND IN VARIABLES VECTOR";
			throw (errorMess);
		}

		// checking right side of rule
		for (std::vector<std::string>::iterator r_it = it->second.begin(); r_it != it->second.end(); r_it++)
		{
			bool Rvar = false;
			// check for variables
			for (std::vector<std::string>::iterator v_it = variables.begin(); v_it != variables.end(); v_it++)
			{
				if (it->first == *v_it)
				{
					Rvar = true;
					break;
				}
			}
			// check for terminals
			for (std::vector<std::string>::iterator t_it = terminals.begin(); t_it != terminals.end(); t_it++)
			{
				if (it->first == *t_it)
				{
					Rvar = true;
					break;
				}
			}
			if (Rvar == false)
			{
				std::string errorMess = "SYMBOL " + it->first + " NOT FOUND IN VARIABLES NOR TERMINALS VECTOR";
				throw (errorMess);
			}
		}
	}


}

CFG::~CFG() {
}

