/*
 * Profiler.hpp
 *
 *  Created on: 15. 1. 2014
 *      Author: petr
 */

#ifndef PROFILER_HPP_
#define PROFILER_HPP_

#include <list>
#include <map>
#include <string>
#include <ctime>
#include <exception>
#include <iostream>

#define GTFO_START_PROFILING1(NAME) Profiler::createInstance(NAME)->start();

#define GTFO_START_PROFILING2(NAME, PARENTNAME) Profiler::createInstance(NAME, PARENTNAME)->start();

#define GTFO_STOP_PROFILING(NAME) Profiler::getInstance(NAME)->stop();

#define GTFO_IP if (Profiler::pi == 0x0) Profiler::pi = new ProfilerMap();

namespace Gremlin {
namespace GTFO {

using namespace std;

class ProfilerException : public exception {

};

class Profiler;

typedef map<string, Profiler *> ProfilerMap;

static ProfilerMap pi;

class Profiler {
public:

	typedef map<string, Profiler *> ProfilerMap;
	typedef list<Profiler *> ProfilerList;

private:

	/**
	 * seznam potomku
	 */
	ProfilerList c;

	/**
	 * cas konce mereni
	 */
	clock_t e;

	/**
	 * jmeno profileru
	 */
	string n;

	/**
	 * predek profileru
	 */
	Profiler *p;

	/**
	 * zacatek mereni
	 */
	clock_t s;

	/**
	 * prepinac, zda zapocalo mereni
	 */
	bool ws;

	/**
	 * vytvori standardni instanci
	 */
	Profiler(string name, Profiler *parent) {

		// kontrola, jestli je jmeno zapsano
		if (pi.find(name) != pi.end() || name.size() == 0) {
			throw ProfilerException();
		}

		n = name;
		p = parent;

		e = s = 0;
		ws = false;

		pi[name] = this;

		if (parent != 0x0) {
			parent->c.push_back(this);
		}
	}

	/**
	 * vypise informace o profilovani
	 */
	void toString(ostream& out, string indent) const {
		// vypsani nazvu
		out << indent << "Name      : " << n << endl;

		// vypsani ticku
		out << indent << "Start tick: " << s << endl;
		out << indent << "End tick  : " << e << endl;

		// vypsani casoveho useku
		out << indent << "Delta time: " << diffSec() << " s" << endl;

		// vypsani hranicni cary
		out << indent << "-----------------------------------" << endl << endl;

		// tisk potomku
		string nextIndent = indent + "  ";

		for (
				ProfilerList::const_iterator pos = c.begin();
				pos != c.end();
				pos++
		) {
			(**pos).toString(out, nextIndent);
		}
	}

public:

	Profiler() {
		e = 0;
		s = 0;
		p = 0x0;
		ws = false;
	}

	virtual ~Profiler() {
		// likvidace potomku
		for (
				ProfilerList::iterator pos = c.begin();
				pos != c.end();
				pos++
		)
		{
			delete *pos;
		}

		// pokud je inicializovateno jmeno, pak se smauou reference
		if (n.size()) {
			// odstraneni reference z mapy
			pi.erase(n);

			// pokud je nastaven predek, odebere se z predka
			if (p != 0x0) {
				p->c.remove(this);
			}
		}
	}

	/**
	 * factory metoda pro tvorbu novych instanci
	 */
	static Profiler *createInstance(string name, string parentName="") {
		// kontrola, zda byl urcen prdek
		Profiler *parent = 0x0;

		if (parentName.size() > 0) {
			ProfilerMap::iterator parit = pi.find(parentName);

			// kontrola existence predka
			if (parit == pi.end()) {
				throw ProfilerException();
			}

			parent = parit->second;
		}

		Profiler *instance = new Profiler(name, parent);

		return instance;
	}

	/**
	 * vraci rozdil mezi zacatkem a konce mereni v sekundach
	 */
	double diffSec() const {
		if (ws) {
			throw ProfilerException();
		}

		double df = e - s;

		return df / (double) CLOCKS_PER_SEC;
	}

	/**
	 * vraci koncovy tick mereni
	 */
	clock_t endClock() const {
		return e;
	}

	/**
	 * vraci instanci profileru dle jmena
	 */
	static Profiler *getInstance(string name) {
		ProfilerMap::iterator pos = pi.find(name);

		if (pos == pi.end()) return 0x0;

		return pos->second;
	}

	/**
	 * zapocne mereni
	 */
	void start() {
		ws = true;
		s = clock();
	}

	/**
	 * vraci pocatecni tick mereni
	 */
	clock_t startClock() const {
		return s;
	}

	/**
	 * ukonci mereni
	 */
	void stop() {
		if (!ws) {
			throw ProfilerException();
		}

		// zasatveni podrizenych instanci
		for (
				ProfilerList::iterator pos = c.begin();
				pos != c.end();
				pos++
		)
		{
			(*pos)->stop();
		}

		ws = false;
		e = clock();
	}

	/**
	 * vypise informace o profilovani
	 */
	void toString(ostream &out) const {
		toString(out, "");
	}

	static void output(ostream &out) {
		// iterace nad mapou a vypisovani dat
		for (
				ProfilerMap::const_iterator pos = pi.begin();
				pos != pi.end();
				pos++
		)
		{
			// vyhodnoceni, jestli se jedna o nejvyssi instanci stromu
			if (pos->second->p == 0x0) {
				pos->second->toString(out);
			}
		}
	}
};

}
}


#endif /* PROFILER_HPP_ */
