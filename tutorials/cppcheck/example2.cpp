#include <iostream>

int foo(int x)
{
	int i;
	if(x > 0 )
	{
		std::cout << "X is greater than 0." << std::endl;
		i = 1;
	}
}

/*In this example, we see some stylistic problems with this code. 
While it may not cause any problems in the program, it is good practice 
to not have unnecessary code. Although, cppcheck does not normally display 
these style isses. In order to display the style issues, we run the 
command `--enable=style`. At the same time, enabling style will also 
enable warning, performance, and portability issues.
*/
