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
#include <iostream>

using namespace std;

namespace Sopka {
namespace GTFO {

#define GTFO_TEST_SUITE : public Sopka::GTFO::TestSuite
#define GTFO_REGISTER_TESTCASE(CLASS_NAME) this->tc.push_back(new CLASS_NAME());this->tc.back()->init()

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
			int testCount = 0;
			int casesCount = 0;

		// vyhodnoceni, jestli se jedna o include nebo exclude
		if (settings.isInclude()) {
			for (TestCaseList::iterator pos = tc.begin(); pos != tc.end();
					pos++) {

				// vyhodnoceni, jestli ma TC alespon nejakou skupinu
				if (!hasGroup(**pos, groups))
					continue;

				(*pos)->doTests();
				testCount += (*pos)->report()->size();
				++casesCount;
			}
		} else {
			for (TestCaseList::iterator pos = tc.begin(); pos != tc.end();
					pos++) {

				// vyhodnoceni, jestli ma TC alespon nejakou skupinu
				if (hasGroup(**pos, groups))
					continue;

				(*pos)->doTests();
                testCount += (*pos)->report()->size();
                ++casesCount;
			}
		}

		cout << endl << "Suite " << typeid(*this).name() << " finished, " << testCount << " tests done in " << casesCount << " test case(s)" << endl;
	}

	void printReports(ostream &out) {
		for (TestCaseList::const_iterator pos = tc.begin();
				pos != tc.end();
				pos++)
		{
			const TestCaseReport::AssertReportList r = (*pos)->report()->reports();
			int testIndex = 1;

			cout << endl << endl;

			for (TestCaseReport::AssertReportList::const_iterator rep = r.begin();
					rep != r.end();
					rep++)
			{
				if (rep->state() != AssertReport::ASSERT_OK) {
					cout << "Test case class (by typeid): " << rep->className() << endl;
					cout << "Test index: " << testIndex << endl;
					cout << "Test name: " << rep->name() << endl;
					cout << "State: ";

					switch (rep->state()) {
					case AssertReport::ASSERT_ERROR:
						cout << "Error";
						break;

					case AssertReport::ASSERT_FAIL:
						cout << "Fail";
						break;

					case AssertReport::NOT_ASSERTED:
						cout << "Not asserted";
						break;

					default:
						cout << "Unknown status";
						break;
					}

					cout << endl << "Message :" << endl;

					cout << rep->message() << endl;
					cout << "-------------------------" << endl << endl;
				}

				testIndex++;
			}
		}
	}
};

}
}

#endif /* TESTSUITE_HPP_ */
