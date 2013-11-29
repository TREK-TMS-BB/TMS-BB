/*
 * BareBonesProgram.h
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#ifndef BAREBONESPROGRAM_H_
#define BAREBONESPROGRAM_H_

namespace BB {

class BareBonesProgram {
public:
	BareBonesProgram();
	virtual ~BareBonesProgram();
	//! A function writing the BareBones program in TM language to given file
	void createTMFile(std::string outputFile);
private:
	std::vector<std::shared_ptr<BareBonesStatement> > statements; //! all statements of the program
};

} /* namespace BB */

#endif /* BAREBONESPROGRAM_H_ */
