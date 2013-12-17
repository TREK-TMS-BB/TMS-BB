/*
 * BareBonesStatement.h
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#ifndef BAREBONESSTATEMENT_H_
#define BAREBONESSTATEMENT_H_

#include <vector>
#include <memory>
#include <string>
#include "TMProgram.h"
#include "Information.h"
namespace BB {

class BareBonesStatement {
	/*
	 * This represents 1 statement of a barabones program
	 * this is a pure virtual class
	 */
public:
	BareBonesStatement();
	virtual ~BareBonesStatement();
	virtual TM::TMProgram createCode() = 0;
	virtual void print() = 0;
protected:
	static unsigned int count_ ; //! the count of nr of statements
};

class BBclear : public BareBonesStatement {
public:
	BBclear(int var);
	TM::TMProgram createCode();
	virtual void print() {std::cout << "clear" << std::endl; }
private:
	const int variable_ ; //! The name of the cleared variable
	const unsigned int statementNr_; //! the nr of the statement
};

class BBincr : public BareBonesStatement {
public:
	BBincr(int var);
	TM::TMProgram createCode();
	virtual void print() {std::cout << "incr" << std::endl; }
private:
	const int variable_ ; //! Name of the variable which will be incremented
	const unsigned int statementNr_; //! the nr of the statement
};

class BBdecr : public BareBonesStatement {
public:
	BBdecr(int var);
	TM::TMProgram createCode();
	virtual void print() {std::cout << "decr" << std::endl; }
private:
	const int variable_ ; //! Name of the variable which will be decremented
	const unsigned int statementNr_; //! the nr of the statement
};

class BBcopy : public BareBonesStatement {
public:
	BBcopy(int orig, int copy);
	TM::TMProgram createCode();
	virtual void print() {std::cout << "copy" << std::endl; }
private:
	const int original_; //! place of variable to be copied
	const int copy_; 	//! place of the variable to be copied to
	const int statementNr_; //! the nr of the statement
};

class BBwhile : public BareBonesStatement {
public:
	BBwhile(int var, std::vector<std::shared_ptr<BareBonesStatement> > body);
	TM::TMProgram createCode();
	virtual void print() {std::cout << "while with statements: " << std::endl;
		for (auto statement : body_) {
			statement->print();
		}
		std::cout << std::endl;
	}

private:
	const int compVar_; //! place of the variable used to loop -> loop while not 0
	const unsigned int statementNr_; //! the nr of the statement
	std::vector<std::shared_ptr<BareBonesStatement> > body_; //! the body of the while statement
};


} /* namespace BB */

#endif /* BAREBONESSTATEMENT_H_ */
