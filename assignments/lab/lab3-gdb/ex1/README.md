###Exercise 1: gdb basics

The file [`ex1.cpp`](ex1.cpp) contains a function called `my_strcpy` (that is supposed to behave like the built-in `strcpy` function) and a simple test case.
Compile the program with the command:
```
$ g++ -g ex1.cpp -o ex1
```
The `-g` option tells `g++` to include "debugging symbols" into the executable.
These symbols let `gdb` give more informative error messages.
If you are getting weird output from gdb, you probably forgot to add the `-g` flag to `g++`.

Then run the executable with the command:
```
$ ./ex1 goodbye hello
```
This tells the `ex1` program to copy the `hello` string into the `goodbye` string.
You should get the following output:
```
First: goodbye
Second: hello

COPY DONE

First:
Second: hello
```

This is incorrect.
If you look at the source code, you can figure out that the result after `COPY DONE` should read:
```
First: goodbye
Second: goodbye
```
So our `my_strcpy` function has a bug.
And we're going to use `gdb` to find it!

`gdb` takes a single parameter, which is the *executable* file we want to debug.
A common beginner mistake is to run `gdb` on the source file instead.
Start `gdb` with the following command:
```
$ gdb ./ex1
```
And you'll get the following output:
```
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-47.el6
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /class/classes/cmanj001/cs100/GDB-Tutorial/a.out...done.
(gdb)
```
The `(gdb)` string at the end is the prompt.
This is where we type our commands.

The `run` (or `r`) command starts our program:
```
(gdb) r goodbye hello
```
The `goodbye` and `hello` strings get passed as arguments to our `ex1` program.
You should get the output:
```
Starting program: /class/classes/cmanj001/cs100/GDB-Tutorial/a.out goodbye hello
First: goodbye
Second: hello

COPY DONE

First:
Second: hello
```

"Breakpoints" are the main tool `gdb` provides to help us debug programs.
`gdb` will pause our program at breakpoints, and let us inspect the values of the variables.
We create breakpoints with the `breakpoint` (or `b`) command followed by the line number to create the breakpoint.

Let's set a "breakpoint" inside the `my_strcpy` function:
```
(gdb) b 25
Breakpoint 1 at 0x4008aa: file ex1/ex1.cpp, line 25.
```

Now, let's rerun our program:
```
(gdb) r hello goodbye
Starting program: /class/classes/cmanj001/cs100/GDB-Tutorial/a.out hello goodbye
First: hello
Second: goodbye

Breakpoint 1, my_strcpy (dst=0x7fffffffd1ec "hello", src=0x7fffffffd1f2 "goodbye") at
ex1/ex1.cpp:25
25      for(i = 0; src[i] != '\0'; ++i)
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64
libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
```

We've stopped just before line 25, but have NOT yet executed that line.
Next, we want to explore what values the variables hold.
For this, we use the `print` (or `p`) command followed by the variable we want to display:
```
(gdb) p src
$1 = 0x7fffffffd1f2 "hello"

(gdb) p dst
$2 = 0x7fffffffd1ec "goodbye"

(gdb) p target_size
$3 = 7
```
You can use `p` on any C++ variable to inspect it at run time.

The `continue` (or `c`) command restarts the program after a break point.
The program will continue to run until another breakpoint is reached, or the program exits normally.
If we type continue now, we get:
```
(gdb) continue
Continuing.

COPY DONE

First:
Second: goodbye
[Inferior 1 (process 22293) exited normally]
(gdb) quit
```
Another important command is the `next` (or `n`) command.
This causes `gdb` to execute only a single line and stop.
`continue` will execute many lines, but `next` will only execute one.

Using these `gdb` commands, answer the following questions on a piece of paper:

1. What are the values of `src` and `dst` before and after the delete command on line 32?

2. Is there a null terminating character (`'\0'`) at the end of `dst` after the copy is complete?

3. How should you fix the code?

**IMPORTANT:**
Beginners often don't see the benefit of using `gdb` and the `p` command.
They ask: "Why go through all the hassle of `gdb` when I can just use `cerr` statements to print the variables?"
Both methods work on small projects.
But on large projects, you often don't even know what variables you need to inspect until you get to that section of code.
In this case, `cerr` statements are useless and you need `gdb`.
With practice, you'll be much faster at debugging using `gdb` than you would be with `cerr` statements.
**If you ever catch yourself putting in `cerr` statements, switch to using `gdb`!**
At first it will be slower, but soon you'll be a much faster debugger.

