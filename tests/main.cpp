/*
 * main.cpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#include "TestCase.hpp"
#include "TestSuite.hpp"

using namespace Gremlin::GTFO;

class Test1 TEST_CASE {

public:

	virtual void doTests() {
		TEST_INIT

		REGISTER_TEST(testEquals1)
		REGISTER_TEST(testEquals2)
	}

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

	virtual void doTests() {
		TEST_INIT

		addGroup("G1");

		REGISTER_TEST(testEquals1)
		REGISTER_TEST(testEquals2)
	}

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

int main() {

	Suite s;
	TestGroupSettings set;

	s.doTests();

	set.isInclude(true);
	set.groups().push_back(TestGroup("G1"));

	s.doTests(set);

	return 0;
}
