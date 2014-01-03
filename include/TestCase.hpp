/*
 * TestCase.hpp
 *
 *  Created on: 29. 12. 2013
 *      Author: petr
 */

#ifndef TESTCASE_HPP_
#define TESTCASE_HPP_

#include "TestBase.hpp"
#include "TestGroup.hpp"
#include "AssertException.hpp"
#include "AssertReport.hpp"
#include "TestCaseReport.hpp"
#include "asserts.hpp"
#include <vector>
#include <iostream>

namespace Gremlin {
namespace GTFO {

using namespace std;

#define REGISTER_TEST(TEST_CALL) \
	r->addReport();\
	try {\
		setUp();\
		TEST_CALL();\
		r->getReport(testIndex).state(AssertReport::ASSERT_OK);\
		cout << ".";\
	} catch (AssertException &e) {\
		AssertReport &rep = r->getReport(testIndex);\
		rep.message(e.what());\
		rep.state(AssertReport::ASSERT_FAIL);\
		cout << "F";\
	} catch (...) {\
		AssertReport &rep = r->getReport(testIndex);\
		rep.message("Unhandled unknown exception");\
		rep.state(AssertReport::ASSERT_ERROR);\
		cout << "E";\
	}\
	tearDown();\
	testIndex++;

#define TEST_CASE : public TestCase
#define TEST_INIT std::size_t testIndex = 0;

class TestCaseReport;

class TestCase: public TestBase {
public:

	typedef vector<TestGroup> TestGroupList;

private:

	/**
	 * seznam skupin, kterych je case clenem
	 */
	TestGroupList g;

protected:

	/**
	 * ukazatel na zpravu z vysledku
	 */
	TestCaseReport *r;

public:

	/**
	 * bezparametricky konstruktor
	 */
	TestCase() {
		r = new TestCaseReport();
	}

	/**
	 * kopytor
	 */
	TestCase(const TestCase &o) {
		r = new TestCaseReport(*o.r);
	}

	/**
	 * destruktor
	 */
	virtual ~TestCase() {
		delete r;
	}

	/**
	 * prida TC do skupiny dle jmena
	 */
	void addGroup(const string &name) {
		g.push_back(TestGroup(name));
	}

	/**
	 * prida TC do skupiny dle instance
	 */
	void addGroup(const TestGroup &group) {
		g.push_back(group);
	}

	/**
	 * zde bude umisteno volani testu
	 */
	virtual void doTests() = 0;

	/**
	 * vraci True, pokud je TC v dane skupiny
	 */
	bool hasGroup(const string &name) const {
		for (TestGroupList::const_iterator pos = g.begin(); pos != g.end(); pos++) {

			if (pos->name() == name)
				return true;
		}

		return false;
	}

	bool hasGroup(const TestGroup &group) const {
		return hasGroup(group.name());
	}

	/**
	 * odebere skupinu dle jmena
	 */
	void removeGroup(const string &name) {
		for (TestGroupList::iterator pos = g.begin(); pos < g.end(); pos++) {

			if (pos->name() == name) {
				pos = g.erase(pos);
				// navrat na predchozi hodnotu
				pos--;
			}
		}
	}

	void removeGroup(const TestGroup &group) {
		removeGroup(group.name());
	}

	/**
	 * vraci zpravu z asertaci
	 */
	inline TestCaseReport *report() const {
		return r;
	}
};

}
}

#endif /* TESTCASE_HPP_ */
