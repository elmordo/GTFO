GTFO
====

GTFO is simple framework for unittests in C++ with no external dependencies (all code is in header files).

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

<code>
  #include &lt;GTFO/TestCase.hpp&gt;<br />
  #include &lt;GTFO/asserts.hpp&gt;<br />
  #include &lt;iostream&gt;<br />

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
</code>