/*
 * TestGroup.hpp
 *
 *  Created on: 30. 12. 2013
 *      Author: petr
 */

#ifndef TESTGROUP_HPP_
#define TESTGROUP_HPP_

#include<string>

using namespace std;

namespace Gremlin {
namespace GTFO {

class TestGroup {

	string n;

public:

	TestGroup() {

	}

	TestGroup(const TestGroup &o) {
		n = o.n;
	}

	virtual ~TestGroup() {

	}

	const string &name() const {
		return n;
	}

	void name(const string &n) {
		this->n = n;
	}
};

}
}



#endif /* TESTGROUP_HPP_ */
