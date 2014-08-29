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
#include <typeinfo>

namespace Sopka {
namespace GTFO {

using namespace std;

#define REGISTER_TEST(TEST_CALL) \
	r->addReport();\
	r->getReport(testIndex).name(#TEST_CALL);\
	r->getReport(testIndex).className(className);\
	setUp();\
	try {\
		TEST_CALL();\
		r->getReport(testIndex).state(Sopka::GTFO::AssertReport::ASSERT_OK);\
		cout << ".";\
	} catch (Sopka::GTFO::AssertException &e) {\
		Sopka::GTFO::AssertReport &rep = r->getReport(testIndex);\
		rep.message(e.what());\
		rep.state(Sopka::GTFO::AssertReport::ASSERT_FAIL);\
		cout << "F(" << (testIndex+1) << ")";\
	} catch (...) {\
		Sopka::GTFO::AssertReport &rep = r->getReport(testIndex);\
		rep.message("Unhandled unknown exception");\
		rep.state(Sopka::GTFO::AssertReport::ASSERT_ERROR);\
		cout << "E(" << (testIndex+1) << ")";\
	}\
	tearDown();\
	testIndex++;

#define TEST_CASE : public Sopka::GTFO::TestCase
#define TEST_IINIT std::size_t testIndex = 0;\
	std::string className = typeid(this).name();
#define TEST_AGROUP(gName) addGroup(gName);
#define TEST_DO(TESTS...) virtual void doTests() {TEST_IINIT TESTS}
#define TEST_INIT(VALS...) virtual void init() { VALS }

class TestCaseReport;

class TestCase: public TestBase {

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
		init();
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
	 * pripravi instanci
	 */
	virtual void init() {

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
