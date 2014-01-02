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
#include <vector>

namespace Gremlin {
namespace GTFO {

#define REGISTER_TEST(TEST_CALL) \
	try {\
		TEST_CALL;\
		r->getReport(testIndex).state(AssertReport::ASSERTR_OK);\
	catch (AssertException &e) {\
		AssertReport &r = r->getReport(testIndex);\
		r.message(e.what());\
		r.state(AssertReport::ASSERT_FAIL);\
	} catch (...) {\
		AssertReport &r = r->getReport(testIndex);\
		r.message("Unhandled unknown exception");\
		r.state(AssertReport::ASSERT_ERROR);\
	}\
	testIndex++;

class TestCaseReport;

class TestCase: public TestBase {
public:

	typedef vector<TestGroup> TestGroupList;

private:

	/**
	 * ukazatel na zpravu z vysledku
	 */
	TestCaseReport *r;

	/**
	 * seznam skupin, kterych je case clenem
	 */
	TestGroupList g;

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
		r = new TestCaseReport(o.r);
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
		for (TestGroupList::iterator pos = g.begin(); pos != g.end(); pos++) {

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
