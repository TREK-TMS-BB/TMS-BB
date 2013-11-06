/*
 * CFG.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CFG.h"

CFG::CFG() {
	variables.push_back("S");
	startSymbol= "S";
}

CFG::CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s )
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

	for (std::map<std::string, std::vector<std::string> >::iterator it = rules.begin(); it != rules.end(); it++)
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

CFG::CFG(std::string file){
	//TODO: Read File and construct the parameters
}

CFG::CFG(CFG& copy)
: variables(copy.variables), terminals(copy.terminals), rules(copy.terminals), startSymbol(copy.startSymbol)
{}

void CFG::toCNF(){
	 //TODO: @Erkki: Transform given function to CNF
}

CFG::~CFG() {
}


CNF_CFG::CNF_CFG() : CFG() {}

CNF_CFG::CNF_CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s) : CFG(v, t, r, s)
{
	/*
	 * Check if rules are of the correct form:
	 */

	for (std::map<std::string, std::vector<std::string> >::iterator r_it = rules.begin(); r_it != rules.end(); r_it++)
	{
		if (r_it->second.size() == 1)
		{
			bool ter = false;
			for (std::vector<std::string>::iterator t_it = terminals.begin(); t_it != terminals.end(); t_it++)
			{
				if (r_it->second.at(0) == *t_it)
				{
					ter = true;
					break;
				}
			}
			if (ter == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) << " WHERE "<< r_it->second.at(0) << "IS NOT A TERMINAL. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
		}
		else if (r_it->second.size() == 2)
		{
			bool r1 = false;
			bool r2 = false;
			for (std::vector<std::string>::iterator v_it = variables.begin(); v_it != variables.end(); v_it++)
			{
				if (r_it->second.at(0) == *v_it)
				{
					r1 = true;
				}
				else if (r_it->second.at(1) == *v_it)
				{
					r2 = true;
				}
				if ((r1 == true) && (r2 == true))
				{
					break;
				}
			}
			if ((r1 == false) && (r2 == false))
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0)<<r_it->second.at(1) << " WHERE "<< r_it->second.at(0) << " AND " <<r_it->second.at(1) << "ARE NO VARIABLEs. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
			else if (r1 == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) <<r_it->second.at(1)<< " WHERE "<< r_it->second.at(0) << "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
			else if (r2 == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) <<r_it->second.at(1)<< " WHERE "<< r_it->second.at(1) << "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
		}
	}
}

CNF_CFG::CNF_CFG(CFG& cfg) : CFG(cfg)
{
	/*
	 * Check if rules are of the correct form:
	 */

	for (std::map<std::string, std::vector<std::string> >::iterator r_it = rules.begin(); r_it != rules.end(); r_it++)
	{
		if (r_it->second.size() == 1)
		{
			bool ter = false;
			for (std::vector<std::string>::iterator t_it = terminals.begin(); t_it != terminals.end(); t_it++)
			{
				if (r_it->second.at(0) == *t_it)
				{
					ter = true;
					break;
				}
			}
			if (ter == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) << " WHERE "<< r_it->second.at(0) << "IS NOT A TERMINAL. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
		}
		else if (r_it->second.size() == 2)
		{
			bool r1 = false;
			bool r2 = false;
			for (std::vector<std::string>::iterator v_it = variables.begin(); v_it != variables.end(); v_it++)
			{
				if (r_it->second.at(0) == *v_it)
				{
					r1 = true;
				}
				else if (r_it->second.at(1) == *v_it)
				{
					r2 = true;
				}
				if ((r1 == true) && (r2 == true))
				{
					break;
				}
			}
			if ((r1 == false) && (r2 == false))
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0)<<r_it->second.at(1) << " WHERE "<< r_it->second.at(0) << " AND " <<r_it->second.at(1) << "ARE NO VARIABLEs. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
			else if (r1 == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) <<r_it->second.at(1)<< " WHERE "<< r_it->second.at(0) << "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
			else if (r2 == false)
			{
				std::string errorMessage = "Because in rule " << r_it->first << " → " << r_it->second.at(0) <<r_it->second.at(1)<< " WHERE "<< r_it->second.at(1) << "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (errorMessage);
			}
		}
	}
}

