Basic guide for gdb
===================

#####What is gdb?

GDB is a debugger which allows the user to see what is going on inside of an executed program. If the written program crashes, the user can use GDB to step through the program to see where the program crashed. GDB helps the user to find and locate bugs such as segmentation faults, errors in output formatting, ect. However, gdb does not find memory leaks. In order to find memory leaks, tools such as valgrind and cppcheck should be used. One thing to remember while using GDB is that it is a tool to help a programmer debug a program. GDB does not ensure the program is perfect if ran with GDB.


#####GDB Download


To download and install GDB, click on the following links

[Download GDB](http://www.gnu.org/software/gdb/download/)

[How to Install](http://www.tutorialspoint.com/gnu_debugger/installing_gdb.htm)

#####Starting gdb

To use `gdb` properly, we need a compiled and executable program. If you have not downloaded the test program, `test.cpp`, do so now from the repository under in `src` folder. To download the examples from the github repository, run the command:


```
$ git clone https://github.com/kle016/gdb.git
```
Once downloaded, you can get familiarized with GDB by going through the following examples. 

These examples will be covering `run`, `quit`, `help`, `breakpoint`, `info break`, `backtrace`, `delete`, `continue`, `next`, `step`, `finish`, `print`, and `list`. In addition, you will learn how `gdb` can automatically find `segfaults`.

(Note: Please do these examples in order because they build off of each other.)



[Example 1](ex1/)

[Example 2](ex2/)

[Example 3](ex3/)



By practicing with these examples, you will be able to debug your future programs more efficiently rather than going through your code, line by line and trying to find bugs. You will save time by using `gdb`.



