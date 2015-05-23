# I/O Redirection/Piping Lab

In this lab you will learn the basics and essentials to understand and implement I/O Redirection and piping using Linux.

Generally, when you enter a Unix command into the keyboard, you expect that the computer will be waiting for input and that output will be sent to the screen/terminal.
Using I/O Redirection can make programming for a beginner level programmer, even an expert level programmer, much faster and simplier.
You can use I/O Redirection to simply manipulate files within the command line or to check thousands of lines of output from a program.
Once you know the ins and outs of I/O Redirection, programming will be a breeze!

##What is I/O Redirection?

Often times, it can be necessary for input or output to be received from a file or another program rather than human input.
To do this, the bash shell uses the methods called:

* input redirection that redirects standard input (<),
* output redirection that appends standard output ( >> ), and
* output redirection that redirects standard output (>)

to achieve these goals.

The form of a command with standard input and output redirection is:

```c++
command -[options] [arguments] < input file > output file
```

For example open a terminal and try running:

```c++
$ ls > filename.txt
```

Notice the output from ls was sent to filename instead of directly to the terminal.

Now make a file using `touch outfile.txt` and add "This is the context of outfile." inside the file.
Now try running the commands:

```c++
$ cat < outfile.txt
```

You should see the text we added into outfile onto the terminal.
We redirected the text from outfile to output to the screen using input redirection.

No, it is not magic! 
But it is pretty useful to help keep track of testing your programs.

To understand how this works, we will first learn the Unix system calls required to build I/O Redirection, `open()`, `close()`, `dup()`, `dup2()`, and `pipe`.

###Using `dup()` and `dup2()`

To understand how to use the `dup()` and `dup2()` system calls, we look at the man page for all the basic information.

Basic Information:
Synopsis:
`#include <unistd.h>`
Description:
* `dup(int oldfd)` uses the lowest-numbered unused file descriptor for the new descriptor.
* `dup2(int oldfd, int newfd)` makes *newfd* be the copy of *oldfd*, closing *newfd* first if it has not already been closed.

Return Value:
On success, these system calls return the new file descriptor.
On error, -1 is returned and *errno* is set properly.

Refer to the dup/dup2 man page for more detailed information here:
[Man Page](https://man7.org/linux/man-pages/man2/dup.2.html "man")
Or refer to the textbook from the UCR software construction course Github:
[Textbook](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/textbook/assignment-help/syscalls/io.md)

####But how does `dup()` and `dup2()` work?

We read from the man page that dup uses the lowest-numbered unused file descriptor for the new file decriptor.
So what does this actually mean?

Well, by default, we have 3 file descriptors represented as integers.
* 0 for standard input or messages to the terminal
* 1 for standard output or messages you type to the terminal
* 2 for standard error

Note: From now on, we will refer to standard input, standard output, and standard error as stdin, stdout and stderr, respectively.

When unspecified, programs will take input from 0(by default stdin) and 1(by default stdout).
Now let us say we instead wanted to send all output to a file.
Well, since dup takes the LOWEST free number for a file descriptor, we need to free up file descriptor 1.
After freeing it, we can now use `dup()` to set out file as output.

But how do we free up a file descriptor you ask? By using the syscalls `open()` and `close()` of course!

####Using `open()` and `close()` System Calls

To understand the basics of the `open()` and `close()` system calls, we look at their man pages:

-------------------------------------------------------------------------------------

#####`open()`
Basic Information:

Synopsis:
`#include <sys/types.h>`,
`#include <sys/stat.h>`,
`#include <fcntl.h>`

Description:

`int open(const char *pathname, int flags)`

Given a pathname for a file, open() returns a file descriptor, a small, nonnegative integer.
The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.
The argument flags must include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR.
These request opening the file read-only, write-only, or read/write, respectively.

Return Value:
`open()` returns the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriately).

Refer to the `open()` man page for more detailed information here:
[Man Page](http://linux.die.net/man/2/open "man")

-------------------------------------------------------------------------------------

#####`close()`
Basic Information:

Synopsis:
`#include <sys/types.h>`,
`#include <sys/stat.h>`,
`#include <fcntl.h>`

Description:

`int close(int fd)`

`close()` closes a file descriptor, so that it no longer refers to any file and may be reused.

Return Value:
`close()` returns zero on success. On error, -1 is returned, and errno is set appropriately.


Refer to the `close()` man page for more detailed information here:
[Man Page](http://linux.die.net/man/2/close "man")

-------------------------------------------------------------------------------------

`dup()` and `dup2()` pair with these system calls to make functioning i/o Redirection.

Here is a picture and an example to illustrate this process:

INSERT PICTURE HERE LATER


Make a new program called `dup_example.cpp` that follows this code:

```c++
#include <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //perror
using namespace std;

int main()
{
	int savestdout = dup(1);
	//close file descriptor 1 so we can use it for output
	if(-1 == close(1))
	{
		perror("Error: close()");
	}
	//open the file we want the output going to
	int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
	if(-1 == fd)
	{
		perror("Error: open()");
	}
	if(dup(fd) == -1)
	{
		perror("Error: dup");
	}
	cout << "fd: " << fd << endl;
	cout << "This should print to file" << endl;
	//restore output back to the terminal
	if(-1 == close(1))
	{
		perror("Error: close()");
	}
	if(dup(savestdout) == -1)
	{
		perror("Error: dup()");
	}
	cout << "This should print to terminal" << endl;
	return 0;
}
```

Notice: We error check every system call we make.
ALWAYS REMEMBER TO ERROR CHECK!
You can find the return value of dup() and dup2() on the man pages.
They return -1 when there is an error.

Note that the value of fd is 1.
Now run:

`$ cat outfile`

And we should get:

`fd: 1`

printed to the screen.

We have successfully redirected to a file!

Equivalently, we can avoid the use of `close()` by using the `dup2()` system call.

`dup2()` works similarly to `dup()` except that it will close whatever the second parameter is, if it isn’t closed already.
In other words, we don’t necessarily have to call `close()` before we call `dup2()`.

So in our example, we can achieve the same results doing this:

```c++
#include <iostream>
#include <unistd.h> //dup and dup2
#include <sys/types.h> //open close
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //perror
using namespace std;

int main()
{
	int savestdout = dup(1);
	//open the file we want the output going to
	int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
	if(-1 == fd)
	{
		perror("Error: open()");
	}
	if(dup2(fd, 1) == -1)
	{
		perror("Error: dup");
	}
	cout << "This should print to file" << endl;
	//restore output back to the terminal
	if(dup2(savestdout, 1) == -1)
	{
		perror("Error: dup()");
	}
	cout << "This should print to terminal" << endl;
	return 0;
}
```
That concludes that `dup` and `dup2` tutorial.

Lab Exercise 1:
IN PROGRESS

##What are Pipes?

What exactly is a pipe?
Understanding what pipes are and how the system call pipe works is a bit confusing, so put down your phone and pay attention!

Using pipes makes navigating your terminal and using shortcuts SO much easier!
You can use pipes to run more that one command at once and pipes also connect the aspects of each command together!
With pipes, you can become an amazing hacker, maybe even unstoppable..
(Okay, maybe we will not go that far...)

In the terminal, we symbolize pipes with the pipe command: '|'.
Here is a quick example to walk through:

First, make a file in your current directory named `names.txt`. 
Then add these names to the file, each on a separate line: "Donna, Ann, Dan, Lauren, Leon, Beyonce, Eminem, 50 Cent, Maroon 5, Julia, Jessica, Diane, Megan, Michelle".

Now run the cat command to output the names of the file:

`$ cat names.txt`

As you can see the names are out of order.
If we want to sort the names, we can use the bash command `sort` to do so using a pipe.
To do so, run the command:

`$ cat name.txt | sort `

Now our names are sorted! 
Yay! :) 
What this command did was it connected the output of the cat process to the input of the sort process.
So it outputs the context of names.txt AFTER it sorts the contents of the file.

For a different example, we will search through the terminal history.
First type this command into your terminal:

`$ history`

Whoa, this prints out ALL your terminal history to stdout.
To shorten this output a little, or search for a specific command, in this case `g++`, we will use the grep command:

`$ history | grep 'g++'`

BOOM!!!
There is now a lot less history than before!
This command searches through your history and prints out where g++ was typed into the terminal.

Using the system call `pipe` creates a pipe, a one-way data channel that can be used for communication between two or more processes.
It takes stdout from the first process and links/pipes/channels/ it to the stdin to the other end of the pipe where the second process waits.

NEED TO EXPLAIN PIPE MORE

Here is an illistration to better understand pipe:

INSERT PICTURE/CHART HERE

###Using the `pipe()` System Call

First, we can look at the basics of the `pipe()` system call:

Basic Information

Synopsis: 

`#include <unistd.h>`

Description: 

`int pipe(int pipefd[2])`

`pipe()` creates a pipe, a unidirectional data channel that can be used for interprocess communication.
The array `pipefd` is used to return two file descriptors referring to the ends of the pipe.
`pipefd[0]` refers to the read end of the pipe.
`pipefd[1]` refers to the write end of the pipe.

Return value: 
On success, zero is returned. On error, -1 is returned, and errno is set appropriately.

Refer to the `pipe()` man page for more detailed information here:
[Man Page](https://man7.org/linux/man-pages/man2/dup.2.html "man")

Here is example code so we can better understand how pipes work:

(Maybe change the way this works)

```c++
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSGLEN  64

int main(){

    int     fd[2];
    pid_t pid;
    int     result;

    //Creating a pipe
    result = pipe (fd);
    if (result < 0) {
        //failure in creating a pipe
        perror("pipe");
        exit (1);
    }

    //Creating a child process
    pid = fork();
    if (pid < 0) {
         //failure in creating a child
         perror ("fork");
         exit(2);
    }

    if (pid == 0) {
        //Child process
         char message[MSGLEN];

          while(1) {
                    //Clearing the message
                    memset (message, 0, sizeof(message));
                    printf ("Enter a message: ");
                    scanf ("%s",message);

                    //Writing message to the pipe
                    write(fd[1], message, strlen(message));
            }
            exit (0);
    }
    else {
        //Parent Process
         char message[MSGLEN];

	while (1) {
	            //Clearing the message buffer
                    memset (message, 0, sizeof(message));

                    //Reading message from the pipe
                   read (fd[0], message, sizeof(message));
                    printf("Message entered %s\n",message);
            }

            exit(0);
     }
}
```
