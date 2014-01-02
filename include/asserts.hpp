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

}
}


#endif /* ASSERTS_HPP_ */
