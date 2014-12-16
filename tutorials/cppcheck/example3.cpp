#include <iostream>

void greaterThanZero(int x)
{
	int i;
	if(x > 0 )
	{
		std::cout << "X is greater than 0." << std::endl;
		i = 1;
	}
}

int foo(int x, int y)
{
	return x + y;
}

int main()
{
	int a = 1, b = 2;
	foo(,b);

	return 0;
}

/*Here we added the main function. We still get the same as errors for not 
using variables i, but now we get errors for an unused function 
`greaterThanZero`. We found this using the command `cppcheck 
--enable=all example3.cpp`.*/

