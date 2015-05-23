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

But how does `dup()` and `dup2()` work?

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

To understand the basics of the `open()` and `close()` system calls, we look at their man page:

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


