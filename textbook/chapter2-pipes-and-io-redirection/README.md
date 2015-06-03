#Chapter 2: Piping and I/O Redirection
In this chapter,  you will continue to use and manipulate file descriptors using two new functions in order to implement piping and input/output redirection.
In addition to this, you will use the skills you've learned so far to implement the `cp`,`rm`, and `mv` commands.

##Section 0 : I/O redirection 
This section covers how to use the `dup` and `pipe` functions.
* **io.md**
	* dup - duplicates a file descriptor and returns the new copy.
	* pipe - creates a pipe that can be written to and read from by other processes.


##lab4 - cp

In this lab, you'll create your own version of `cp`, and practice using git and strace.

##lab5 - rm

Implement both `mv` and `rm`, using the `link` and `unlink` syscalls for the former, and `rmdir` for the latter. 

##HW2 - Piping

Modify your rshell project to handle input/output redirection and piping.
