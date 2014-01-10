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
#include "TestGroupSettings.hpp"

using namespace std;

namespace Gremlin {
namespace GTFO {

#define TEST_SUITE : public TestSuite
#define REGISTER_TESTCASE(CLASS_NAME) this->tc.push_back(new CLASS_NAME());this->tc.back()->init()

class TestSuite: public TestBase {
public:

	/**
	 * typ pro uchovavani TC
	 */
	typedef vector<TestCase*> TestCaseList;

private:

	bool hasGroup(const TestCase &tc, const TestGroupList &groups) {

		for (TestGroupList::const_iterator pos = groups.begin();
				pos != groups.end(); pos++) {
			if (tc.hasGroup(*pos)) {
				// skupina nalezena
				return true;
			}
		}

		// pokud program dosel az sem, pak skupina nebyla nalezena
		return false;
	}

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
		// kopirovani test cases

	}

	virtual ~TestSuite() {
		for (TestCaseList::const_iterator pos = tc.begin(); pos != tc.end();
				pos++) {
			delete *pos;
		}
	}

	/**
	 * provede testy
	 */
	void doTests(const TestGroupSettings& settings = TestGroupSettings()) {
	// separace seznamu skupin
			const
		TestGroupList &groups = settings.groups();

		// vyhodnoceni, jestli se jedna o include nebo exclude
		if (settings.isInclude()) {
			for (TestCaseList::iterator pos = tc.begin(); pos != tc.end();
					pos++) {

				// vyhodnoceni, jestli ma TC alespon nejakou skupinu
				if (!hasGroup(**pos, groups))
					continue;

				(*pos)->doTests();
			}
		} else {
			for (TestCaseList::iterator pos = tc.begin(); pos != tc.end();
					pos++) {

				// vyhodnoceni, jestli ma TC alespon nejakou skupinu
				if (hasGroup(**pos, groups))
					continue;

				(*pos)->doTests();
			}
		}
	}
};

}
}

#endif /* TESTSUITE_HPP_ */
