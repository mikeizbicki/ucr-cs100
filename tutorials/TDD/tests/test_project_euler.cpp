#define BOOST_TEST_MODULE "EulerTest"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

int find_mult(const int &first_num, const int& second_num, const int &upper_bound)
{
  int mult_first_and_second = 0;

  //Using modulo to check if it is a multiple of first_num or second_num
  for(int i = 0; i < upper_bound; ++i)
    if(i % first_num == 0 || i % second_num == 0)
      mult_first_and_second+=i;

  return mult_first_and_second;
}

BOOST_AUTO_TEST_CASE( euler_test )
{
  BOOST_CHECK(find_mult(3, 5, 1000) == 233168);
}
