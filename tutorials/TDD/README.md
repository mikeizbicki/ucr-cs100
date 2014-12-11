# Tutorial on Test Driven Development

# Contents

  - [What is Test Driven Development](#what-is-test-driven-development)
  - [Why TDD](#why-tdd)
  - [TDD in C++](#tdd-in-c++)
  - [Examples:](#examples)
    - [Testing tokenizing a string](#testing-tokenizing-a-string)


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

Test Driven Development (TDD) is a [software development
process](http://en.wikipedia.org/wiki/Software_development_process). Development processes are methodologies to write code in a way that speeds up development, minimize bugs, and keep a code base managable.

TDD is fairly simple to use:

  1. Write tests
  2. Write code to pass that test
  3. Refractor until the code meets standards


## Why TDD


TDD keeps code akin to [unix philosophy](http://en.wikipedia.org/wiki/Unix_philosophy#Eric_Raymond.E2.80.99s_17_Unix_Rules). By following this philosophy it helps keep code modular and understandable. Because TDD forces you to start with focusing on what could go wrong, it practices thinking about edge cases.

## TDD in C++
To give examples of TDD I will be using the [boost test framework](http://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/utf.html).

# Examples
## Testing tokenizing a string

In this example I need a function( or functions ) that will take a `string` and return a `vector<string>`.

I want the `strings` in the `vector` to contain no whitespaces and be in the order they were in the string.

```
string s = "Today is a nice day!"
vector<string> v = some_tok_func(s)
```

Inside of `v` we want `["Today", "is", "a", "nice", "day!"]`.



