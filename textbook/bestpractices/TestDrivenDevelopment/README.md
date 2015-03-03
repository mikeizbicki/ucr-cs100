# Tutorial on Test Driven Development

# Contents

  - [Introduction](#introduction)
  - [What is Test Driven Development](#what-is-test-driven-development)
  - [What TDD Is Not](#what-tdd-is-not)
  - [Examples:](#examples)
    - [Basic Example](#basic-example)
    - [Tokenizing A String](#tokenizing-a-string)


# Introduction
When I began coding, my process consisted of:

  * Writing down the problem (homework or personal project)
  * Thinking of some useful functions that might help me
  * Deciding what objects to use
  * Opening up my editor and just start programming
  * Realizing I didn't think of everything and throw aside my plan and struggle to complete what I set out to do

A lot of time was wasted planning a design that wouldn't work, but also rewriting code without a clear idea of what my code was doing.

Realizing this pain point I started practicing Test Driven Development.

## What is Test Driven Development

Test Driven Development (TDD) is a [software development process](http://en.wikipedia.org/wiki/Software_development_process).
Development processes are methodologies to write code in stages (or cycles). In general these methodologies are meant to help speed up development, minimize bugs, and keep code bases malleable.

Even though there are many different approaches to development, I prefer TDD because its style is to keep code simple and robust.

TDD's development cycle is simple:

  1. Write a test (initially failing)
  2. Write code to pass the test
  3. Rerun the tests
    * If the test fails back to 2
    * If the test passes go to 4
  4. Refractor to clean up the code.

# What TDD Is Not

TDD is not a magic bullet. Even though quality of code is higher, TDD can still lead to its own
[problems](http://blog.james-carr.org/2006/11/03/tdd-anti-patterns/). Also it has known issues for not being sufficient testing for interfaces such as UI, databases, or networking.

Because a test was written and passed does not mean that it is bug free. A programmer may not think of every situation.

TDD is meant to test and verify your own code. It's not necessary to test libraries that are included in your code. An example of an unnecessary test would be to test std::string `std::string("test") == "test"`. 

# Examples

To give examples of TDD I will be using the [boost test framework](http://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/utf.html).

## Basic Example

This is meant to be a very short introduction to testing. For a basic problem to
solve I will be using the first problem on
[projecteuler](https://projecteuler.net/problem=1)

`Find the sum of all the multiples of 3 or 5 below 1000.`

First let's write our test in `test/test_project_euler.cpp`.

```
#define BOOST_TEST_MODULE "EulerTest"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

int find_mult(const int &first_num, const int& second_num, const int &upper_bound)
{
  return -1;
}

BOOST_AUTO_TEST_CASE( euler_test )
{
  // The answer is 233168
  BOOST_CHECK(find_mult(3, 5, 1000) == 233168);
}
```
Compile and run our test.

```
$ g++ test_project_euler.cpp -o run_tests
$ ./run_tests
Running 1 test case...
tests/test_project_euler.cpp(12): error in "euler_test": check find_mult(3, 5, 1000) == 233168 failed

*** 1 failure detected in test suite "EulerTest"
```

Our test failed like we wanted it to. Now that we have our test, lets implement some code to pass our test.

```
int find_mult(const int &first_num, const int& second_num, const int &upper_bound)
{
  int mult_first_and_second = 0;

  // Using modulo (%) to check if it is a multiple of first_num or second_num
  for(int i = 0; i < upper_bound; ++i)
    if(i % first_num == 0 || i % second_num == 0)
      mult_first_and_second+=i;

  return mult_first_and_second;
}
```

The function `find_mult` is iterating over all integers from 0 to `upper_bound` and summing all the numbers that are a multiple of `first_num` or `second_num`.

Compile and run to see if we pass our test.

```
$ g++ test_project_euler.cpp -o run_tests
$ ./run_tests
Running 1 test case...

*** No errors detected
```

We passed the test so we were able to find all the multiples of 3 and 5 from 0
to 1000.

## Tokenizing A String

In this example I need a function( or functions ) that will take a `string` and return a `vector<string>`.

The `strings` in the `vector` should contain no whitespaces, and their arrangement should be in the order they appeared in the string.

```
string s = "Today is a nice day!"
vector<string> v = some_tok_func(s)
// v should contain `["Today", "is", "a", "nice", "day!"]`.
```

First let's write our test in `tests/test_string_tok.cpp`. The test should be designed such that the first time they are ran they will fail.

```
#define BOOST_TEST_MODULE "C++ Unit Tests for StrTok"
#include <boost/test/included/unit_test.hpp> // used so we can include other .cpp
#include <boost/test/unit_test.hpp>
#include "../src/string_tok.cpp" // Where we are implementing our code

BOOST_AUTO_TEST_CASE(string_tok_test)
{
// This sting is the string we are going to try and tokenize
  const string test_string = "Hello today is a good day!";
// This vector is what tok_string should return 
  vector<string> test_vector = {"Hello", "today", "is", "a", "good", "day!"}; // c++11 vector initialization

  BOOST_CHECK(tok_string(test_string) == test_vector);
}
```

Now we implement a prototype of `tok_string` in `src/string_tok.cpp`, so our test can run and fail.

```
vector<string> tok_string(const string& input)
{
  vector<string> v;
  return v;
}
```

`tok_string` will always return an empty vector causing `string_tok_test` to fail. 

Let’s find out. Compile and run the test.

```
$ g++ -std=c++11  tests/test_string_tok.cpp -o str_test
$ ./str_test
Running 1 test case...
tests/test_string_tok.cpp(11): error in "string_tok_test": check tok_string(test_string) == test_vector failed

*** 1 failure detected in test suite "C++ Unit Tests for StrTok"
```

Good, our test failed. Now we can begin implementing code to try and pass the test.

Now, let us implement some basic code to make sure our code will pass our test.

```
// ./src/string_tok.cpp
vector<string> tok_string(const string& input)
{
  vector<string> v = {"Hello", "today", "is", "a", "good", "day!"};
  return v;
}
```

Recompile and run.

```
$ g++ -std=c++11  tests/test_string_tok.cpp -o str_test
$./str_test
Running 1 test case...

*** No errors detected
```

This is a pitfall I wanted to point out. Our code does pass the test, however the code was implemented to only pass that one test. If the test was slightly adjusted at all, the test would immediately fail.  

Now we need to begin refractoring our implementation. 

```
vector<string> tok_string(const string& input)
{
  vector<string> v;
  string token;
  istringstream ss(input.c_str());

  // Strip whitespaces from input
  while(ss>>token)
    v.push_back(token);

  return v;
}
```

Recompile and retest:

```
$ g++ -std=c++11  tests/test_string_tok.cpp -o str_test
$./str_test
Running 1 test case...

*** No errors detected
```

We can expand the test cases more to cover more edge cases.

```
BOOST_AUTO_TEST_CASE(string_tok_test)
{
  const string test_string = "Hello today is a good day!";
  const string test_string2 = "           Hello     today           is           a      good day!";
  const string test_string3 = "Hello \n today \t is \n\t a good day!";

  vector<string> test_vector = {"Hello", "today", "is", "a", "good", "day!"};

  //Testing basic tokens
  BOOST_CHECK(tok_string(test_string) == test_vector);

  //Testing many spaces
  BOOST_CHECK(tok_string(test_string2) == test_vector);

  //Testing newlines spaces and tabs
  BOOST_CHECK(tok_string(test_string3) == test_vector);
}
```


```
$ g++ -std=c++11 tests/test_string_tok.cpp -o str_test
$./str_test
Running 1 test case...

*** No errors detected
```

The new tests pass, however `BOOST_CHECK(tok_string(test_string3) == test_vector);` is not a good test.
The reason for this is that it is testing too many things. Suppose newlines broke `tok_string`. Our test will not tell us that newline was the cause of the failure. It will tell us that failure was either newline or tabs. This is ambiguous because you don't know the source of the failure.

In summary:

  1. We wrote the test `string_tok_test`.
  2. Implemented the function `tok_string` to satisfy the test we made.
  3. Refractor the test until `string_tok_test` was passed.
