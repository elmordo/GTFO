/*
 * TestCaseReport.hpp
 *
 *  Created on: 29. 12. 2013
 *      Author: petr
 */

#ifndef TESTCASEREPORT_HPP_
#define TESTCASEREPORT_HPP_

#include "AssertReport.hpp"
#include "TestCase.hpp"
#include <vector>
#include <exception>

namespace Gremlin {
namespace GTFO {

class TestCase;

using namespace std;

class TestCaseReport {
public:

	/**
	 * typ pro udrzeni seznamu zprav z asertace
	 */
	typedef vector<AssertReport> AssertReportList;

private:

	/**
	 * seznam zprav z asertaci
	 */
	AssertReportList reports;

	/**
	 * ukazatel na TestCase, ktereho se zprava tyka
	 */
	const TestCase *tc;

public:

	TestCaseReport() {
		tc = 0x0;
	}

	TestCaseReport(const TestCase *testCase, size_t count = 0) {
		tc = testCase;
		reports = AssertReportList(count);
	}

	TestCaseReport(const TestCaseReport &o) {
		tc = o.tc;
		reports = o.reports;
	}

	virtual ~TestCaseReport(){

	}

	/**
	 * vytvori novou zpravu, vlozi ji na posledni misto v seznamu a vraci novou instanci
	 */
	AssertReport &addReport() {
		reports.push_back(AssertReport());

		return reports.back();
	}

	/**
	 * zkopiruje zpravu a vlozi ji na konec seznamu
	 */
	AssertReport &addReport(const AssertReport &report) {
		reports.push_back(report);

		return reports.back();
	}

	/**
	 * vraci zpravu na pozici i
	 */
	const AssertReport &getReport(size_t i) const {
		// kontrola jestli zprava existuje
		if (!hasIndex(i)) {
			// vyhozeni nejake vyjimky
			throw exception();
		}

		return reports[i];
	}

	AssertReport &getReport(size_t i) {
			// kontrola jestli zprava existuje
			if (!hasIndex(i)) {
				// vyhozeni nejake vyjimky
				throw exception();
			}

			return reports[i];
		}

	/**
	 * vraci True, pokud existuje zprava s indexem i
	 */
	inline bool hasIndex(size_t i) const {
		return i >= 0 && i < reports.size();
	}

	/**
	 * odebere zpravu z daneho mista
	 */
	inline void removeReport(size_t i) {
		reports.erase(reports.begin() + i);
	}

	/**
	 * vraci pocet reportu
	 */
	inline size_t size() const {
		return reports.size();
	}

	/**
	 * vraci konstantni ukazatel na rodicovsky TestCase
	 */
	inline const TestCase *testCase() const {
		return tc;
	}
};

}
}


#endif /* TESTCASEREPORT_HPP_ */
