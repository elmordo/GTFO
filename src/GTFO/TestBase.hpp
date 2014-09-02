/*
 * TestBase.hpp
 *
 *  Created on: 29. 12. 2013
 *      Author: petr
 */

#ifndef TESTBASE_HPP_
#define TESTBASE_HPP_

#define GTFO_MAIN_INIT \#include <iostream>

#define GTFO_TEST_MAIN(SUITES...) int main(int argc, char** argv) {\
	Sopka::GTFO::TestGroupSettings settings;/* naparsovani argumentu*/\
	if (argc > 1) {\
		/* vyhodnoceni, zda se bude includovat nebo excludovat */ \
		string ie(argv[1]);\
		if (ie == "-i") settings.isInclude(true);\
		for (int i = 2; i < argc; i++) {\
			settings.groups().push_back(Sopka::GTFO::TestGroup(argv[i]));\
		}\
	}\
	SUITES\
	std::cout << endl << endl << "-----------" << endl << "All tests were finished" << endl;\
	return 0;\
}

#define GTFO_REGISTER_SUITE(CLASS_NAME) {\
	CLASS_NAME s;\
	s.doTests(settings);\
	s.printReports(std::cout);\
}

namespace Sopka {
namespace GTFO {

class TestBase {

public:

	TestBase() {

	}

	virtual ~TestBase() {

	}

	virtual void setUp() {

	}

	virtual void tearDown() {

	}
};

}
}


#endif /* TESTBASE_HPP_ */
