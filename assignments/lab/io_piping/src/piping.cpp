#include <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h> //perror
#include <stdlib.h> //exit
using namespace std;

int main()
{
    char* cmd[] = {"ls", NULL};
    char* cmd2[] = {"grep", "a.out", NULL};
    const int PIPE_READ = 0;
    const int PIPE_WRITE = 1;
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Error: pipe()");
    }
    int pid = fork();
    if(pid == -1)
    {
        perror("Error: fork()");
        exit(1);
    }
    else if(pid == 0)
    {
        if(close(fd[PIPE_READ]) == -1) //close the read end of the pipe since not using
        {
            perror("Error: close()");
        }
        if(dup2(fd[PIPE_WRITE], 1) == -1) //make stdout the write end of the pipe
        {
            perror("Error: dup2");
        }
        if(execvp(cmd[0], cmd) == -1)
        {
            perror("Error: execvp()");
        }
        exit(1); //prevents zombie process
    }
    else if(pid > 0)
    {
        //read end of the pipe
        int savestdin;
        if((savestdin = dup(0)) == -1)
        {
            perror("Error: dup");
        }
        if(wait(0) == -1)
        {
            perror("wait");
        }
        int pid2 = fork();
        if(pid2 == -1)
        {
            perror("Error: second fork()");
            exit(1);
        }
        else if(pid2 == 0)
        {
            if(close(fd[PIPE_WRITE]) == -1)
            {
                perror("Error: close()");
            }
            if(dup2(fd[PIPE_READ], 0) == -1)
            {
                perror("Error: dup2()");
            }
            if(execvp(cmd2[0], cmd2) == -1)
            {
                perror("Error: second execvp()");
            }
            exit(1);
        }
        else if(pid2 > 0)
        {
            if(close(fd[PIPE_WRITE]) == -1)
            {
                perror("Error: close()");
            }
            if(wait(0) == -1)
            {
                perror("Error: wait()");
            }
        }
        if(dup2(savestdin, 0) == -1)
        {
            perror("Error: dup2()");
        }
        return 0;
    }


