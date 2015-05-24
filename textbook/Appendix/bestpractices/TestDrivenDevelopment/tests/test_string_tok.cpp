#define BOOST_TEST_MODULE "C++ Unit Tests for StrTok"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include "../src/string_tok.cpp"

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
