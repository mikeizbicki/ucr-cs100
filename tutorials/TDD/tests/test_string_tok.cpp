#define BOOST_TEST_MODULE "C++ Unit Tests for StrTok"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include "../src/string_tok.cpp"

BOOST_AUTO_TEST_CASE(string_tok_test)
{
  string test_string = "Hello today is a good day!";
  vector<string> test_vector;
  test_vector.push_back("Hello");
  test_vector.push_back("today");
  test_vector.push_back("is");
  test_vector.push_back("a");
  test_vector.push_back("good");
  test_vector.push_back("day!");

  BOOST_CHECK(tok_string(test_string) == test_vector);
}
