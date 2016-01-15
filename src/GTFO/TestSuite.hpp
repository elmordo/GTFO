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

#define GTFO_REGISTER_TESTCASE(CLASS_NAME) this->tc.push_back(new CLASS_NAME());this->tc.back()->init()

#define GTFO_TESTSUITE(TSNAME) class TSNAME : public Sopka::GTFO::TestSuite {\
public:\
    TSNAME() {
#define GTFO_ENDTESTSUITE }};

class TestSuite: public TestBase {
public:

	/**
     * test case container
	 */
	typedef vector<TestCase*> TestCaseList;

private:

	bool hasGroup(const TestCase &tc, const TestGroupList &groups) {

		for (TestGroupList::const_iterator pos = groups.begin();
				pos != groups.end(); pos++) {
			if (tc.hasGroup(*pos)) {
                // group found
				return true;
			}
		}

        // group not found
		return false;
	}

protected:

	/**
     * contains list of testcases in suite
	 */
	TestCaseList tc;

public:

	/**
     * create empty instance
	 */
    TestSuite()
    {
	}

    /**
     * @brief copytor
     * @param o original instance
     */
    TestSuite(const TestSuite &o)
    {
		// kopirovani test cases
        tc = o.tc;
	}

    /**
     * @brief destroy all instances
     */
	virtual ~TestSuite() {
		for (TestCaseList::const_iterator pos = tc.begin(); pos != tc.end();
				pos++) {
			delete *pos;
		}
	}

	/**
     * run registered test cases
	 */
    void doTests(const TestGroupSettings& settings = TestGroupSettings())
    {
        // separate test groups
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
        }
        else
        {
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

    /**
     * @brief print report into given stream
     * @param out output stream
     */
    void printReports(ostream &out)
    {
		for (TestCaseList::const_iterator pos = tc.begin();
				pos != tc.end();
				pos++)
		{
			const TestCaseReport::AssertReportList r = (*pos)->report()->reports();
			int testIndex = 1;

            out << endl << endl;

			for (TestCaseReport::AssertReportList::const_iterator rep = r.begin();
					rep != r.end();
					rep++)
			{
				if (rep->state() != AssertReport::ASSERT_OK) {
                    out << "Test case class (by typeid): " << rep->className() << endl;
                    out << "Test index: " << testIndex << endl;
                    out << "Test name: " << rep->name() << endl;
                    out << "State: ";

					switch (rep->state()) {
					case AssertReport::ASSERT_ERROR:
                        out << "Error";
						break;

					case AssertReport::ASSERT_FAIL:
                        out << "Fail";
						break;

					case AssertReport::NOT_ASSERTED:
                        out << "Not asserted";
						break;

					default:
                        out << "Unknown status";
						break;
					}

                    out << endl << "Message :" << endl;

                    out << rep->message() << endl;
                    out << "-------------------------" << endl << endl;
				}

				testIndex++;
			}
		}
	}
};

}
}

#endif /* TESTSUITE_HPP_ */
