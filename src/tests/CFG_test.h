/*
 * CFG_test.h
 *
 *      Author: Robin
 */

#ifndef BASICCLASSESTEST_H_
#define BASICCLASSESTEST_H_

#include "../CFG.h"
#include <gtest/gtest.h>


namespace tests {

	class CFGTest: public testing::Test {
			friend class CFG;
		protected:
			CFG cfg;
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
	};

	class CNF_CFGTest: public testing::Test {
		friend class CFG;
	protected:
		CNF_CFG cnf;
		virtual void SetUp() {
		}
		virtual void tearDown() {
		}
	};

	TEST_F(CFGTest, ConstructorTest) {
		/*
		 * Test all the constructors for CFG
		 */
		std::vector<std::string> var = cfg.getVariables();
		EXPECT_EQ(var.size(), 1);
	}
}

#endif /* BASICCLASSESTEST_H_ */
