#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int main()
{
	
	cout << "$";
	string command;

	getline(cin, command);

		
//	cout << endl;

	int argvlength = 0;	

	char *argv = new char[command.length() + 1];
	strcpy(argv, command.c_str());

	char *p = strtok(argv, " ");
	
	while(p != 0)
	{
		argv[argvlength] = p;
		argvlength++;
		p = strtok(NULL," ");
	}

//	argv[0] = new char[3];
//	argv[0] = "ls";
//	argv[1] = "-a";
//	argv[2] = "-a";

//	int r = execvp(argv[0], argv);

//	if(r == -1)
//	{
//		perror("Error");
//		cout << "Error executing execvp.";
//		exit(1);
//	}

	
	

	return 0;
}
