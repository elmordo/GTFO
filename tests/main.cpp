/*
 * main.cpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#include "TestCase.hpp"
#include "TestSuite.hpp"
#include <iostream>

using namespace Gremlin::GTFO;
using namespace std;

class Test1 TEST_CASE {

public:

	TEST_DO(
			REGISTER_TEST(testEquals1)
			REGISTER_TEST(testEquals2)
	)

	void testEquals1() {
		int i1 = 1;
		int i2 = 2;

		assertEqual(i1, i2, "Ahoj");
	}

	void testEquals2() {
		int i1 = 1;
		int i2 = 1;

		assertEqual(i1, i2, "Ahoj svete");
	}
};

class Test2 TEST_CASE {

public:

	TEST_INIT(
		TEST_AGROUP("G1")
	)

	TEST_DO(
		REGISTER_TEST(testEquals1)
		REGISTER_TEST(testEquals2)
	)

	void testEquals1() {
		int i1 = 1;
		int i2 = 2;

		assertEqual(i1, i2, "Ahoj");
	}

	void testEquals2() {
		int i1 = 1;
		int i2 = 1;

		assertEqual(i1, i2, "Ahoj svete");
	}
};

class Suite TEST_SUITE {

public:

	Suite() {
		REGISTER_TESTCASE(Test1);
		REGISTER_TESTCASE(Test2);
	}
};

GTFO_TEST_MAIN(
		REGISTER_SUITE(Suite)
		REGISTER_SUITE(Suite)
)
