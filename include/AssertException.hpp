/*
 * AssertException.hpp
 *
 *  Created on: 1. 1. 2014
 *      Author: petr
 */

#ifndef ASSERTEXCEPTION_HPP_
#define ASSERTEXCEPTION_HPP_

#include <exception>
#include <string>

using namespace std;

namespace Gremlin {
namespace GTFO {

class AssertException : public exception {

	/**
	 * retezec obsahujici popis chyby
	 */
	string w;

	/**
	 * kod chyby
	 */
	int c;

public:

	/**
	 * bezparametricky konstruktor
	 */
	AssertException() {
		c = 1;
	}

	/**
	 * konstruktor vytvori chybovou hlasku
	 */
	AssertException(string w, int c = 1) {
		this->w = w;
		this->c = c;
	}

	/**
	 * kopytor
	 */
	AssertException(const AssertException &o) {
		w = o.w;
		c = o.c;
	}

	/**
	 * destruktor
	 */
	virtual ~AssertException() throw() {

	}

	/**
	 * vraci chybovy kod
	 */
	int code() const {
		return c;
	}

	/**
	 * vraci chybovou hlasku
	 */
	virtual const char *what() const throw() {
		return w.c_str();
	}
};

}
}


#endif /* ASSERTEXCEPTION_HPP_ */
