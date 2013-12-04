/*
 * CYKTable.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: robin
 */

#include "CYKTable.h"

namespace Grammar {

CYKTable::CYKTable():startSymbol_("S") {
}
CYKTable::CYKTable(std::map<std::string, std::vector<std::string> > &r, std::string stS)
: rules_(r), startSymbol_(stS)
{}
CYKTable::CYKTable(std::string w, std::map<std::string, std::vector<std::string> > &r, std::string stS)
: rules_ (r), startSymbol_(stS)
{
	createTable(w);
}

CYKTable::~CYKTable() {
	// TODO Auto-generated destructor stub
}

bool CYKTable::operator() (std::string w)
{
	if (w.size() == 0){
		w = " ";
	}
	createTable(w);
	std::vector<std::string> top = this->at(1, w.size());
	for (int i = 0; i < top.size(); i++)
	{
		if (startSymbol_ == top.at(i))
		{
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const CYKTable& c) {
	for (int row = c.table_.size()-1; row >= 0; row--)
	{
		for (int collumn = 0; collumn < c.table_.at(row).size(); collumn++)
		{
			out << "{";
			if (c.table_.at(row).at(collumn).size() == 0)
			{
				out << " ";
			}
			else if (c.table_.at(row).at(collumn).size() == 1)
			{
				out << c.table_.at(row).at(collumn).at(0);
			}
			else
			{
				out << c.table_.at(row).at(collumn).at(0);
				for (int var = 1; var < c.table_.at(row).at(collumn).size(); var++)
				{
					out << ","<< c.table_.at(row).at(collumn).at(var) ;
				}
			}
			out << "}" << "\t";
		}
		out << std::endl;
	}
	return out;
}

std::map<std::string, std::vector<std::string> > CYKTable::getRules() const {
	return rules_;
}
std::string CYKTable::getStartSymbol() const {
	return startSymbol_;
}

Table CYKTable::getTable() const {
	return table_;
}

std::vector<std::string> CYKTable::at(unsigned int i, unsigned int j) const{
	int collumn = i-1;
	int row = (j-i);

	if (row >= table_.size())
	{
		throw (Exception("ARGUMENT J IS OUT OF BOUNDS"));
	}
	else if (collumn >= table_.at(row).size())
	{
		throw (Exception("ARGUMENT I IS OUT OF BOUNDS"));
	}
	return table_.at(row).at(collumn);
}

void CYKTable::add(unsigned int i, unsigned int j, std::string var) {
	int collumn = i-1;
	int row = (j-i);

	if (row >= table_.size())
	{
		throw (Exception("ARGUMENT J IS OUT OF BOUNDS"));
	}
	else if (collumn >= table_.at(row).size())
	{
		throw (Exception("ARGUMENT I IS OUT OF BOUNDS"));
	}

	/*
	 * check if variable already in the given vector
	 */
	for (std::vector<std::string>::iterator it = this->table_.at(row).at(collumn).begin(); it != this->table_.at(row).at(collumn).end(); it++)
	{
		std::string temp = *it;
		if (var == temp)
		{
			return;
		}
	}
	/*
	 * Add variable to given vector
	 */
	this->table_.at(row).at(collumn).push_back(var);
}

std::vector<std::pair<std::string, std::string> > CYKTable::calculateCombinations(unsigned int i, unsigned int k, unsigned int j) {

	std::vector<std::pair<std::string, std::string> > retVal;

	std::vector<std::string> v_ik = this->at(i,k);
	std::vector<std::string> v_kj = this->at(k+1, j);
	/*
	 * if any of these 2 is empty: return empty vector
	 */
	if (v_ik.size() == 0 || v_kj.size() == 0)
	{
		return retVal;
	}

	for (std::vector<std::string>::iterator it1 = v_ik.begin(); it1 != v_ik.end(); it1++ )
	{
		for (std::vector<std::string>::iterator it2 = v_kj.begin(); it2 != v_kj.end(); it2++)
		{
			std::pair<std::string, std::string> p(*it1, *it2);
			retVal.push_back(p);
		}
	}

	return retVal;
}

void CYKTable::createTable(std::string w)
{
	table_.clear();
	/*
	 * Setup table with empty vectors for size of w
	 */
	int size = w.size();
	std::vector<std::string> temp;
	std::vector<std::vector<std::string> > tempRow;
	for (int i = 0; i< size; i++)
	{
		tempRow.push_back(temp);
	}
	for (int j = 0; j < size ; j++)
	{
		table_.push_back(tempRow);
		tempRow.pop_back();
	}

	/*
	 * Add variables that correspond to characters of w;
	 */
	int count = 1;
	for (std::string::iterator w_it = w.begin(); w_it!= w.end(); w_it++)
	{
		std::stringstream t_temp;
		t_temp << *w_it;
		std::string terminal;
		t_temp >> terminal;
		for (std::map<std::string, std::vector<std::string> >::iterator r_it = rules_.begin(); r_it != rules_.end(); r_it++)
		{
			std::string var = r_it->first;
			for (std::vector<std::string>::iterator it = r_it->second.begin(); it != r_it->second.end(); it++)
			{
				std::string temp = *it;
				if (temp == terminal)
				{
					this->add(count, count, var);
				}
			}
		}
		count++;
	}

	/*
	 * Fill Table
	 */
	for (int row = 1; row < table_.size(); row++)
	{
		for (int collumn = 0; collumn < table_.at(row).size(); collumn++)
		{
			int i = collumn+1;
			int j = row+i;
			/*
			 *	calculate all possibilities
			 *	Xij → Xik Xk+1j
			 */
			for (int k = i; k < j; k++)
			{
				std::vector<std::pair<std::string, std::string> > combinations = this->calculateCombinations(i, k, j);
				for (int t = 0; t< combinations.size(); t++ )
				{
					/*
					 * Check all rules if any of the pairs can be found
					 */
					for (std::map<std::string, std::vector<std::string> >::iterator r_it = rules_.begin(); r_it != rules_.end(); r_it++)
					{
						std::string var = r_it->first;
						for (std::vector<std::string>::iterator it = r_it->second.begin(); it != r_it->second.end(); it++)
						{
							std::string temp = *it;
							if (temp.size() == 2)
							{
								std::string t1, t2;
								std::stringstream t_temp;
								t_temp << temp.at(0);
								t_temp >> t1;
								t_temp.clear();
								t_temp<<temp.at(1);
								t_temp>>t2;

								if (t1 == combinations.at(t).first && t2 == combinations.at(t).second)
								{
									this->add(i, j, var);
								}
							}
						}
					}
				}
			}
		}
	}
}
} /*namespace Grammar */

