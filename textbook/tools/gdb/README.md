Basic guide for GDB
===================

#####What is GDB?

GDB is the debugger that runs on many Unix-like systems which allows the user to trace and alter the execution of a program. One of the most useful GDB features is backtrace which gives a summary of how your program executed line by line. If your program crashes in GDB, typing backtrace will print out information about your crash and possibly the line numbers of the code that caused the crash. GDB helps the user to find and locate bugs such as segmentation faults or errors in output formating. However, it is important to note that GDB does nothing to find memory leaks. In order to find memory leaks, use tools such as valgrind and cppcheck. It is important to remember that GDB is only a tool to help a programmer debug their program, GDB does not ensure the program will be perfect or be free of all of the programs bugs.


#####Download GDB


To download and install GDB, click on the following links:

[Download GDB](http://www.gnu.org/software/gdb/download/)

[How to Install](http://www.tutorialspoint.com/gnu_debugger/installing_gdb.htm)

#####Using GDB

To use `gdb` properly, we need a compiled and executable program. If you have not downloaded the test program, `test.cpp`, do so now from the repository under in `src` folder. To download the examples from the github repository, run the command:


```
$ git clone https://github.com/kle016/gdb.git
```
After your download is finished, go ahead and get familiarized with GDB by working through the following examples. 

These examples will be covering `run`, `quit`, `help`, `breakpoint`, `info break`, `backtrace`, `delete`, `continue`, `next`, `step`, `finish`, `print`, and `list`. Additionally we will cover how `gdb` can automatically find `segfaults`.

(Note: Please do these examples in order because they build off of each other.)



[Example 1](ex1/)

[Example 2](ex2/)

[Example 3](ex3/)

[Example 4](ex4/)

Example 4 is optional as the topics covered are watch, record, and reverse which are rarely used as record and reverse use a lot of resources.
Watch however is useful in keeping track of variable and their values.

So now you know the very basics of GDB. With practice, you will be debugging like a pro and hopefully, `gdb` will end up saving you a lot of time!


