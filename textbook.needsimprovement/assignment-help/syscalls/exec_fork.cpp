#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    
    pid = fork();                                                                                                                                               

    if(pid < 0)
    {                                                                                                                                  
        perror("fork failed");
        exit(1);                                                                                                                                        
    }
    else if( pid == 0 )
    {
        printf("Child: I'm the child: %d\n", pid);
    }
    else if (pid > 0)
    {
        printf("Parent: I'm the parent: %d\n", pid);
    }

    return 0;                                                                                                                                                       
}
