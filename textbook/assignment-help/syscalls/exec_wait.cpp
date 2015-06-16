#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

  pid_t c_pid, pid;
  int status;

  c_pid = fork();                                                                                                                                                


  if( pid < 0)
  {                                                                                                                           
    perror("fork failed");
    exit(1);                                                                                                                                        
  }


  else if( c_pid == 0 )
  {
   
    pid = getpid();

    printf("Child: %d: I'm the child\n", pid, c_pid);
    printf("Child: sleeping for 3 seconds \n");

    sleep(3);
    exit(12);

  }
  else if (c_pid > 0)
  {
    pid = wait(&status);

    if ( WIFEXITED(status) )
    {
      printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
    }

  }
  return 0;                                                                                                                                                        
}
