/*
 * AssertReport.hpp
 *
 *  Created on: 23. 12. 2013
 *      Author: petr
 */

#ifndef ASSERTREPORT_HPP_
#define ASSERTREPORT_HPP_

#include <string>

using namespace std;

namespace Gremlin {
namespace GTFO {

class AssertReport {

public:

	enum ASSERT_STATE {
		NOT_ASSERTED,
		ASSERT_OK,
		ASSERT_FAIL,
		ASSERT_ERROR
	};

private:

	/**
	 * zprava z asertace
	 */
	string msg;

	/**
	 * jmeno asertace
	 */
	string n;

	/**
	 * stav asertace
	 */
	ASSERT_STATE s;

public:

	/**
	 * vytvori prazdnou instanci
	 */
	AssertReport() {
		s = NOT_ASSERTED;
	}

	/**
	 * vytvori plne inicializovanou instanci
	 */
	AssertReport(string message, ASSERT_STATE state) {
		msg = message;
		s = state;
	}

	/**
	 * kopytor
	 */
	AssertReport(const AssertReport &o) {
		msg = o.msg;
		s = o.s;
	}

	virtual ~AssertReport() {

	}

	/**
	 * vraci zpravu z asertace
	 */
	const string &message() const {
		return msg;
	}

	/**
	 * vraci jmeno asertace
	 */
	const string &name() const {
		return n;
	}

	/**
	 * vraci stav z asertace
	 */
	ASSERT_STATE state() const {
		return s;
	}

	/**
	 * operator prirazeni
	 */
	AssertReport &operator =(const AssertReport &o) {
		s = o.s;
		msg = o.msg;

		return *this;
	}
};

}
}


#endif /* ASSERTREPORT_HPP_ */
