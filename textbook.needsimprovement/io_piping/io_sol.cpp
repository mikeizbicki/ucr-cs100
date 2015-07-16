#include <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <fcntl.h>
#include <stdio.h> //perror
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    //Output redirection
    int savestdout = dup(1);
    //open the file we want the output going to
    int fd = open("outfile.txt", O_WRONLY|O_CREAT|O_TRUNC, 00664);
    if(fd == -1)
    {
        perror("Error: open() in output");
    }
    if(dup2(fd, 1) == -1)
    {
        perror("Error: dup2 in output");
    }
    //cout << "fd: " << fd << endl;
    cout << "This should print to file" << endl;
    //restore output back to the terminal
    if(dup2(savestdout, 1) == -1)
    {
        perror("Error: dup()2");
    }
    //cout << "This should print to terminal" << endl;

    //input Redirection
    int savestdin = dup(0);
    //Open the file we are taking input from
    int fd2  = open("infile", O_RDONLY);
    if(fd2 == -1)
    {
        perror("Error: open() in input");
    }
    if(dup2(fd2, 0) == -1)
    {
        perror("Error: dup2() in input");
    }
    //restore input back to the terminal
    //if(dup2(savestdin, 0) == -1)
    //{
    //      perror("Error: dup2()");
    //}

    char** argv= new char*[1];
    argv[0] = new char[4];
    strcpy(argv[0], "sort");
    argv[1] = NULL;
    if(execvp(argv[0], argv) == -1)
    {
        perror("Error: execvp()");
    } 

    return 0;
}
