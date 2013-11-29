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
namespace BB {

class BareBonesStatement {
	/*
	 * This represents 1 statement of a barabones program
	 * this is a pure virtual class
	 */
public:
	BareBonesStatement();
	virtual ~BareBonesStatement();
};

class BBclear : public BareBonesStatement {
private:
	std::string variableName_ ; //! The name of the cleared variable
};

class BBincr : public BareBonesStatement {
private:
	std::string variableName_ ; //! Name of the variable which will be incremented
};

class BBdecr : public BareBonesStatement {
private:
	std::string variableName_ ; //! Name of the variable which will be decremented
};

class BBcopy : public BareBonesStatement {
private:
	std::string original_; //! name of variable to be copied
	std::string copy_; 	//! name of the variable to be copied to
};

class BBcomparison : public BareBonesStatement {
private:
	std::string left_; //! name of 1st variable
	char operator_; //! the comparison operator
	std::string right_; //! name of 2nd variable
};

class BBwhile : public BareBonesStatement {
private:
	BBcomparison check_; //! the statement to be evaluated
	std::vector<std::shared_ptr<BareBonesStatement> > body_; //! the body of the while statement
};


} /* namespace BB */

#endif /* BAREBONESSTATEMENT_H_ */
