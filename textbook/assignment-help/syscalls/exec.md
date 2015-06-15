#System calls relating to the use of Exec

This markdown file will demonstrate how to use `exec` and the system calls needed to run `exec`.
These system calls include `fork`, `wait` and `exec` itself.
The examples below will show us how to use `fork` and `wait` individually and then we will use them together along with `exec`.
##fork()
The following is an example of how to use `fork`.
The source code can be found at [`exec_fork.cpp`](./exec_fork.cpp).

This is a simple program that show us how to create a `fork`.
The program then dislays the return value of the `fork` at the child and parent process.

The program can be ran by typing the following in the terminal:
```
$ g++ exec_fork.cpp -o fork
$ ./fork
```
Here is a terminal diplaying the ouput of the program:
![](http://i.imgur.com/f9UGWP7.png)

Now that we know what the program is supposed to do, let's implement it.

We can now create the `fork`.
```
pid_t pid = fork();
```

We now have to check the value of the `pid` to determine which process we are in.
We know what return values correspond to the parent process and child process.
Any number less than 0 will indicate the fork failed so we show that with:
```
if( pid < 0)
{
    perror("fork failed");
    exit(1);
}
```
We then check to see if the proccess is the child.
If the return value of `fork` is 0, then we are in the child process.
```
else if( pid == 0 )
{
    printf("Child: I'm the child: %d\n", pid);
}
```
We then check to see if the proccess is the parent.
If the return value of `fork` is greater than 0, then we are in the parent process.
The return value of `fork` here is the process id of the newly created child process.
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
Here is a terminal diplaying the ouput of the program:
![](http://i.imgur.com/oNjoHsw.png)

We begin again by declaring the `pid.`
This time we will be using two `pid` variables and a `status` variable.
The `status` variable is used so we can wait check the status of the child process.


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
We now check if the process is the child.
If this is the child process, we can wait by using the function `sleep()`.
The call to `sleep(3)` delays the child's exit by 3 seconds.
We can then exit the process after it is done sleeping.
We will be doing that by using `exit(12)`, which is an exit status.
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

We now check to see if the process is the parent process.
If we are in the parent process, we can wait for the child process to finish by using the `wait()` system call.
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
We can now use `fork` and `wait` together with `exec` to run a program within a process.
We will now use `execvp()` within a proccess to execute a program.
We will be connecting all three system calls for the following example.
The source code can be found at [`exec_code.cpp`](./exec_code.cpp).

This is a simple program that runs `ls` within the child process and the parent process will wait for the child process to finish.

The program can be ran by typing the following in the terminal:
```
$ g++ exec_code.cpp -o exec
$ ./exec
```
Here is a terminal diplaying the ouput of the program:
![](http://i.imgur.com/YMlBWXH.png)

We begin by declaring a `char *` array that will hold the job we want `execvp` to run.
In this case it will be `ls`.

```
char * args[2] = { "ls", NULL} ;
```

We will now declare the `pids` and `status` and create our `fork`.
```
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
At this point `ls` is going to run and display the files within the current directory onto the terminal.
```
else if (c_pid == 0)
{
    printf("Child: executing ls\n");
    execvp( args[0], args);
    perror("execvp failed");
}
```
Notice that we only want to show the `perror` when `execvp` fails.

We now check the parent process and `wait` until the child process finishes.
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
