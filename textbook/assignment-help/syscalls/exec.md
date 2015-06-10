#System calls relating to the use of Exec

This markdown file will demonstrate how to use `exec` and the system calls needed to run `exec`.
These system calls include `fork`, `wait` and `exec` itself. 
There are examples that will show us how to use `fork` and `wait` by themselves and then we will connect them together with `exec` to implement them all together.
##fork()
The following is an example of how to use `fork`.
The source code can be found at [`exec_fork.cpp`](./exec_fork.cpp).

This is a simple program that creates a child proccess from a parent process and it then displays the `pids` to the terminal.

The program can be ran by typing the following in the terminal:
```
$ g++ exec_fork.cpp -o fork
$ ./fork
```
The program will then output the following message to the terminal:
```
Parent: I'm the parent: parent pid
Child: I'm the child: 0
```
Where the `parent pid` will be a number, greater than 0, which corresponds to the parent's `pid`. 
The child's `pid` will always be 0.

Now that we know what the program is supposed to do, let's implement it.

We begin by declaring a `pid`.
```
pid_t pid;
```

We then duplicate the `pid` by using `fork`.
```
pid = fork();
```

We now have to check the value of the `pid` to determine which process we are in.
We know what values correspond to the parent process and child process. 
Any number less than 0 will indicate the fork failed so we show that with:
```
if( pid < 0)
{                                                                                                                           
    perror("fork failed");
    exit(1);                                                                                                                                        
}
```
We then check to see if the proccess is the child.
If it is, we want to print the `pid` of it.
```
else if( pid == 0 )
{
    printf("Child: I'm the child: %d\n", pid);
}
```
We then check to see if the proccess is the parent.
If it is, we want to print the `pid` of it.
```
else if (pid > 0)
{
    printf("Parent: I'm the parent: %d\n", pid);
}
```
That is all it takes to use `fork` properly.
We just have to make sure to check the `pid` and match it to the correct process.

##wait()
The following is an example of how to use `wait`.
The source code can be found at [`exec_wait.cpp`](./exec_wait.cpp).

This is a simple program that creates a child proccess from a parent process and the parent process then waits for the child process to finish.

The program can be ran by typing the following in the terminal:
```
$ g++ exec_wait.cpp -o wait
$ ./wait
```
The program will then output the following message to the terminal:
```
Child: *child pid*: I'm the child
Child: sleeping for 3 seconds.
Parent: Child exited with status: 12
```

We begin again by declaring the `pid.` 
This time we will be using two `pid` variables and a `status` variable, so we can wait for the child process to end.

```
pid_t c_pid, pid;
int status;
```
We now `fork` the process.
```
c_pid = fork();
```
We can now check to see whether the `fork` failed like we did before.
```
if( pid < 0)
{                                                                                                                           
    perror("fork failed");
    exit(1);                                                                                                                                        
}
```
We now check if the process is the child, so we can wait using the function `sleep()`.
We then need to exit the process after it is done sleeping and we will be doing that by using `exit(12)`, which is an exit status.
```
else if( c_pid == 0 )
{
    pid = getpid();

    printf("Child: %d: I'm the child\n", pid, c_pid);
    printf("Child: sleeping for 3 seconds \n");

    sleep(3);
    exit(12);
}
```

We now check to see if the process is the parent process, and we wait using the `wait()` system call.
```
else if (c_pid > 0)
{
    pid = wait(&status);

    if (WIFEXITED(status))
    {
        printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
    }
}
```
`WIFEITED` and `WEXITSTATUS` are macros that are used to check if the status is true or false compared to the status we used to exit within the child process.

That is how you use the system call `wait()` to get the parent proccess to wait until the child process is finished.

##exec()
The following is an example of how to use `exec`. 
Now that we know how to `fork` and `wait`. 
We will now use `execv()` and `execvp()` within a proccess to execute a program.
We will be connecting all three system calls for the following example.
The source code can be found at [`exec_code.cpp`](./exec_code.cpp).

This is a simple program that runs `ls` within the child process and the parent process will wait for its child to finish.

The program can be ran by typing the following in the terminal:
```
$ g++ exec_code.cpp -o exec
$ ./exec
```
The program will then output the following message to the terminal:
```
Child: executing ls
*files within directory*
Parent: finished
```

We begin by declaring a `char *` array that will hold the job we want `execvp` to run.
In this case it will be `ls`.
We also declare the `pids` and `status` like we did before.
We will then create our `fork`.
```
char * args[2] = { "ls", NULL} ;
pid_t c_pid, pid;
int status;
c_pid = fork();
```

We now check if the `fork` failed.
```
if( c_pid < 0)
{
    perror("fork failed");
    exit(1);
}
```

We now check if the process is the child and if it is, we want to run `execvp` with `ls` passed in as the parameter.
At this point `ls` is going to run and display the directories' contents on the terminal.
```
else if (c_pid == 0)
{
    printf("Child: executing ls\n");                                                                                                                                                                 
    execvp( args[0], args);                                                                                                                
    perror("execve failed");
}
```
Notice that we only want to show the `perror` when `execvp` fails.

We now check the parent process and `wait` like we did before, until the child process finishes.
```
else if (c_pid > 0)
{
    if( (pid = wait(&status)) < 0)
    {
        perror("wait");
        exit(1);
    }

    printf("Parent: finished\n");
}
```
This program is now complete and `ls` should run in the child process and the parent process should wait for the child to finish.

This is the end of the tutorial, hopefully we got a better understanding of how to use the system calls: `fork`, `wait` and `exec `.
