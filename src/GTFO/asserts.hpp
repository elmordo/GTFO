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
#include <cstdarg>
#include <cstdio>

using namespace std;

namespace Sopka {
namespace GTFO {

static char messageBuffer[1024];

#ifndef THROW_ASSERT
#define THROW_ASSERT va_list msgArgs; va_start(msgArgs, msg); vsprintf(messageBuffer, msg, msgArgs);va_end(msgArgs); throw AssertException(messageBuffer);
#endif

#ifndef ASSERT_MESSAGE
#define ASSERT_MESSAGE const char *msg, ...
#endif

/**
 * asertace, jestli hodnoty jsou stejne pomoci operatoru ==
 */
template<class E, class G>
void assertEqual(G g, E e, ASSERT_MESSAGE) {
	if (!(e == g)) {
		// vyhozeni vyjimky
		THROW_ASSERT;
	}
}

/**
 * asertace, jestli hodnoty jsou rozdilne pomoci operatoru !=
 */
template<class E, class G>
void assertNotEqual(G g, E e, ASSERT_MESSAGE) {
	if (!(e != g)) {
		// vyhozeni vyjimky
		THROW_ASSERT
	}
}

/**
 * asertace, jestli hodnota g je vetsi nez e pomoci operatoru >
 */
template<class E, class G>
void assertGreater(G g, E e, ASSERT_MESSAGE) {
	if (!(g > e)) {
		// vyhozeni vyjimky
		THROW_ASSERT

	}
}

/**
 * asertace, jestli hodnota g je vetsi nebo rovno e pomoci operatoru >=
 */
template<class E, class G>
void assertGreaterOrEqual(G g, E e, ASSERT_MESSAGE) {
	if (!(g >= e)) {
		// vyhozeni vyjimky
		THROW_ASSERT
	}
}

/**
 * asertace, jestli hodnota g je mensi nez e pomoci operatoru <
 */
template<class E, class G>
void assertLess(G g, E e, ASSERT_MESSAGE) {
	if (!(g < e)) {
		// vyhozeni vyjimky
		THROW_ASSERT
	}
}

/**
 * asertace, jestli hodnota g je mensi nebo rovno e pomoci operatoru <=
 */
template<class E, class G>
void assertLessOrEqual(G g, E e, ASSERT_MESSAGE) {
	if (!(g <= e)) {
		// vyhozeni vyjimky
		THROW_ASSERT
	}
}

/**
 * asertace, jestli ukazatel ukazuje na spravnou instanci
 */
template<class E, class B>
void assertInstanceOf(B *g, ASSERT_MESSAGE) {
	if ((dynamic_cast<E*>(g)) == 0) {
		THROW_ASSERT;
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
void assertNotIdentical(T &g, T &e, ASSERT_MESSAGE) {
	if (&g == &e) {
		THROW_ASSERT
	}
}

/**
 * asertace, jestli je dany ukazatel NULL (0x0)
 */
template <class G>
void assertNull(G *g, ASSERT_MESSAGE) {
	if (g != 0x0) {
		THROW_ASSERT
	}
}

/**
 * asertace, jestli dany ukazatel neni NULL (0x0)
 */
template<class G>
void assertNotNull(G *g, ASSERT_MESSAGE) {
	if (g == 0x0) {
		THROW_ASSERT
	}
}

/**
 * asertace, jestli je dana hodnota True
 */
template<class G=bool>
void assertTrue(G g, ASSERT_MESSAGE) {
	if (!g) {
		THROW_ASSERT
	}
}

/**
 * asertace, jestli je dana hodnota False
 */
template<class G=bool>
void assertFalse(G g, ASSERT_MESSAGE) {
	if (g) {
		THROW_ASSERT
	}
}

/**
 * test if arrays has equal elements
 */
template<class E, class G>
void assertArrayEqual(G g, E e, size_t n, ASSERT_MESSAGE) {
    try {
        for (size_t i = 0; i < n; ++i)
            assertEqual(g[i], e[i], "");
    } catch (AssertException &) {
        THROW_ASSERT
    }
}

/**
 * test if arrays has equal elements
 */
template<class E, class G>
void assertArrayNotEqual(G g, E e, size_t n, ASSERT_MESSAGE) {
    try {
        assertArrayEqual(g, e, n, "");
    } catch (AssertException &) {
        return;
    }

    THROW_ASSERT
}

#undef THROW_ASSERT
#undef ASSERT_MESSAGE

}
}


#endif /* ASSERTS_HPP_ */
