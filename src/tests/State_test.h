/*
 * State_test.h
 *
 *  Created on: Nov 21, 2013
 *      Author: tom
 */

#ifndef STATE_TEST_H_
#define STATE_TEST_H_

#include <iostream>
#include <map>

#include "../State.h"
#include <gtest/gtest.h>

namespace tests {

	class StateTest: public testing::Test {
		friend class PDA::State;
	protected:
		PDA::State state;
		virtual void SetUp() {
		}
		virtual void TearDown() {
		}
	};

	TEST_F(StateTest, State_ConstructorTest) {
		PDA::State q0("q0");
		PDA::State q1("q1");
		PDA::State q2;

		EXPECT_EQ(q0.get_name(), "q0");
		EXPECT_EQ(q1.get_name(), "q1");
		EXPECT_EQ(q2.get_name(), "uninitialized");
	}

	TEST_F(StateTest, State_TransitionsTest) {
		PDA::State q0("q0");
		std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> transitions;
		std::vector<std::string> stackops;
		stackops.push_back("pop");
		stackops.push_back("push");
		stackops.push_back("3");
		q0.add_transition('x', "X", "q1", stackops);
		std::pair<char, std::string> inputpair;
		inputpair.first = 'x';
		inputpair.second = 'X';
		std::pair<std::string, std::vector<std::string>> outputpair;
		outputpair.first = "q1";
		outputpair.second = stackops;
		transitions.insert(std::pair<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>(inputpair, outputpair));
		stackops.clear();
		stackops.push_back("pop");
		q0.add_transition('x', "Y", "q2", stackops);
		inputpair.first = 'x';
		inputpair.second = 'Y';
		outputpair.first = "q2";
		outputpair.second = stackops;
		transitions.insert(std::pair<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>(inputpair, outputpair));
		std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>>::iterator it1, it2;
		std::multimap<std::pair<char, std::string>, std::pair<std::string, std::vector<std::string>>> statetransitions = q0.get_transitions();
		it2 = statetransitions.begin();
		for (it1 = transitions.begin(); it1 != transitions.end(); it1++) {
			EXPECT_EQ(it1->first.first, it2->first.first);
			EXPECT_EQ(it1->first.second, it2->first.second);
			EXPECT_EQ(it1->second.first, it2->second.first);
			EXPECT_EQ(it1->second.second, it2->second.second);
			it2++;
		}
	}

	TEST_F(StateTest, State_SimulateTest) {
		PDA::State q0("q0");
		std::vector<std::string> stackops;
		stackops.push_back("pop");
		stackops.push_back("push");
		stackops.push_back("3");
		q0.add_transition('x', "X", "q1", stackops);
		std::vector<std::string> stackops2;
		stackops2.push_back("pop");
		q0.add_transition('x', "Y", "q2", stackops2);
		std::vector<std::pair<std::string, std::vector<std::string>>> after_transition = q0.simulate('x', "X");
		for (auto p : after_transition) {
			EXPECT_EQ(p.first , "q1");
			for (unsigned int i = 0; i < stackops.size(); i++) {
				EXPECT_EQ(stackops[i], p.second[i]);
			}
		}
		after_transition = q0.simulate('x', "Y");
		for (auto p : after_transition) {
			EXPECT_EQ(p.first , "q2");
			for (unsigned int i = 0; i < stackops2.size(); i++) {
				EXPECT_EQ(stackops2[i], p.second[i]);
			}
		}
		after_transition = q0.simulate('y', "Y");
		EXPECT_EQ(after_transition.size(), 0);
	}


}



#endif /* STATE_TEST_H_ */
