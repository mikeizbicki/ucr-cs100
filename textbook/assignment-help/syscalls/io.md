#Input and Output System Calls
 
This markdown file demonstrates how to use the system calls `dup` , `dup2` and `pipe`.
This file contains code that we will be able to use to create simple programs that show us how to use `dup`, `dup2` and `pipe`.
 
###dup() and dup2()
The following is an example of how redirect standard out to a file using two different methods.
The two different methods of doing this are with the use of `dup()` or `dup2()`.
The source code on the `dup()` method can be found at [`io_dup.cpp`](./io_dup.cpp). 
The source code on the `dup2()` method can be found at [`io_dup2.cpp`](./io_dup2.cpp).

The first method we will be implementing is with the use of `dup`.

The code is ran by typing the following commands in the terminal.
```
$ g++ io_dup.cpp -o dup
$ ./dup
```
After running the program, a file named `filename.txt` is created and standard out is redirected to the file.
We can show this by typing the following command in the terminal.
```
$ cat filename.txt
```
This will display the following:
```
Standard Out is now a file.
```


Now that we know what the program is supposed to do, let's implement it.

We begin by opening a file that is used for writing only. 
We will be using the system call `open()` with the flags `O_WRONLY`, `O_CREAT`, and `O_TRUNC`.

```
int outfd = -1
    
outfd = open("filename.txt", O_WRONLY | O_CREAT | O_TRUNC);
    
if(outfd < 0)
{
    perror("open()" );
    exit(1);
}
```
In case we forgot what the flags mean:

`O_WRONLY`: This flag is an access mode that means write only.

`O_CREAT`: If the file does not exist, then it will be created.

`O_TRUNC`:  If the file already exists and the access mode allows writing it will be truncated to length 0.

Notice that output file descriptors (`outfd`) less than 0 are invalid and proper error checking is displayed.

We will now close `stdout` and the lowest available file descriptor will now become `STDOUT_FILENO`, which we know is the integer value 1. 
Once again, proper error checking is needed.

```
if(close(STDOUT_FILENO) < 0)
{
    perror("close()");
    close(outfd);
    exit(1);
}
```
We can now copy `outfd` onto `STDOUT_FILENO` and provide proper error checking.

```
if(dup(outfd) != STDOUT_FILENO)
{
    perror("dup()");
    close(outfd)
    exit(1)
}
```
The final step after everything has been successful is to close the original file:
```
close(outfd);
```
Remember: Closing files is very important!

Now that we know how to use `dup()` to redirect `stdout` to a file, using the `dup2()` method should be fairly simple.

The code for `dup2()` is ran by typing the following commands in the terminal.
```
$ g++ io_dup2.cpp -o dup2
$ ./dup2
```
This program serves the same purpose as the program above, so when we type the following into the terminal:
```
$ cat filename.txt
```
We should get a message on the terminal that says:
```
This statement will print within filename.txt.
```
This shows that `stdout` was redirected to the file.

Now that we know that it does the same job as the method above, let's see how the code differs.

We begin by opening a file that is used only for writing as we did above, but we replace the next two steps in the `dup()` method with the `dup2()` system call. 
To avoid confusion, the code should look like this:

```
outfd = open("filename.txt", O_WRONLY | O_CREAT | O_TRUNC);
    
if(outfd < 0)
{
    perror("open()" );
    exit(1);
}

if(dup2(outfd,1) < 0)
{
    return 1;
}
```
All we did was use the `dup2()` system call which takes in two file descriptors. 
The first paramater is the old file descriptor and the second parameter is the new file descriptor. With this simple code,standard out has now been redirected and we can now write to the file.


##pipe()
We will now write a simple program that uses `pipe()` as an interproccess communication between two processes. The full source code can be found at [`io_pipe.cpp`](./io_pipe.cpp).

The program can be ran by typing the following in the terminal:
```
$ g++ io_pipe.cpp -o pipe
$ ./pipe
```
The program will then output the following message to the terminal:
```
Parent Proccess
Child Process
Hello World!
```

First we will begin by declaring our `pipefd[2]` array.
We are also declaring a pid because we will be using two different processes in order to communicate between the both.
We also declare a `char` array named `buf` that has a size of 15 because it will hold the message `Hello World!`.
```
pid_t pid;
int pipefd[2];
char buf[15];
    
```
We can now create the pipe.
```
int ret = pipe(pipefd);
```
We now have to provide proper error checking for the pipe. A pipe returns -1 if an erro has been found so we should use the following for error checking.
```
if( ret == -1)
{
    perror ("pipe:" );
    exit(1);
}
```
We can now create our fork and provide proper error checking as well.
```
pid = fork() ;

if(pid == -1)
{
    perror("fork():");
        exit(1);
}
```
We can now use `pipefd[1]` to write our message to the buffer through the pipe. Remember that when we use 1 as our parameter we are at the write end of the pipe and when a 0 is used we are at the read end of the pipe.
Remember that when the `pid == 0` we are in the child proccess, so we will be writing in the child process. 

```
if(pid == 0) 
{
    printf("Child Process \n");
    write(ourpipefd[1], "Hello World!" , 12);   
}
```
We can now use `ourpipefd[0]` to read from one process to the other.
We will be reading from the parent process since the `pid == 1`.
We choose the value 13 so we make sure that we read the whole message.
```
else if(pid > 0)
{
    printf("Parent Process \n");
    read(ourpipefd[0], buf, 13);
    printf(buf);
}
```
This program will now read from the write end of the pipe and display `Hello World!` to the screen. 
This is a simple program, but it shows how `pipe()` can be used to communicate between processes.

This is the end of the tutorial, hopefully we now have a better understanding of what the input and output system calls are and how to use them.
