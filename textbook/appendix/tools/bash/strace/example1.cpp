#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main()
{
	int pid = fork();

	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		cout << "Hello, I am a child!" << endl;
		exit(1);
	}
	else
	{
		if(wait(0) == -1)
		{
			perror("wait");
			exit(1);
		}
		cout << "Hello, I am a parent!" << endl;
	}

	cout << endl;
	return 0;
}
