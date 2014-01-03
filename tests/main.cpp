/*
 * main.cpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#include "TestCase.hpp"

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

int main() {

	Test1 t;

	t.doTests();

	return 0;
}
