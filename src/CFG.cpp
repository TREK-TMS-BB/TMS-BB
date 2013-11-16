/*
 * CFG.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CFG.h"

CFG::CFG() {
	variables_.push_back("S");
	startSymbol_= "S";
}

CFG::CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s )
: variables_(v), terminals_(t), rules_(r), startSymbol_(s)
{
	checkAttributes();
}

CFG::CFG(std::string file){
	CFGParser CFGP(file);
	variables_ = CFGP.getVariables();
	terminals_ = CFGP.getTerminals();
	startSymbol_ = CFGP.getStart();
	rules_ = CFGP.getRules();
	checkAttributes();
}

CFG::CFG(CFG& copy)
{
	variables_ = copy.getVariables();
	terminals_= copy.getTerminals();
	rules_ = copy.getRules();
	startSymbol_ = copy.getStart();
}

void CFG::toCNF(){
	 //TODO: @Erkki: Transform given function to CNF
}
std::vector<std::string> CFG::getVariables() const {
	return variables_;
}
std::vector<std::string> CFG::getTerminals() const {
	return terminals_;
}
std::map<std::string, std::vector<std::string> > CFG::getRules() const {
	return rules_;
}
std::string CFG::getStart() const {
	return startSymbol_;
}

std::ostream& operator<< (std::ostream& out, CFG& c) {
	out << "variables: " << std::endl;
	out << "{ " << c.variables_.at(0);
	for (std::vector<std::string>::iterator it = c.variables_.begin()+1; it != c.variables_.end(); it++)
	{
		out<< ", " << *it;
	}
	out << " }" << std::endl << std::endl;

	out << "terminals: " << std::endl;
	out << "{ " << c.terminals_.at(0);
	for (std::vector<std::string>::iterator it = c.terminals_.begin()+1; it != c.terminals_.end(); it++)
	{
		out<< ", " << *it;
	}
	out << " }" << std::endl << std::endl;

	out << " start symbol: " << c.startSymbol_ << std::endl;

	out << "rules: " << std::endl;
	out << "{ "  << std::endl;
	out << c.rules_.begin()->first << " → ";
	for (std::vector<std::string>::iterator it = c.rules_.begin()->second.begin(); it != c.rules_.begin()->second.end(); it++)
	{
		out << *it << "| ";
	}
	out << std::endl;
	std::map< std::string, std::vector<std::string> >::iterator it = c.rules_.begin();
	it++;
	for ( it ; it != c.rules_.end(); ++it)
	{
		out << it->first << " → ";
		for (std::vector<std::string>::iterator r_it = it->second.begin(); r_it != it->second.end(); r_it++)
		{
			out << *r_it << "| ";
		}
		out << std::endl;
	}
	out << "}" << std::endl << std::endl;
	return out;
}

CFG::~CFG() {
}

void CFG::checkAttributes()
{
	/*
	 * Is this a valid CFG?
	 */
	/*
	 * - terminals and variables may not be empty
	 */
	if (variables_.size() == 0)
	{
		throw(Exception("VARIABLES SHOULD NOT BE EMPTY"));
	}
	if (terminals_.size() == 0)
	{
		throw(Exception("TERMINALS SHOULD NOT BE EMPTY"));
	}
	/*
	 * - the startSymbol can be found in variables
	 */
	bool start = false;
	for (std::vector<std::string>::iterator it = variables_.begin(); it != variables_.end(); it++)
	{
		if (*it == startSymbol_)
		{
			start = true;
			break;
		}
	}
	if (start == false)
	{
		throw(Exception("INVALID START SYMBOL"));
	}

	/*
	 * - Variable and terminal vector are fully distinct
	 */

	for (std::vector<std::string>::iterator v_it = variables_.begin(); v_it != variables_.end(); v_it++)
	{
		for (std::vector<std::string>::iterator t_it = terminals_.begin(); t_it != terminals_.end(); t_it++)
		{
			if (*t_it == *v_it)
			{
				std::string errorMess = "TERMINAL " + *t_it + " IS ALSO FOUND IN VARIABLES";
				throw (Exception(errorMess));
			}
		}
	}

	/*
	 * - Left side of rule has to be a variable
	 * - all variables and terminals in rules can also be found in the variables and terminals vector.
	 */

	for (std::map<std::string, std::vector<std::string> >::iterator it = rules_.begin(); it != rules_.end(); it++)
	{
		// Checking Left variable
		bool Lvar = false;
		for (std::vector<std::string>::iterator v_it = variables_.begin(); v_it != variables_.end(); v_it++)
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
			throw (Exception(errorMess));
		}

		// checking right side of rule
		for (std::vector<std::string>::iterator r_it = it->second.begin(); r_it != it->second.end(); r_it++)
		{
			bool Rvar = false;
			// check for variables
			for (std::vector<std::string>::iterator v_it = variables_.begin(); v_it != variables_.end(); v_it++)
			{
				if (it->first == *v_it)
				{
					Rvar = true;
					break;
				}
			}
			// check for terminals
			for (std::vector<std::string>::iterator t_it = terminals_.begin(); t_it != terminals_.end(); t_it++)
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
				throw (Exception(errorMess));
			}
		}
	}
	/*
	 * - all variables have a replacement rule
	 */
	std::map<std::string , int> ruleMatched;	// second gives the nr of rules for certain variable
	for (std::vector<std::string>::iterator it = variables_.begin(); it != variables_.end(); it++)
	{
		ruleMatched[*it]=0;
	}
	for (std::map<std::string, std::vector<std::string> >::iterator it = rules_.begin(); it != rules_.end(); it++)
	{
		ruleMatched[it->first] = it->second.size();
	}
	for (std::vector<std::string>::iterator it = variables_.begin(); it != variables_.end(); it++)
	{
		if (ruleMatched[*it] == 0)
		{
			std::string errorMess = "VARIABLE " + *it + " HAS NO MATCHING RULE";
			throw(Exception(errorMess));
		}
	}
}

CNF_CFG::CNF_CFG() : CFG() {}

CNF_CFG::CNF_CFG(std::vector<std::string> &v, std::vector<std::string> &t, std::map<std::string, std::vector<std::string> > &r, std::string s) : CFG(v, t, r, s), cyk_(rules_, startSymbol_)
{
	checkRules();
}

CNF_CFG::CNF_CFG(CFG& cfg) : CFG(cfg), cyk_(rules_, startSymbol_)
{
	checkRules();
}

CNF_CFG::CNF_CFG(std::string file) : CFG(file), cyk_(rules_, startSymbol_)
{
	CFGParser CFGP(file);
	variables_ = CFGP.getVariables();
	terminals_ = CFGP.getTerminals();
	startSymbol_ = CFGP.getStart();
	rules_ = CFGP.getRules();
	checkRules();
}

void CNF_CFG::checkRules() {
	/*
	 * Check if rules are of the correct form:
	 */

	for (std::map<std::string, std::vector<std::string> >::iterator r_it = rules_.begin(); r_it != rules_.end(); r_it++)
	{
		if (r_it->second.size() == 1)
		{
			bool ter = false;
			for (std::vector<std::string>::iterator t_it = terminals_.begin(); t_it != terminals_.end(); t_it++)
			{
				if (r_it->second.at(0) == *t_it)
				{
					ter = true;
					break;
				}
			}
			if (ter == false)
			{
				std::string errorMessage = "Because in rule " + r_it->first + " → " + r_it->second.at(0) + " WHERE "+ r_it->second.at(0) + "IS NOT A TERMINAL. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (Exception(errorMessage));
			}
		}
		else if (r_it->second.size() == 2)
		{
			bool r1 = false;
			bool r2 = false;
			for (std::vector<std::string>::iterator v_it = variables_.begin(); v_it != variables_.end(); v_it++)
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
				std::string errorMessage = "Because in rule " + r_it->first + " → " + r_it->second.at(0)+r_it->second.at(1) + " WHERE "+ r_it->second.at(0) + " AND " +r_it->second.at(1) + "ARE NO VARIABLEs. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (Exception(errorMessage));
			}
			else if (r1 == false)
			{
				std::string errorMessage = "Because in rule " + r_it->first + " → " + r_it->second.at(0) +r_it->second.at(1)+ " WHERE "+ r_it->second.at(0) + "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (Exception(errorMessage));
			}
			else if (r2 == false)
			{
				std::string errorMessage = "Because in rule " + r_it->first + " → " + r_it->second.at(0) +r_it->second.at(1)+ " WHERE "+ r_it->second.at(1) + "IS NOT A VARIABLE. \n THIS CFG IS NOT IN CHOMSKY NORMAL FORM";
				throw (Exception(errorMessage));
			}
		}
	}
}

bool CNF_CFG::check_string(std::string w)
{
	return cyk_(w);
}
