#Chapter 1: writing shell commands

In this chapter, you will learn how certain shell commands like `ls` work, and you will be introduced to a number of debugging tools.
By the end of this chapter, you will use everything you've learned to implement the `ls` command yourself.

##Section 0: [File Descriptors](./section0-file-descriptors)

Learn how to manipulate files with file descriptors, using the `open`, `close`, `read`, and `write` syscalls

* [fd.md](./section0-file-descriptors/fd.md)
	* `open` -  opens a file, returning a file descriptor for it.
	* `close` - closes the file descriptor, freeing it.
	* `read` - reads specified number of bytes from file descriptor. 
	* `write` - writes specified number of bytes from file descriptor.

* [fd_code.cpp](./section0-file-descriptors/fd_code.cpp) -  source code file for fd demo

* [fileold](./section0-file-descriptors/fileold) -  example file for demo

##Section 1: [Using Stat](./section1-using-stat)

This section covers how to use `stat` and its variants, `fstat` and `lstat`, to get information on a file

* [stat.md](./section1-using-stat/stat.md) - 
covers the syscall `stat`, which returns a stat struct with information about the file

##Section 2: [Bitwise Operators](./section2-bitwise-operators)

Learn how bitwise operators allow you combine and pass in multiple flags.

* [bitwise-ops](./section2-bitwise-operators/bitwise-ops) - 
this section explains the logic behind bitwise operators and how it can be applied.


##Section 3 : [Working with Directories](./section3-working-with-directories)
Learn how to manipulate directories with the `opendir`, `readdir`, and `closedir` syscalls

* [dir.md](./section3-working-with-directories/dir.md)
	* `opendir` - opens a directory, returning a DIR pointer
	* `readdir` - using a DIR pointer, reads the opened directory stream
	* `closedir` - closes the directory stream our DIR pointer is pointing towards.

* [dir_code.cpp](./section3-working-with-directories/dir_code.cpp) -
this file contains example source code for the dir demo


##Section 4: [Getting Information](./section4-getting-information)

This section covers the `getcwd`, `getpwuid`, and `getgrgid` system calls

* [getinfo.md](./section4-getting-information/getinfo.md)
	* `getcwd` - gets the pathname of the current working directory
	* `getpwuid` - returns a passwd struct with information about the user
	* `getgrgid` - returns a group struct with information about the group


##Section 5 : [Formatting Output](./section5-formatting-output)
This section covers multiple techniques for formatting your program's output.

* [README.md](./section5-formatting-output/output-formatting-in-c++/README.md)
	* `setbase` - set numerical base between octal, decimal, and hexadecimal
	* `setw` - adjust width of a column
	* `setfill` - change fill character when using setw
	* ANSI escape codes - bold, underline, and color text

* [ANSIfontUtils.h](./section5-formatting-output/output-formatting-in-c++/ANSIfontUtils.h) - 
contains ready-to-use ANSI string codes.

##Section 6: [Valgrind](./section6-valgrind)
This section covers valgrind, a memory-checking tool you'll be expected to use from now on.

* [README.md](./section6-valgrind/README.md) - tutorial on how to use valgrind to detect memory leaks and errors.

* [example1.cpp](./section6-valgrind/example1.cpp) - this is an example file for the above valgrind tutorial.

* [example2.cpp](./section6-valgrind/example2.cpp) - this is another valgrind example file.

##lab2 - [fork](./lab2-fork)

This lab covers correct use of the `fork` syscall, as well as creating and stopping fork bombs.  

##lab3 - [gdb](./lab3-gdb)

Learn how to use gdb, a debugging program, for large and complex software. 

##hw1 - [ls](./hw1-ls)

Create your own version of the `ls` command, implementing flag options and other parameters.
 
