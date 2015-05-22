# I/O Redirection/Piping Lab

In this lab you will learn the basics and essentials to understand and implement I/O Redirection and piping using Linux.

Generally, when you enter a Unix command into the keyboard, you expect that the computer will be waiting for input and that output will be sent to the screen/terminal.
Using I/O Redirection can make programming for a beginner level programmer, even an expert level programmer, much faster and simplier.
You can use I/O Redirection to simply manipulate files within the command line or to check thousands of lines of output from a program.
Once you know the ins and outs of I/O Redirection, programming will be a breeze!

##What is I/O Redirection?

###Using the dup() and dup2() Syscalls

Often times, it can be necessary for input or output to be received from a file or another program rather than human input.
To do this, shells use methods called:

* input redirection (<),
* output redirection that appends to files ( >> ), and
* output redirection (>)

to achieve these goals.
For example open a terminal and try running ls > filename.
Notice the output from ls was sent to filename instead of directly to the terminal.
No, it is not magic, but it is pretty useful.

To understand how this works, we will first learn the Unix system calls required to build I/O Redirection, `dup` and `pipe`.

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
[Textbook]https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/textbook/assignment-help/syscalls/io.md





