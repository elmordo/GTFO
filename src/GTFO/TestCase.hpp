/*
 * TestCase.hpp
 *
 *  Created on: 29. 12. 2013
 *      Author: petr
 */

#ifndef GTFO_TESTCASE_HPP_
#define GTFO_TESTCASE_HPP_

#include "TestBase.hpp"
#include "TestGroup.hpp"
#include "AssertException.hpp"
#include "AssertReport.hpp"
#include "TestCaseReport.hpp"
#include "asserts.hpp"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <string>

namespace Sopka {
namespace GTFO {

using namespace std;

#define GTFO_REGISTER_TEST(TEST_CALL) \
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
	} catch (std::exception &e){\
	    Sopka::GTFO::AssertReport &rep = r->getReport(testIndex);\
	    rep.message(std::string("Unhandled std exception: ") + e.what());\
	    rep.state(Sopka::GTFO::AssertReport::ASSERT_ERROR);\
	    cout << "E(" << (testIndex+1) << ")";\
	} catch (...) {\
		Sopka::GTFO::AssertReport &rep = r->getReport(testIndex);\
		rep.message("Unhandled unknown exception");\
		rep.state(Sopka::GTFO::AssertReport::ASSERT_ERROR);\
		cout << "E(" << (testIndex+1) << ")";\
	}\
	tearDown();\
	testIndex++;

#define GTFO_TESTCASE(TCNAME) class TCNAME : public Sopka::GTFO::TestCase {\
public:\
    TCNAME() {}
#define GTFO_ENDTESTCASE };

#define GTFO_TESTCASE_INIT std::size_t testIndex = 0;\
	std::string className = typeid(this).name();
#define GTFO_TESTCASE_AGROUP(GNAME) addGroup(GNAME);
#define GTFO_TESTCASE_DO(TESTS...) virtual void doTests() {GTFO_TEST_INIT TESTS}

#define GTFO_TESTCASE_TESTLIST virtual void doTests() { GTFO_TEST_INIT
#define GTFO_TESTCASE_ENDTESTLIST }

#define GTFO_TESTCASE_INIT virtual void init() {
#define GTFO_TESTCASE_ENDINIT }

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

    void fail(const char *msg, ...) {
        char messageBuffer[1024];

        va_list msgArgs;
        va_start(msgArgs, msg);
        vsprintf(messageBuffer, msg, msgArgs);
        va_end(msgArgs);

        throw AssertException(messageBuffer);
    }

    /**
     * vraci True, pokud je TC v dane skupiny
     */
    bool hasGroup(const string &name) const {
        for (TestGroupList::const_iterator pos = g.begin(); pos != g.end();
                pos++) {

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
