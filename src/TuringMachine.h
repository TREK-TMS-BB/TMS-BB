/*
 * TuringMachine.h
 *
 *  Created on: Nov 23, 2013
 *      Author: robin
 */

#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_

#include <vector>
#include <tuple>
#include <iostream>
#include "Exception.h"
#include "TMParser.h"
#include "TapeSymbol.h"
#include "Information.h"
#include "TMProgram.h"

namespace TM {

class TuringMachine {
public:
	//! Default constructor
	TuringMachine();

	//! Construct from .tm file
	/**
	 * @param filename the filename in which the Turing Machine is described
	 */
	TuringMachine(std::string filename);
	//! Construct from TMProgram
	/**
	 * @param program the program you want to run
	 */


	//! Function simulating the Turing Machine with given string on the stack
	/**
	 * @ param input vector with the input to be put on the tape, input will be handled as integers
	 */
	void simulate(std::vector<TapeSymbol> input );
	//! Function simulating the Turing Machine Turing Program
	void simulate(TMProgram);

	//! function printing the tape and the productions
	friend std::ostream& operator<< (std::ostream& out, TuringMachine& tm);

	//! A function returning the data on the tape (ie from 1st nonBlank symbol to last nonBlank symbol)
	std::vector<TapeSymbol> getOutput() const;


	//! Default destructor
	virtual ~TuringMachine();
private:

	//! A function moving the head in the direction given, adding a new place on the tape if neccessary
	/**
	 * @param dir the direction in which the head should move
	 */
	void move(Direction dir);

	//! A function returning the symbol under the head
	TapeSymbol getHead() const;

	//! A function writing given symbol under the head
	/**
	 * @param input TapeSymbol to be written on the tape
	 */
	void writeHead(TapeSymbol input);

	//! A function handling 1 simulation
	/*
	 * reads a symbol, writes, moves
	 */
	void simulateCycle();
	//! A function handling 1 simulation (using a TMProgram)
	/*
	 * reads a symbol, writes, moves
	 */
	void simulateCycle(TMProgram);

	//! A function setting the tape to 100 blanks
	void resetTape();

	Tape::iterator head_;					//! the head of the turing machine moving over the tape
	Tape tape_;								//! tape of the turing machine
	std::vector<StateName> states_;			//! vector containing all states
	StateName curState_;					//! the state where the TM currently in is
	std::vector<Production> productions_;	//! vector with all productions
};

} /* namespace TM */

#endif /* TURINGMACHINE_H_ */
