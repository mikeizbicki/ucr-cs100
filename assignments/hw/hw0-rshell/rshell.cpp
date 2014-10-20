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
	cout << endl;
	cout << "$";
	string command;

	getline(cin, command);


	int argvlength = 0;	
	int i = 0;

	char **argv = new char*[4];

	while(i != 4)
	{
		argv[i] = NULL;
		++i;
	}

	char *temp = new char[command.length() + 1];
	strcpy(temp, command.c_str());

	char *p = strtok(temp, " ");
	
	while(p != 0)
	{
		argv[argvlength] = p;
		argvlength++;
		p = strtok(NULL," ");
	}
	argv[argvlength] = NULL;


	int r = execvp(argv[0], argv);

	if(r == -1)
	{
		perror("Error");
		cout << "Error executing execvp."
		     << endl;
		exit(1);
	}

	
	return 0;
}
