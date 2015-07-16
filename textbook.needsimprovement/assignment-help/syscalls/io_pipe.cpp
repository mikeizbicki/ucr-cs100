#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    pid_t pid;
    int pipefd[2];
    char buf[15];
    
    int ret = pipe(pipefd);
    
    if(ret == -1)
    {
        perror("pipe():");
        exit(1);
    }
    
    pid = fork();
    
    if(pid == 0)
    {
        printf("Child Process \n");
        write(pipefd[1], "Hello World!", 12);
    }
    else if( pid < 0)
    {
        perror("fork");
        exit(1);
    }

    else if( pid > 0)
    {
        printf("Parent Process \n");
        read(pipefd[0], buf, 13);
        printf(buf);
        cout << endl;
    }
    
    return 0;
}
