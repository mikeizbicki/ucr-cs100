#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <netdb.h>

using namespace std;

void parsing(char* buf, char** arguments)
{

	int i;
	for( i = 0; buf[i] != '\0'; i++)  //if it does not contain the '\0' aka NULL character. Checks each bit if it does not contain '\0'

	 {
		if( buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') // if it contains space, a new line (enter), or tab, it will put a '\0' in its place
 
		{
			buf[i] = '\0';
		}
	}

	//parses arguments into buf
	int arg_iterator = 0;
	arguments[arg_iterator] = buf;
	buf++;
	arg_iterator++;


	for( int j = 1; j < i; j++ ) 
	{
		if( *buf == '\0' ) // if the last bit has the '\0', it goes through here

		 {
			arguments[arg_iterator] = buf+1; // adds 1 to the length because the is added '\0' to the end of the string so it it will have 1 more lenght

			arg_iterator++;
		}
		buf++;
	}

	arguments[arg_iterator] = 0;
}

void forking(char** arguments) //forking function
{

	int PID = fork();
	{
		if (PID == -1)  //-1 is returned in the parent, no child process is created
		{
			cerr << "Error creating a new process." << endl;
			exit(0);

		}

		if (PID == 0)  // the child, copy of the parents, makes a new process to excecute the inputed command

		{
			if( execvp(arguments[0], arguments) == -1 ) // if the command that is not listed is entered, error will print out

			{
				cerr << "execvp failed" << endl; //could not find the command or the command does not exist

				exit(1);
			}
		}
	
		else
		{
			wait(0);   //Parent waits for the child to finish
		
		}
	}




}



int main(int argc, char** argv)
{
	char buf[BUFSIZ];
	char* arguments[100];

	while(true) //loops the terminal so that you can enter different commands
	{
		char hostname[HOST_NAME_MAX];

		if (gethostname(hostname, sizeof hostname) == 0) // the host
		{
			char* buff;	
			buff = getlogin(); // the username of the person who logged in

			cout << getlogin() << "@" << (hostname) << " $ " << flush;
			cin.getline(buf, BUFSIZ);
		
			
			if (strcmp(buf, "exit") == 0) //exits the program
			{
				return 0; //exits the program by returning 0
			}
			else

			parsing(buf, arguments);
			forking(arguments);  //calls forking fuction
			


		}
  		  else
       			 perror("gethostname");

	}

	return 0;
}




