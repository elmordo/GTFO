/*
 * TestGroupSettings.hpp
 *
 *  Created on: 8. 1. 2014
 *      Author: petr
 */

#ifndef TESTGROUPSETTINGS_HPP_
#define TESTGROUPSETTINGS_HPP_

#include "TestGroup.hpp"

namespace Sopka {
namespace GTFO {

class TestGroupSettings {

	/**
	 * seznam skupin
	 */
	TestGroupList g;

	/**
	 * prepinac pro include / exclude
	 * pokud je True, seznam bude zarhnut
	 */
	bool i;

public:

	TestGroupSettings() {
		i = false;
	}

	TestGroupSettings(const TestGroupSettings &o) {
		g = o.g;
		i = o.i;
	}

	virtual ~TestGroupSettings() {

	}

	/**
	 * vraci (konstantni) referenci na seznam skupiny
	 */
	inline const TestGroupList &groups() const {
		return g;
	}

	inline TestGroupList &groups() {
		return g;
	}

	/**
	 * vraci nastaveni include prepinace
	 */
	inline bool isInclude() const {
		return i;
	}

	/**
	 * nastavi hodnotu prepinace include
	 */
	inline void isInclude(bool include) {
		i = include;
	}
};

}
}

#endif /* TESTGROUPSETTINGS_HPP_ */
