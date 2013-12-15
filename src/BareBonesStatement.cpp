/*
 * BareBonesStatement.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: robin
 */

#include "BareBonesStatement.h"

namespace BB {

unsigned int BareBonesStatement::count_ = 0;

BareBonesStatement::BareBonesStatement() {
	count_++;
}

BareBonesStatement::~BareBonesStatement() {
}

BBclear::BBclear(int var) :variable_(var) , BareBonesStatement(), statementNr_(count_) {
}

TM::TMProgram BBclear::createCode() {
	std::vector<TM::Production> productions;
	std::vector<TM::StateName> states;

	// Goto n
	int i = 0;
	for (i = 0; i < variable_; i++) {
		states.push_back(utilities::toString(i));
		TM::Production temp(utilities::toString(i),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i) );
		productions.push_back(temp);
		TM::Production temp2(utilities::toString(i),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+1) );
		productions.push_back(temp2);
	}
	states.push_back(utilities::toString(i));
	states.push_back("while");
	// link to while
	TM::Production temp(utilities::toString(i),TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none, "while" );
	productions.push_back(temp);


	// clear itself:
	/**
	PRODUCTIONS {
	0 0 0 n halt ;           # end of while loop
	0 1 1 n true ;           # here link to rest of while loop
	true * * n ds ;
	ds 1 B r d0 ;      		 # write a Blank on the 1 we are going to delete
	d0 1 1 r d0 ;
	d0 0 0 r d0 ;
	d0 B B l dq ;
	dq 1 B l da ;
	dq 0 B l db ;
	da 1 1 l da ;
	da 0 1 l db ;
	da B 1 r end ;
	db 0 0 l db ;
	db 1 0 l da ;
	db B 0 r end ;
	end * * l g0 ;
	g0 1 1 l g0 ;
	g0 0 0 l g0 ;
	g0 B B r 0 ;
	}
	 */

	states.push_back("true");
	// the while check:

	temp = TM::Production ("while",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::none, "goS" );
	productions.push_back(temp);
	temp = TM::Production ("while",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::none, "true" );
	productions.push_back(temp);

	// add states used in decr
	states.push_back("ds");
	states.push_back("d0");
	states.push_back("d1");
	states.push_back("d2");
	states.push_back("d3");
	states.push_back("dend");

	// link true to decr:
	temp = TM::Production ("true",TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none, "ds" );
	productions.push_back(temp);

	temp = TM::Production ("ds",TM::TapeSymbol(1),TM::TapeSymbol("_"),TM::right, "d0" );
	productions.push_back(temp);

	// go over input till end
	temp = TM::Production ("d0",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, "d0" );
	productions.push_back(temp);
	temp = TM::Production ("d0",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, "d0" );
	productions.push_back(temp);
	temp = TM::Production ("d0",TM::TapeSymbol("_"),TM::TapeSymbol("_"),TM::left, "d1" );
	productions.push_back(temp);

	// remove last input (remember it)
	temp = TM::Production ("d1",TM::TapeSymbol(1),TM::TapeSymbol("_"),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d1",TM::TapeSymbol(0),TM::TapeSymbol("_"),TM::left, "d3" );
	productions.push_back(temp);

	// go back, writing remembered value over head and remembering head
	temp = TM::Production ("d2",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d2",TM::TapeSymbol(0),TM::TapeSymbol(1),TM::left, "d3" );
	productions.push_back(temp);
	temp = TM::Production ("d2",TM::TapeSymbol("_"),TM::TapeSymbol(1),TM::none, "dend" );
	productions.push_back(temp);

	temp = TM::Production ("d3",TM::TapeSymbol(1),TM::TapeSymbol(0),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d3",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, "d3" );
	productions.push_back(temp);
	temp = TM::Production ("d3",TM::TapeSymbol("_"),TM::TapeSymbol(0),TM::none, "dend" );
	productions.push_back(temp);

	// link back to while:
	temp = TM::Production ("dend",TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none, "while" );
	productions.push_back(temp);

	// go Back to start (from while false)
	states.push_back("goS");

	temp = TM::Production("goS",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left,"goS" );
	productions.push_back(temp);
	temp = TM::Production("goS",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left,"goS" );
	productions.push_back(temp);
	temp = TM::Production("goS",TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none,"halt" );
	productions.push_back(temp);


	states.push_back("halt");

	// create clear program:
	TM::TMProgram prog(states,productions, utilities::toString(statementNr_)+"Clear"+utilities::toString(variable_));

	return prog;

}

BBincr::BBincr(int var) : variable_(var) , statementNr_(count_){
}

TM::TMProgram BBincr::createCode() {
	std::vector<TM::Production> productions;
	std::vector<TM::StateName> states;

	// Goto n
	int i = 0;
	for (i = 0; i < variable_; i++) {
		states.push_back(utilities::toString(i));
		TM::Production temp(utilities::toString(i),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i) );
		productions.push_back(temp);
		TM::Production temp2(utilities::toString(i),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+1) );
		productions.push_back(temp2);
	}

	// incr itself:
	/**
	 * PRODUCTIONS {
		0 1 1 r a ;
		0 0 1 r b ;
		0 B B n halt ;

		a 1 1 r a ;
		a 0 1 r b ;
		a B 1 n halt ;

		b 0 0 r b ;
		b 1 0 r a ;
		b B 0 n halt ;
		}
	*/
	states.push_back(utilities::toString(i));	// the start
	states.push_back(utilities::toString(i+1));	// write 1's
	states.push_back(utilities::toString(i+2));	// write 0's
	states.push_back(utilities::toString(i+3));	// link to gotoStart
	TM::Production temp(utilities::toString(i),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i+1) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+2) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i),TM::TapeSymbol("_"),TM::TapeSymbol("_"),TM::none, utilities::toString(i+3) );
	productions.push_back(temp);

	temp = TM::Production(utilities::toString(i+1),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i+1) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+1),TM::TapeSymbol(0),TM::TapeSymbol(1),TM::right, utilities::toString(i+2) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+1),TM::TapeSymbol("_"),TM::TapeSymbol(1),TM::none, utilities::toString(i+3) );
	productions.push_back(temp);

	temp = TM::Production(utilities::toString(i+2),TM::TapeSymbol(1),TM::TapeSymbol(0),TM::right, utilities::toString(i+1) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+2),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+2) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+2),TM::TapeSymbol("_"),TM::TapeSymbol(0),TM::none, utilities::toString(i+3) );
	productions.push_back(temp);

	// link to halt:
	/**
	 0 1 1 l 0
	 0 0 0 l 0
	 0 B B r halt
	 */
	states.push_back("halt");
	temp = TM::Production(utilities::toString(i+3),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, utilities::toString(i+3) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+3),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, utilities::toString(i+3) );
	productions.push_back(temp);
	temp = TM::Production(utilities::toString(i+3),TM::TapeSymbol("_"),TM::TapeSymbol("_"),TM::right, "halt" );
	productions.push_back(temp);


	// create incr program:
	TM::TMProgram prog(states,productions, utilities::toString(statementNr_)+"Incr"+utilities::toString(variable_));

	return prog;

}

BBdecr::BBdecr(int var) : variable_(var) , statementNr_(count_){
}

TM::TMProgram BBdecr::createCode() {
	std::vector<TM::Production> productions;
	std::vector<TM::StateName> states;


	// Goto n
	int i = 0;
	for (i = 0; i < variable_; i++) {
		states.push_back(utilities::toString(i));
		TM::Production temp(utilities::toString(i),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i) );
		productions.push_back(temp);
		TM::Production temp2(utilities::toString(i),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+1) );
		productions.push_back(temp2);
	}
	states.push_back(utilities::toString(i));
	// decr code:
	/**
	PRODUCTIONS {
	s 1 B r 0 ;      # write a Blank on the 1 we are going to delete
	0 1 1 r 0 ;
	0 0 0 r 0 ;
	0 B B l q ;
	q 1 B l a ;
	q 0 B l b ;
	a 1 1 l a ;
	a 0 1 l b ;
	a B 1 n halt ;
	b 0 0 l b ;
	b 1 0 l a ;
	b B 0 n halt ;
	}
	*/
	// add decr states:
	states.push_back("s");
	states.push_back("d0");
	states.push_back("d1");
	states.push_back("d2");
	states.push_back("d3");
	states.push_back("end");

	// link to decr:
	TM::Production temp(utilities::toString(i),TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none, "s");
	productions.push_back(temp);

	temp = TM::Production ("s",TM::TapeSymbol(1),TM::TapeSymbol("_"),TM::right, "d0" );
	productions.push_back(temp);

	// go over input till end
	temp = TM::Production ("d0",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, "d0" );
	productions.push_back(temp);
	temp = TM::Production ("d0",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, "d0" );
	productions.push_back(temp);
	temp = TM::Production ("d0",TM::TapeSymbol("_"),TM::TapeSymbol("_"),TM::left, "d1" );
	productions.push_back(temp);

	// remove last input (remember it)
	temp = TM::Production ("d1",TM::TapeSymbol(1),TM::TapeSymbol("_"),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d1",TM::TapeSymbol(0),TM::TapeSymbol("_"),TM::left, "d3" );
	productions.push_back(temp);

	// go back, writing remembered value over head and remembering head
	temp = TM::Production ("d2",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d2",TM::TapeSymbol(0),TM::TapeSymbol(1),TM::left, "d3" );
	productions.push_back(temp);
	temp = TM::Production ("d2",TM::TapeSymbol("_"),TM::TapeSymbol(1),TM::none, "end" );
	productions.push_back(temp);

	temp = TM::Production ("d3",TM::TapeSymbol(1),TM::TapeSymbol(0),TM::left, "d2" );
	productions.push_back(temp);
	temp = TM::Production ("d3",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, "d3" );
	productions.push_back(temp);
	temp = TM::Production ("d3",TM::TapeSymbol("_"),TM::TapeSymbol(0),TM::none, "end" );
	productions.push_back(temp);

	// go back to start:
	/**
	 0 1 1 l 0
	 0 0 0 l 0
	 0 B B r halt
	 */
	temp = TM::Production("end",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, "end" );
	productions.push_back(temp);
	temp = TM::Production("end",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, "end" );
	productions.push_back(temp);
	temp = TM::Production("end",TM::TapeSymbol("_"),TM::TapeSymbol("_"),TM::right, "halt" );
	productions.push_back(temp);

	states.push_back("halt");

	// create decr program:
	TM::TMProgram prog(states,productions, utilities::toString(statementNr_)+"Decr"+utilities::toString(variable_));

	return prog;
}

BBcopy::BBcopy(int orig, int copy) : BareBonesStatement(), statementNr_(count_), original_(orig), copy_(copy) {
}

TM::TMProgram BBcopy::createCode() {
	std::vector<TM::Production> productions;
	std::vector<TM::StateName> states;


	// Goto n
	int i = 0;
	for (i = 0; i < original_; i++) {
		states.push_back(utilities::toString(i));
		TM::Production temp(utilities::toString(i),TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, utilities::toString(i) );
		productions.push_back(temp);
		TM::Production temp2(utilities::toString(i),TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, utilities::toString(i+1) );
		productions.push_back(temp2);
	}
	states.push_back(utilities::toString(i));

	//Copy:
	/**
	0 0 0 n wr0			# no more 1s to copy
	0 1 Y r 1			# overwrite 1 with Y (remembers position)
	1 1 1 r 1
	1 0 0 r 1
	1 B 1 l 2			# write 1

	2 1 1 l 2			# Go back to Y
	2 0 0 l 3
	3 1 1 l 3
	3 Y 1 r 0			# Start again

	wr0 B 0 n halt		# loop over everything untill you meet a Blank (write 0 here)
	wr0 * * r wr0
	 */

	TM::StateName s0 = utilities::toString(i+1);
	TM::StateName s1 = utilities::toString(i+2);
	TM::StateName s2 = utilities::toString(i+3);
	TM::StateName s3 = utilities::toString(i+4);

	states.push_back(s0);
	states.push_back(s1);
	states.push_back(s2);
	states.push_back(s3);
	states.push_back("wr0");

	// link to copy:
	TM::Production temp(utilities::toString(i), TM::TapeSymbol("*"),TM::TapeSymbol("*"),TM::none, s0 );
	productions.push_back(temp);


	temp = TM::Production (s0,TM::TapeSymbol(0),TM::TapeSymbol(0),TM::none, "wr0" );
	productions.push_back(temp);
	temp = TM::Production (s0,TM::TapeSymbol(1),TM::TapeSymbol("Y"),TM::right, s1 );
	productions.push_back(temp);

	temp = TM::Production (s1,TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, s1 );
	productions.push_back(temp);
	temp = TM::Production (s1,TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, s1 );
	productions.push_back(temp);
	temp = TM::Production (s1,TM::TapeSymbol(),TM::TapeSymbol(1),TM::left, s2 );
	productions.push_back(temp);

	temp = TM::Production (s2,TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, s2 );
	productions.push_back(temp);
	temp = TM::Production (s2,TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, s2 );
	productions.push_back(temp);
	temp = TM::Production (s2,TM::TapeSymbol("Y"),TM::TapeSymbol(1),TM::right, s0 );
	productions.push_back(temp);

	temp = TM::Production ("wr0",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::right, "wr0" );
	productions.push_back(temp);
	temp = TM::Production ("wr0",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::right, "wr0" );
	productions.push_back(temp);
	temp = TM::Production ("wr0",TM::TapeSymbol(),TM::TapeSymbol(0),TM::none, "goS" );
	productions.push_back(temp);

	states.push_back("goS");

	temp = TM::Production ("goS",TM::TapeSymbol(0),TM::TapeSymbol(0),TM::left, "goS" );
	productions.push_back(temp);
	temp = TM::Production ("goS",TM::TapeSymbol(1),TM::TapeSymbol(1),TM::left, "goS" );
	productions.push_back(temp);
	temp = TM::Production ("goS",TM::TapeSymbol(),TM::TapeSymbol(),TM::right, "halt" );
	productions.push_back(temp);

	states.push_back("halt");

	TM::TMProgram prog(states, productions, utilities::toString(statementNr_)+"Copy"+utilities::toString(original_));
	return prog;
}

BBwhile::BBwhile(int var, std::vector<std::shared_ptr<BareBonesStatement> > body)
	: compVar_(var),
	  statementNr_(count_),
	  body_(body)
{}


TM::TMProgram BBwhile::createCode() {

}


} /* namespace BB */
