#Chapter 1: writing shell commands

In this chapter, you will learn how certain shell commands like `ls` work, and you will be introduced to a number of debugging tools.
By the end of this chapter, you will use everything you've learned to implement the `ls` command yourself.

##Section 0: File Descriptors

Learn how to manipulate files with file descriptors, using the open, close, read, and write syscalls

* **fd.md**
	* open -  opens a file, returning a file descriptor for it.
	* close - closes the file descriptor, freeing it.
	* read - reads specified number of bytes from file descriptor. 
	* write - writes specified number of bytes from file descriptor.

* **fd_code.cpp** -  source code file for fd demo

* **fileold** -  example file for demo

##Section 1: Using stat

This section covers how to use stat and its variants, fstat and lstat, to get information on a file

* **stat.md** - 
covers the syscall stat, which returns a stat struct with information about the file

##Section 2: Bitwise Operators

Learn how bitwise operators allow you combine and pass in multiple flags.

* **bitwise-ops** - 
this section explains the logic behind bitwise operators and how it can be applied.


##Section 3 : Working with Directories
Learn how to manipulate directories with the opendir, readdir, and closedir syscalls

* **dir.md**
	* opendir - opens a directory, returning a DIR pointer
	* readdir - using a DIR pointer, reads the opened directory stream
	* closedir - closes the directory stream our DIR pointer is pointing towards.

* **dir_code.cpp** -
this file contains example source code for the dir demo


##Section 4: Getting Information

This section covers the getcwd, getpwuid, and getgrgid system calls

* **getinfo.md**
	* getcwd - gets the pathname of the current working directory
	* getpwuid - returns a passwd struct with information about the user
	* getgrgid - returns a group struct with information about the group


##Section 5 : Formatting Output
This section covers multiple techniques for formatting your program's output.

* **README.md**
	* setbase - set numerical base between octal, decimal, and hexadecimal
	* setw - adjust width of a column
	* setfill - change fill character when using setw
	* ANSI escape codes - bold, underline, and color text

* **ANSIfontUtils.h** - 
contains ready-to-use ANSI string codes.

##lab2 - fork

This lab covers correct use of the fork syscall, as well as creating and stopping fork bombs.  

##lab3 - gdb

Learn how to use gdb, a debugging program, for large and complex software. 

##hw1 - ls

Create your own version of the `ls` command, implementing flag options and other parameters.
 
