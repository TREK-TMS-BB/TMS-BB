/*
 * LinkTM.h
 *
 *  Created on: Dec 11, 2013
 *      Author: robin
 */

#ifndef LINKTM_H_
#define LINKTM_H_

#include <iostream>
#include <vector>

namespace TM {

//! A function renaming the variables to filename_VarName
/**
 * @param file: the name of the TM file where the variables have to be renamed
 * @param output: the name of the output file
 */
void renameVariables(std::string file, std::string output);

//! A function linking 2 files into output
/**
 * @param input1: the name of the 1st TM file
 * @param input2: the name of the 2nd TM file
 * @param output: the name of the output TM file
 */
void linkFiles(std::string input1, std::string input2, std::string output);

//! A function linking n files into output
/**
 * @param input a vector with the filenames of the files to be linked
 * @param output the file in which the TM will be written
 */
void linkFiles(std::vector<std::string> input, std::string output);
}



#endif /* LINKTM_H_ */
