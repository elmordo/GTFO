GTFO
====

GTFO (Gremlin Test Framework Objects) is simple framework for unittests in C++ with no external dependencies and there is no need to include any external library (all code is in header files).

Components
----------

### TestCase

Base of all unit tests is test case represented by Sopka::GTFO::TestCase class

* GTFO_TEST_CASE - include information about class inheritance from TestCase
* GTFO_TEST_CASE_INIT(code) - create initialisation method (called from constructor)
* GTFO_TEST_DO(testList) - create method called when test case is runned. Contains GTFO_REGISTER_TEST macros with tests
* GTFO_REGISTER_TEST(testMethodName) - register test method into test case


Example:

Create your test case class at first.

MyTestCase.hpp:


    #include <GTFO/TestCase.hpp>
    #include <GTFO/asserts.hpp>
    #include <iostream>

    using namespace std;
    using namespace Sopka::GTFO;

    class MyTestCase : GTFO_TEST_CASE {
    public:

      GTFO_TEST_CASE_INIT(
        cout << "TestCase initialisation" << endl;
      )

      GTFO_TEST_DO(
        GTFO_REGISTER_TEST(test1)
        GTFO_REGISTER_TEST(test2)
      )

      /**
       * do some test
       */
      void test1() {
        assertEqual(1, 2, "This assert fails, because %d was given but %d was expected", 1, 2);
      }

      /**
       * do some another test
       */
      void test2() {
        assertEqual(2, 2, "This assert should be ok");
      }
    };

### TestSuite

One or more TestCase instance is grouped into TestSuite. Test suite is logical group of test cases. Base class for test suites is Sopka::GTFO::TestSuite

Provided macros:

* GTFO_TEST_SUITE - include information about class inheritance for suite
* GTFO_REGISTER_TESTCASE - register testcase into suite

Example:

    #include<GTFO/TestSuite.hpp>
    
    class SampleSuite GTFO_TEST_SUITE {
    public:
      
      SampleSuite() {
        GTFO_REGISTER_TESTCASE(SomeTestCaseClass);
        GTFO_REGISTER_TESTCASE(SomeOtherTestCaseClass);
      }
    };

### TestBase

Basic module is TestBase.hpp. This header file provides several macros for initialization test environment.

Provided macros:

* GTFO_MAIN_INIT - include modules from STL required by environment
* GTFO_COMMA - macro for comma character [,]
* GTFO_TEST_MAIN - generate main() function for test program
* GTFO_REGISTER_SUITE - register suite into main function

Example:

    #include<GTFO/TestBase.hpp>
    
    GTFO_MAIN_INIT
    
    GTFO_TEST_MAIN(
      GTFO_REGISTER_SUITE(SomeSuiteClassToRegister),
      GTFO_REGISTER_SUITE(SomeOtherSuiteClassToRegister)
    )
