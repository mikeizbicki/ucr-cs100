###Example 1

**These excercises will cover the basic GDB commands.**

[Ex1](ex1.cpp) is a rough implementation of the `strcpy` function. It takes
two arguments, and the program copies the second argument onto the first.
Compile the file with the `-g` flag mentioned in the parent README.

If you pass in the arguments `hello` then `goodbye`, the output should be the following:

```
First: hello
Second: goodbye

COPY DONE

First: 
Second: goodbye
```

Clearly, the copy function is flawed. At first, you might want to make print
statements in the function that output each character. Unfortunately, this
can result in long outputs. Also, it's tedious to go back and add print
statements at various locations. In many cases, outputting specific elements
of data structures may result in very long outputs. 
This is where GDB is useful.

Run GDB on the binary executable you compiled. You can run the program by 
typing `r` of `run` followed by the arguments you wish to pass in.

```
$ wget https://github.com/ManjunathChet/GDB-Tutorial/blob/master/ex1/ex1.cpp
  # here you will get a confirmation from wget
$ g++ -g ex1.cpp
$ gdb a.out 

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
(gdb) r hello goodbye
Starting program: /class/classes/cmanj001/cs100/GDB-Tutorial/a.out hello goodbye
First: hello
Second: goodbye

COPY DONE

First: 
Second: goodbye
```

You can move through different parts of the program. Since we the
error seems to occur in the `my_strcpy` function, you can start there.

* Create a breakpoint where you think you should start looking.
  * Enter `b` or `break` followed by the line number where you want to place the break.
  If it was created you should see:
  `breakpoint 1 at 0x4007db: file ex1.cpp, line 19.`
  * Breakpoints are where the program "pauses". From here you can print different values.

```
(gdb)b 22
Breakpoint 1 at 0x4008aa: file ex1/ex1.cpp, line 22.
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

Next, you want to explore what values the variables hold. For this, we use
the print command. 

* To print, type `p` or `print` followed by the variable you wish to observe.
  *`p` is especially useful when working with data structures. 
  * Try it for yourself; print an array name, what do you see?

```
(gdb) p src
$1 = 0x7fffffffd1f2 "goodbye"
(gdb) p dst
$2 = 0x7fffffffd1ec "hello"
(gdb) p target_size
$3 = 7
```

Depending on where you are in the program, you can move through lines of code.
After entering a breakpoint, you can traverse the code that follows using `next`.
This is especially useful because the program continues to execute every line you move
to. 

* To move to the next line, enter `n` or `next`.
* GDB remembers the last command you ran. You dont have to re-enter the same command multiple times. Hit enter as many times as you wish to step.
* If you want to let the program run, type `c` or `continue`. It will run till it completes or hits the next break.

```
(gdb) continue
Continuing.

COPY DONE

First: 
Second: goodbye
[Inferior 1 (process 22293) exited normally]
(gdb) quit 
```

Using these commands, answer the following questions.

* What are the values of `src` and `dst` before and after the delete command?
* Is there a null pointer at the end of `dst` after the copy is complete?
