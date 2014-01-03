/*
 * TestSuite.hpp
 *
 *  Created on: 3. 1. 2014
 *      Author: petr
 */

#ifndef TESTSUITE_HPP_
#define TESTSUITE_HPP_

#include "TestCase.hpp"
#include "TestBase.hpp"

#include <vector>

using namespace std;

namespace Gremlin {
namespace GTFO {

class TestSuite : public TestBase {
public:

	/**
	 * typ pro uchovavani TC
	 */
	typedef vector<TestCase> TestCaseList;

protected:

	/**
	 * obsahuje seznam provedenych TC
	 */
	TestCaseList tc;

public:

	/**
	 * bezparametricky, zakladni konstruktor
	 */
	TestSuite() {

	}

	TestSuite(const TestSuite &o) {
		tc = o.tc;
	}

	virtual ~TestSuite() {

	}

	/**
	 * provede testy
	 */
	void doTests() {

		/**
		 * @todo: dodelat filtrovani pomoci include a exclude
		 */
		for (TestCaseList::iterator pos = tc.begin();
				pos != tc.end();
				pos++) {

			pos->doTests();
		}
	}
};

}
}


#endif /* TESTSUITE_HPP_ */
