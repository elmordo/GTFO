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

#ifndef GTFO_THROW_ASSERT
#define GTFO_THROW_ASSERT va_list msgArgs; va_start(msgArgs, msg); vsprintf(messageBuffer, msg, msgArgs);va_end(msgArgs); throw AssertException(messageBuffer);
#endif

#ifndef GTFO_ASSERT_MESSAGE
#define GTFO_ASSERT_MESSAGE const char *msg, ...
#endif

/**
 * equal assertation by operator ==
 */
template<class E, class G>
void assertEqual(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(e == g)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT;
	}
}

/**
 * non equal assertatiob by operator !=
 */
template<class E, class G>
void assertNotEqual(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(e != g)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT
	}
}

/**
 * is greater by operator >
 */
template<class E, class G>
void assertGreater(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(g > e)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT

	}
}

/**
 * is greater or equal by operator >=
 */
template<class E, class G>
void assertGreaterOrEqual(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(g >= e)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT
	}
}

/**
 * is lesser by operator <
 */
template<class E, class G>
void assertLess(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(g < e)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT
	}
}

/**
 * is lesser or equal by operator <=
 */
template<class E, class G>
void assertLessOrEqual(G g, E e, GTFO_ASSERT_MESSAGE) {
	if (!(g <= e)) {
		// vyhozeni vyjimky
		GTFO_THROW_ASSERT
	}
}

/**
 * assert given object is instance or its child
 */
template<class E, class B>
void assertInstanceOf(B *g, GTFO_ASSERT_MESSAGE) {
	if ((dynamic_cast<E*>(g)) == 0) {
		GTFO_THROW_ASSERT;
	}
}

/**
 * assert identity of objects (memory address)
 * @param g given value to test
 * @param e expected value
 * @param msg error message template
 * @param ... parameters of template
 * @tparam T type of tested value
 */
template<class T>
void assertIdentical(T &g, T &e, string msg) {
	if (&g != &e) {
		throw AssertException(msg);
	}
}

/**
 * assert not identity of objects (memory address)
 * @param g given value to test
 * @param e expected value
 * @param msg error message template
 * @param ... parameters of template
 * @tparam T type of tested value
 */
template<class T>
void assertNotIdentical(T &g, T &e, GTFO_ASSERT_MESSAGE) {
	if (&g == &e) {
		GTFO_THROW_ASSERT
	}
}

/**
 * assert pointer is null (0x0)
 * @param g given value to test
 * @param msg error message template
 * @param ... parameters of template
 * @tparam G type of tested value
 */
template <class G>
void assertNull(G *g, GTFO_ASSERT_MESSAGE) {
	if (g != 0x0) {
		GTFO_THROW_ASSERT
	}
}

/**
 * assert pointer is not NULL (0x0)
 * @param g given value to test
 * @param msg error message template
 * @param ... parameters of template
 * @tparam G type of tested value
 */
template<class G>
void assertNotNull(G *g, GTFO_ASSERT_MESSAGE) {
	if (g == 0x0) {
		GTFO_THROW_ASSERT
	}
}

/**
 * assert True value
 * @param g given value to test
 * @param msg error message template
 * @param ... parameters of template
 * @tparam G type of tested value
 */
template<class G=bool>
void assertTrue(G g, GTFO_ASSERT_MESSAGE) {
	if (!g) {
		GTFO_THROW_ASSERT
	}
}

/**
 * assert False value
 * @param g given value to test
 * @param msg error message template
 * @param ... parameters of template
 * @tparam G type of tested value
 */
template<class G=bool>
void assertFalse(G g, GTFO_ASSERT_MESSAGE) {
	if (g) {
		GTFO_THROW_ASSERT
	}
}

/**
 * assert arrays have equal elements
 * @param g array with given values
 * @param e array with expected values
 * @param n number of elements
 * @param msg error message template
 * @param ... arguments of template message
 * @tparam E type of expected array
 * @tparam G type of given array
 */
template<class E, class G>
void assertArrayEqual(G g, E e, size_t n, GTFO_ASSERT_MESSAGE) {
    try {
        for (size_t i = 0; i < n; ++i)
            assertEqual(g[i], e[i], "");
    } catch (AssertException &) {
        GTFO_THROW_ASSERT
    }
}

/**
 * assert arrays have not equal elements
 * @param g array with given values
 * @param e array with expected values
 * @param n number of elements
 * @param msg error message template
 * @param ... arguments of template message
 * @tparam E type of expected array
 * @tparam G type of given array
 */
template<class E, class G>
void assertArrayNotEqual(G g, E e, size_t n, GTFO_ASSERT_MESSAGE) {
    try {
        assertArrayEqual(g, e, n, "");
    } catch (AssertException &) {
        return;
    }

    GTFO_THROW_ASSERT
}

/**
 * assert exception thrown from given function
 * @param callRef function pointe to call
 * @param msg error message template
 * @param ... arguments of template message
 * @tparam EXCEPT exception type
 */
template<class EXCEPT>
void assertThrow(void (*callRef)(), GTFO_ASSERT_MESSAGE) {

    try {
        // call method
        callRef();
    } catch (EXCEPT &e) {
        return;
    }

    // exception was not catched - raise assert error
    GTFO_THROW_ASSERT
}

#undef GTFO_THROW_ASSERT
#undef GTFO_ASSERT_MESSAGE

}
}


#endif /* ASSERTS_HPP_ */
