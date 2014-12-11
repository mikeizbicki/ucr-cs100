# Tutorial on Test Driven Development

# Contents

  - [Introduction](#introduction)
  - [What is Test Driven Development](#what-is-test-driven-development)
  - [Why TDD](#why-tdd)
  - [TDD in C++](#tdd-in-c++)
  - [Examples:](#examples)
    - [Basic Example](#basic-example)
    - [Tokenizing A String](#tokenizing-a-string)


# Introduction
When I began coding my process consisted of:

  * Writing down the problem (homework/or personal project)
  * Maybe thinking of some useful functions that might help me
  * Maybe some objects to use
  * Open up my editor and just start programming
  * Realize I didn't think of everything and throw aside my plan
  and struggle to complete what I set out to do

The point being I wasted a lot of time not just planning something that wouldn't
work, also rewriting code without a clear idea of what my code was doing.

Realizing this pain point I started practicing Test Driven Development.

## What is Test Driven Development

Test Driven Development (TDD) is a [software development process](http://en.wikipedia.org/wiki/Software_development_process). Development processes are methodologies to write code in a way that speeds up development, minimize bugs, and keep a code base managable.

TDD is fairly simple to use:

  1. Write tests
  2. Write code to pass that test
  3. Refractor until the code meets standard.

## Why TDD

TDD keeps code akin to [unix philosophy](http://en.wikipedia.org/wiki/Unix_philosophy#Eric_Raymond.E2.80.99s_17_Unix_Rules). By following this philosophy it helps keep code modular and understandable.
An advantage of TDD is that a feauture is required to be unabiguous

## TDD in C++
To give examples of TDD I will be using the [boost test framework](http://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/utf.html).

# Examples

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

Now that we have our test we will start writing code to try and pass our test.

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

The `strings` in the `vector` should contain no whitespaces and be in the order they were in the string.

```
string s = "Today is a nice day!"
vector<string> v = some_tok_func(s)
```

Inside of `v` we want `["Today", "is", "a", "nice", "day!"]`.
First we lets write our test in `tests/test_string_tok.cpp`

```
#define BOOST_TEST_MODULE "C++ Unit Tests for StrTok"
#include <boost/test/included/unit_test.hpp> // used so we can include other .cpp
#include <boost/test/unit_test.hpp>
#include "../src/string_tok.cpp" // Where we are implementing our code

BOOST_AUTO_TEST_CASE(string_tok_test)
{
  const string test_string = "Hello today is a good day!";
  vector<string> test_vector = {"Hello", "today", "is", "a", "good", "day!"}; // c++11 vector initialization

  BOOST_CHECK(tok_string(test_string) == test_vector);
}
```
The tests should be designed so that it is easy to control how they will fail.

Now we implement a prototype of `tok_string` in `src/string_tok.cpp`. Our
prototype should compile but fail 100% of the time . The reason for this is we want to
ensure we don't get any false posatives in our tests.

```
vector<string> tok_string(const string& input)
{
  vector<string> v;
  return v;
}
```

Now we compile and run our test.

```
$ g++ -std=c++11  tests/test_string_tok.cpp -o str_test
$ ./str_test
Running 1 test case...
tests/test_string_tok.cpp(11): error in "string_tok_test": check tok_string(test_string) == test_vector failed

*** 1 failure detected in test suite "C++ Unit Tests for StrTok"
```

Now that there is a full test file we can begin trying to implement code that
will pass our test. We want to just know if our test will pass with some very
basic code to make sure our code will pass our test.

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

To recap so far what we have done:

  1. Wrote the `string_tok_test`
  2. Wrote the function `tok_string` to barely pass `string_tok_test`

Now we need to begin refractoring our implementation. Since we can't just return
the correct a constant vector each and everytime we need to actually tokenize
our string.

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

We can expand on our test cases more to cover more edge cases in our code.

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

In summary:

  1. Wrote `string_tok_test`
  2. Wrote `tok_string`
  3. Refractored
  4. Added more tests to `string_tok_test`

