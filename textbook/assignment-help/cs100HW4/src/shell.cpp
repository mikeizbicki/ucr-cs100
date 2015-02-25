#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
	string command;
	while(1)
	{
		getline(cin, command);
		if(command == "exit")
			exit(EXIT_SUCCESS);
	}
	return 0;
}
