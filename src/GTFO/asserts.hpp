/*
 * asserts.hpp
 *
 *  Created on: 1. 1. 2014
 *      Author: petr
 */

#ifndef ASSERTS_HPP_
#define ASSERTS_HPP_

#include "AssertReport.hpp"
#include "AssertException.hpp"
#include <string>
#include <string.h>
#include <typeinfo>

using namespace std;

namespace Gremlin {
namespace GTFO {

/**
 * asertace, jestli hodnoty jsou stejne pomoci operatoru ==
 */
template<class E, class G>
void assertEqual(G g, E e, string msg) {
	if (!(e == g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli hodnoty jsou rozdilne pomoci operatoru !=
 */
template<class E, class G>
void assertNotEqual(G g, E e, string msg) {
	if (!(e != g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli hodnota g je vetsi nez e pomoci operatoru >
 */
template<class E, class G>
void assertGreater(G g, E e, string msg) {
	if (!(e > g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli hodnota g je vetsi nebo rovno e pomoci operatoru >=
 */
template<class E, class G>
void assertGreaterOrEqual(G g, E e, string msg) {
	if (!(e >= g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli hodnota g je mensi nez e pomoci operatoru <
 */
template<class E, class G>
void assertLess(G g, E e, string msg) {
	if (!(e < g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli hodnota g je mensi nebo rovno e pomoci operatoru <=
 */
template<class E, class G>
void assertLessOrEqual(G g, E e, string msg) {
	if (!(e <= g)) {
		// vyhozeni vyjimky
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli ukazatel ukazuje na spravnou instanci
 */
template<class E, class B>
void assertInstanceOf(B *g, string msg) {
	if ((dynamic_cast<E*>(g)) == 0) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli g a e jsou stejne instance (stejne misto v pameti)
 */
template<class T>
void assertIdentical(T &g, T &e, string msg) {
	if (&g != &e) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli g a e jsou ruzne instance (ruzne misto v pameti)
 */
template<class T>
void assertNotIdentical(T &g, T &e, string msg) {
	if (&g == &e) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli je dany ukazatel NULL (0x0)
 */
void assertNull(void *g, string msg) {
	if (g != 0x0) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli dany ukazatel neni NULL (0x0)
 */
void assertNotNull(void *g, string msg) {
	if (g == 0x0) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli je dana hodnota True
 */
void assertTrue(bool g, string msg) {
	if (!g) {
		throw AssertException(msg);
	}
}

/**
 * asertace, jestli je dana hodnota False
 */
void assertFalse(bool g, string msg) {
	if (g) {
		throw AssertException(msg);
	}
}

}
}


#endif /* ASSERTS_HPP_ */
