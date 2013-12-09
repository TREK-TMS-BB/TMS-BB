/*
 * utilities.cpp
 *
 *  Created on: Nov 15, 2013
 *      Author: kristof
 */

#include "utilities.h"

bool utilities::isNumber(std::string input) {
	for (auto e : input) {
		if (!std::isdigit(e)) {
			return false;
		}
	}
	return true;
}

std::string utilities::charToString(char input) {
	std::stringstream ss;
	ss << input;
	return ss.str();
}

std::string utilities::lowToUp(std::string woord){
	std::locale loc;
	for (std::string::size_type i=0; i<woord.length(); ++i){
	    woord[i]= std::toupper(woord[i],loc);
	}
	return woord;
}
std::string utilities::upToLow(std::string woord){
	std::locale loc;
	for (std::string::size_type i=0; i<woord.length(); ++i){
	    woord[i]= std::tolower(woord[i],loc);
	}
	return woord;
}
std::string utilities::replacestring(std::string str, std::string oldV, std::string newV){
	int index = 0;
	while (true) {
	     /* Locate the substring to replace. */
	     index = str.find(oldV, index);
	     if (index > str.length()){
	    	 break;
	     }
	     /* Make the replacement. */
	     str.replace(index, newV.length(), newV);
	     /* Advance index forward so the next iteration doesn't pick it up as well. */
	     index += newV.length();
	}
	return str;

}

std::string utilities::nextstring(std::string str){
	if (str.length() == 1){
		if (str < "Z"){
			str[str.length()-1]++;
			return str;
		}
		else if(str == "Z"){
			str = "A0";
			return str;
		}
	}
	else if (str.length() > 1 ){
		str[str.length()-1]++;
		return str;
	}
	return str;
}
