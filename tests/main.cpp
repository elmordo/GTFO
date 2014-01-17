/*
 * main.cpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#include "TestCase.hpp"
#include "TestSuite.hpp"
#include "Profiler.hpp"
#include <iostream>

using namespace Gremlin::GTFO;
using namespace std;

class A {

public:

	A() {

	}

	virtual ~A() {

	}
};

class B : public A {

public:

	B() {

	}

	virtual ~B() {

	}
};

class C {

public:

	C() {

	}

	virtual ~C() {

	}
};


class Test1 TEST_CASE {

public:

	TEST_DO(
			REGISTER_TEST(testEquals1)
			REGISTER_TEST(testEquals2)
			REGISTER_TEST(testInstance1)
			REGISTER_TEST(testInstance2)
			REGISTER_TEST(testInstance3)
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

	void testInstance1() {
		A a;

		assertInstanceOf<A>(&a, "Invalid instance");
	}

	void testInstance2() {
		A a;

		assertInstanceOf<B>(&a, "Invalid instance");
	}

	void testInstance3() {
		B a;

		assertInstanceOf<A>(&a, "Invalid instance");
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

		GTFO_START_PROFILING1("P1");
		GTFO_START_PROFILING2("P2", "P1");
		REGISTER_SUITE(Suite)

		GTFO_STOP_PROFILING("P1");

		Profiler::output(cout);
)
