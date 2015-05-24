#Chapter 2: Piping and I/O Redirection
In this chapter,  you will continue to use and manipulate file descriptors using two new functions in order to implement piping and input/output redirection.
In addition to this, you will use the skills you've learned so far to implement the `cp`,`rm`, and `mv` commands.

##Section 0 : [I/O redirection](./section0-io-redirection) 
This section covers how to use the `dup` and `pipe` functions.
* [io.md](./section0-io-redirection/io.md)
	* `dup` - duplicates a file descriptor and returns the new copy.
	* `pipe` - creates a pipe that can be written to and read from by other processes.

* [io_dup.cpp](./section0-io-redirection/io_dup.cpp) - example code for `dup`.

* [io_dup2.cpp](./section0-io-redirection/io_dup2.cpp) - example code for `dup2`.

* [io_pipe.cpp](./section0-io-redirection/io_pipe.cpp) - example code for `pipe`.

##lab4 - [cp](./lab4-cp)

In this lab, you'll create your own version of `cp`, and practice using git and strace.

##lab5 - [rm](./lab5-rm)

Implement both `mv` and `rm`, using the `link` and `unlink` syscalls for the former, and `rmdir` for the latter. 

##HW2 - [Piping](./hw2-piping)

Modify your rshell project to handle input/output redirection and piping.
