#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <cstdlib>
#include <stdio.h>
#include <boost/tokenizer.hpp>

using namespace std;
//using namespace boost;

int main()
{
	
	cout << endl;
	cout << "$";
	string command;

	getline(cin, command);

	

//	tokenizer<char_separator<char> > tok(command);
//	char_separator<char> sep(" ", keep_empty_tokens);
//	for(tokenizer<>::iterator
//	 beg=tok.begin(); beg!=tok.end(); ++beg)
//	{
//		cout << *beg << endl;
//	}
		

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
//	argv[0] = new char[3];
	cout <<	argv[0] << endl;
	cout <<	argv[1] << endl;

	cout <<	argv[2] << endl;
	cout << argv[3] << endl;
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
