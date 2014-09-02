/*
 * main.cpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#include <iostream>

#include "GTFO/TestCase.hpp"
#include "GTFO/TestSuite.hpp"
#include "GTFO/Profiler.hpp"

using namespace Sopka::GTFO;
using namespace std;

class A {

public:

    A() {

    }

    virtual ~A() {

    }
};

class B: public A {

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

class Test1 GTFO_TEST_CASE {

public:

	GTFO_TEST_DO(
			GTFO_REGISTER_TEST(testEquals1)
			GTFO_REGISTER_TEST(testEquals2)
			GTFO_REGISTER_TEST(testInstance1)
			GTFO_REGISTER_TEST(testInstance2)
			GTFO_REGISTER_TEST(testInstance3)
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

class Test2 GTFO_TEST_CASE {

public:

    GTFO_TEST_CASE_INIT(
        GTFO_TEST_AGROUP("G1")
	)

    GTFO_TEST_DO(GTFO_REGISTER_TEST(testEquals1) GTFO_REGISTER_TEST(testEquals2))

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

class Suite GTFO_TEST_SUITE {

public:

Suite() {
    GTFO_REGISTER_TESTCASE(Test1);
    GTFO_REGISTER_TESTCASE(Test2);
}
};

GTFO_TEST_MAIN(

    GTFO_START_PROFILING1("P1"); GTFO_START_PROFILING2("P2", "P1"); GTFO_REGISTER_SUITE(Suite)

    GTFO_STOP_PROFILING("P1");

    Profiler::output(cout);)
