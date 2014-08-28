/*
 * TestGroup.hpp
 *
 *  Created on: 30. 12. 2013
 *      Author: petr
 */

#ifndef TESTGROUP_HPP_
#define TESTGROUP_HPP_

#include<string>
#include<vector>

using namespace std;

namespace Sopka {
namespace GTFO {

class TestGroup {

	string n;

public:

	TestGroup() {

	}

	TestGroup(const string &name) {
		n = name;
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

typedef vector<TestGroup> TestGroupList;

}
}



#endif /* TESTGROUP_HPP_ */
