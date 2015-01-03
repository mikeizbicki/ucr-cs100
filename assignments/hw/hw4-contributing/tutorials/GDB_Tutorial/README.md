===

#Introduction to GDB
---

**Description**

GDB is a debugger that allows you to observe what is happening in a specific 
program. The purpose of this tutorial is to get familiar with the basic
GDB commands and their uses.

**Setup**

GDB is a tool that controls how a program runs. If you want to give GDB
access to the program, you need to compile the files using a specific flag.

Before you begin, GDB needs access to your program. In order to do this,
simply add the `-g` flag to the compile command.

For example, if your compile flags are:

` -W -Wall -Werror -ansi -pedantic`
 
a GDB compatible counterpart would be:

`-W -Wall -Werror -ansi -pedantic -g`

Next, you need to run GDB on the specific program you compiled. In bash,
type `gdb` followed by the program you wish to debug. 
For example: `gdb ./a.out`

**Runtime**

GDBs UI is similar to bash. You enter commands and arguments into the
prompt. After you start GDB, you can configure how the program will run with these
commands. To understand how this works, lets look at the following examples.

[Exercise 1](ex1/)

[Exercise 2](ex2/)

[Exercise 3](ex3/)
