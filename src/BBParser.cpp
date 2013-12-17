/*
 * BBParser.cpp
 *
 *  Created on: Dec 12, 2013
 *      Author: kristof
 */

#include "BBParser.h"

namespace parser {

BBParser::BBParser() {
	// TODO Auto-generated constructor stub

}

BBParser::~BBParser() {
	// TODO Auto-generated destructor stub
}

BB::BareBonesProgram BBParser::parseBB(std::string file) {
	try {
		//While info;
		int whileVar = -1;
		bool whileFlag = false;
		std::vector<std::shared_ptr<BB::BareBonesStatement> > whileBody;

		std::string::iterator it;
		std::ifstream fs;
			fs.open(file);
			if (fs.is_open()) {
				while (!fs.eof()) {
					// As long as there is input.
					std::string line;
					std::string cleaned_line;
					getline(fs, line);
					std::size_t found;

					// Clean the line.
					found = line.find("#");
					if (found != std::string::npos) {
						// We found a comment.
						cleaned_line = line.substr(0, found);
					}
					else {
						cleaned_line = line;
					}

					// Continue with cleaned_line
					// Only 1 statement per line allowed.

					found = cleaned_line.find("clear ");
					if (found != std::string::npos) {
						// We found a clear statement.
						it = cleaned_line.begin() + found + 6;
						int var = readVar(it);
						// Read ';'
						if (*it != ';') {
							throw Exception("Statement doesn't end with ';'");
						}

						std::shared_ptr<BB::BareBonesStatement> statement = std::make_shared<BB::BBclear>(var);
						if (!whileFlag) {
							statements_.push_back(statement);
						}
						else {
							whileStack_.top().first.push_back(statement);
						}
					}

					found = cleaned_line.find("copy ");
					if (found != std::string::npos) {
						// We found a copy statement.
						it = cleaned_line.begin() + found + 5;
						// Read first var
						int from = readVar(it);
						// Read " to "
						std::string toBeRead(it, it+4);
						if (toBeRead != " to ") {
							throw Exception("Something wrong with statement: " + line);
						}
						// Read second var
						it = it + 4;
						int to = readVar(it);
						// Read ';'
						if (*it != ';') {
							throw Exception("Statement doesn't end with ';'");
						}

						std::shared_ptr<BB::BareBonesStatement> statement = std::make_shared<BB::BBcopy>(from, to);
						if (!whileFlag) {
							statements_.push_back(statement);
						}
						else {
							whileStack_.top().first.push_back(statement);
						}
					}

					found = cleaned_line.find("incr");
					if (found != std::string::npos) {
						// We found an incr statement.
						it = cleaned_line.begin() + found + 5;
						// Read var
						int var = readVar(it);
						// Read ';'
						if (*it != ';') {
							throw Exception("Statement doesn't end with ';'");
						}

						std::shared_ptr<BB::BareBonesStatement> statement = std::make_shared<BB::BBincr>(var);
						if (!whileFlag) {
							statements_.push_back(statement);
						}
						else {
							whileStack_.top().first.push_back(statement);
						}
					}
					found = cleaned_line.find("decr");
					if (found != std::string::npos) {
						// We found a decr statement.
						// We found an incr statement.
						it = cleaned_line.begin() + found + 5;
						// Read var
						int var = readVar(it);
						// Read ';'
						if (*it != ';') {
							throw Exception("Statement doesn't end with ';'");
						}

						std::shared_ptr<BB::BareBonesStatement> statement = std::make_shared<BB::BBdecr>(var);
						if (!whileFlag) {
							statements_.push_back(statement);
						}
						else {
							whileStack_.top().first.push_back(statement);
						}
					}

					found = cleaned_line.find("while ");
					if (found != std::string::npos) {
						// We found a while statement.
						// Turn on while flag and set whileVar.
						it = cleaned_line.begin() + found + 6;
						// Read whileVar
						whileVar = readVar(it);
						// Read " not 0 do;"
						std::string toBeRead(it, it+10);
						whileStack_.push(std::pair<std::vector<std::shared_ptr<BB::BareBonesStatement> >, int>(whileBody, whileVar));
						if (toBeRead != " not 0 do;") {
							throw Exception("Something wrong with statement: " + line);
						}
						else {
							whileFlag = true;
						}
					}

					found = cleaned_line.find("end;");
					if (found != std::string::npos) {

						std::pair<std::vector<std::shared_ptr<BB::BareBonesStatement> >, int> top = whileStack_.top();

						// End of while, construct the statement.
						std::shared_ptr<BB::BareBonesStatement> statement = std::make_shared<BB::BBwhile>(top.second, top.first);

						// We are only allowed to push the most outer while.
						// Else we'll execute some code more than once.
						if (whileStack_.size() == 1) {
							statements_.push_back(statement);
							whileStack_.pop();
						}
						else if (whileStack_.size() > 1) {
							// Add this while to the parent while body.
							whileStack_.pop();
							top = whileStack_.top();
							top.first.push_back(statement);
						}

						if (whileStack_.empty()) {
							whileFlag = false;
						}
					}
				}
			}
			return BB::BareBonesProgram(statements_	, varMap_.size());
	}
	catch (Exception& e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "ERROR: .bb file could not be parsed." << std::endl;
		exit(1);
	}
}

int BBParser::readVar(std::string::iterator& it) {
	try {
		std::string var = "";
		while (true) {
			char c = *it;
			if (c == ' ' || c == ';') {
				break;
			}
			if (isupper(c) && !isdigit(c)) {
				var += c;
			}
			else {
				throw Exception("Variables can only consist of uppercase letters. " + utilities::charToString(c) + " is not correct.");
			}
			it++;
		}

		// Check for var in map if it's not present add it.
		std::map<std::string, int>::iterator it;
		it = varMap_.find(var);
		if (it != varMap_.end()) {
			return it->second;
		}
		else {
			// We need to add this in our map.
			int size = varMap_.size();
			varMap_[var] = size;
			return size;
		}
	}
	catch (Exception& e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "ERROR: .bb file could not be parsed." << std::endl;
		exit(1);
	}
}

} /* namespace parser */
