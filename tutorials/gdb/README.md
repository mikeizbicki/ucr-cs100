Basic Tutorial for gdb
======================

#####What is gdb?

`gdb` is a debugger which allows the user to see what is going on inside of an executed program. If the written program has a bug, the user can use `gdb` to step through the program to locate the bug. `gdb` helps the user to find and locate bugs such as segmentation faults, errors in output formating, ect. However, gdb does not find memory leaks. In order to find memory leaks, tools such as valgrind and cppcheck should be used. One thing to remember while using `gdb` is that it is a tool to help a programmer debug a program. `gdb` does not ensure the program is perfect if ran with `gdb`.


#####gdb Download


To download and learn how to install `gdb`, click on the following links

[Download gdb](http://www.gnu.org/software/gdb/download/)

[How to Install](http://www.tutorialspoint.com/gnu_debugger/installing_gdb.htm)

#####Starting gdb

To use `gdb`, you will need a compiled and executable program, which is located in `src` folder. 

You can download the examples from the github repository, run the following command

```
$ git clone https://github.com/Daniel-Goerlich/gdb.git
```

Once downloaded, change directory into the `src` folder by running the following command

```
$ cd gdb/src
```
Now compile `ex1.cpp` with the following command 

```
$ g++ -g ex1.cpp
```
The `-g` flag enables the program to run inside of `gdb` for debugging. 

Once `ex1.cpp` compiles, you will start `gdb` with

```
$ gdb a.out
```
By entering in this command, you now are in the `gdb` debugging program. This command does not run the program but it opens the `a.out` file in `gdb`.

The prompt in `gdb` will look like

```
(gdb) 
```
You can enter commands after the `(gdb)` prompt.

#####Running Programs

Now you can to run the program in `gdb` by typing in `run` or `r`

```
(gdb) run
```

This runs the `a.out` that was loaded into `gdb` with the `gdb a.out` command from the terminal.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000
Enter first number
2
Enter second nunber
4
2 times 4 equals 8

Program exited normally.
(gdb)   
```

Another way to run the program though `gdb` is to pass in arguments.
```
(gdb) r arg1 arg2
```

This runs the program with `arg1` and `arg2` as command line parameters.

#####Exiting Out of gdb

To exit out of `gdb`, all you have to do is type `quit` or `q` in the prompt. It brings you back to your current working directory.

```
(gdb) quit
```

#####Automatic Segfault Detection

`gdb` is capable of automatically detecting segfaults. This is demonstrated by `gdb` from the following link. 

[Automatic Segfault Detection](segfault_detection/)

However, `gdb` cannot automatically locate all segfaults. If `gdb` does not find the segfault for you, use `gdb` to find the segfault like any other bug.



#####Breakpoints and Continue

You can create breakpoints in `gdb`. A breakpoint causes a pause (break) in the program when it reaches a certain point.

Breakpoints stop the program before executing the line number.

To create breakpoints, type `break` or `b` in the `gdb` prompt followed by the line number that you want to pause (break) at.

In addition, breakpoints can be set at a specific line by entering a function name instead of a line number. When a function name is passed in GDB, it will put a breakpoint where the function name is found in the code.

```
(gdb) break 10
Breakpoint 1 at 0x40092d: file test.cpp, line 10.
```
As you can see, it creates a breakpoint on line 10.

When you `run` the program, it will output

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb)
```
Notice how the program pauses here at line 10. Line 10 has not been executed yet. It is because the breakpoint was set here on line 10, so it paused the program on line 10.

This is useful because it prevents other lines of code from executing so that you can inspect the variables and execution of the program.

If you want to continue the program, type in `continue` or `c` in the prompt
 
```
(gdb) continue
Continuing.
Enter first number
```

The `continue` command will execute the program from the breakpoint, which is line 10. Once the `continue` command is ran, the program will execute line 11, which is `Enter first number`.

You can make multiple breakpoints in the program through `gdb`. To make another breakpoint in the program, type `breakpoint` followed by the line number or the name of a function. By setting another breakpoint, you are able to pause at another line in the program.

```
(gdb) break 12
Breakpoint 2 at 0x400957: file test.cpp, line 12.
```
Now there are two breakpoints on `ex1.cpp`. Now run the program from `gdb` by typing `run` in the prompt. This will run the program until breakpoint 1 is reached.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb)
```
The program pauses at `Breakpoint 1`, which is the first breakpoint. To continue on to the next breakpoint, type `continue` in the prompt. The program will continue until the next breakpoint, which is on line 12.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb) continue
Continuing.
Enter first number
6

Breakpoint 2, main () at test.cpp:12
12      cout << "Enter second nunber" << endl;
(gdb)       
```
If you want to see all the breakpoints that you have made and the number of times you have reached each breakpoint, type `info break` into the prompt.

```
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040092d in main() at test.cpp:10
        breakpoint already hit 1 time
2       breakpoint     keep y   0x0000000000400957 in main() at test.cpp:12
        breakpoint already hit 1 time
(gdb)      
```


To delete a breakpoint, type `delete N`, where `N` is the breakpoint number.

```
(gdb) delete 2
```
As you can see, we deleted 2, which was breakpoint 2. Then we used `info break` to confirm that it has been deleted.

```
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040092d in main() at test.cpp:10
        breakpoint already hit 1 time
(gdb) 
```

You can also set breakpoints on fuctions. To set breakpoints on fuctions, you will need to type out the name of the fuction right after `break`

```
(gdb) break nameofthefuction
```

Using `break` with the name of a function, will set a breakpoint wherever the name of the function appears in the program.

Now compile `ex2.cpp` and run it through `gdb` with the following command

```
$ g++ -g ex2.cpp
$ gdb a.out
```

Then create breakpoints at `main`, `bar`, and `foo`. Then run `ex2.cpp`.

```
(gdb) break main
Breakpoint 1 at 0x4007fd: file test.cpp, line 18.
(gdb) break bar
Breakpoint 2 at 0x4007d6: file test.cpp, line 12.
(gdb) break foo
Breakpoint 3 at 0x4007b4: file test.cpp, line 7.
(gdb) run
Starting program: /class/classes/dgoer001/./a.out 

Breakpoint 1, main () at test.cpp:18
18		cout << "test1" << endl;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) c
Continuing.
test1

Breakpoint 2, bar () at test.cpp:12
12		cout << "test2" << endl;
(gdb) c
Continuing.
test2

Breakpoint 3, foo () at test.cpp:7
7		cout << "test3" << endl;
(gdb) c
Continuing.
test3
[Inferior 1 (process 32517) exited normally]
(gdb) q

```


The `delete` or `d` command removes all the breakpoints which you have created. Type `delete` or `d` into the prompt of `gdb`. Then it will ask if you want to delete all the breakpoints. Type `y` for yes or `n` for no.

```
(gdb) delete
Delete all breakpoints? (y or n) y
(gdb) info break
No breakpoints or watchpoints.
(gdb)   
```


To check if the breakpoints where deleted properly, run  `info break`. `info break` displays information on all breakpoints that currently exist. After you deleted all the breakpoints, `info break` will show that there are no breakpoints remaining.

```
(gdb) info break
No breakpoints or watchpoints.
```

#####Stepping Through Code

Stepping through your code lets you narrow down the bug(s) in your program.

The `step` or `s` command allows you to progress through code, line by line through the main body of code and functions until the program ends.

```
(gdb) run
Starting program: /class/classes/dgoer001/gdb/src/a.out 

Breakpoint 1, main () at ex2.cpp:20
20	  int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) s
22	  cout << x << endl;
(gdb) s
0
23	  bar(x);
(gdb) s
bar (x=0) at ex2.cpp:13
13	  x = x + 1;
(gdb) s
14	  cout << x << endl;
(gdb) s
1
15	  foo(x);
(gdb) bt
#0  bar (x=1) at ex2.cpp:15
#1  0x0000000000400829 in main () at ex2.cpp:23
(gdb) s
foo (x=1) at ex2.cpp:7
7	  x = x + 1;
(gdb) s
8	  cout << x << endl;
(gdb) s
2
9	}
(gdb) bt
#0  foo (x=2) at ex2.cpp:9
#1  0x00000000004007f2 in bar (x=1) at ex2.cpp:15
#2  0x0000000000400829 in main () at ex2.cpp:23
(gdb) s
bar (x=1) at ex2.cpp:16
16	}
(gdb) s
main () at ex2.cpp:27
27	  return 0;
(gdb) bt
#0  main () at ex2.cpp:27
(gdb) s
28	}
(gdb) s
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 23014) exited normally]
```
Stepping through the code eliminates the need to have print statements showing a specific line that has been reached.

The `finish` or `f` command has a similar use as `continue`. However, `finish` allows you to complete the execution of a function that you have already accessed by `step`. `finish` can save you time if you do not want to continue to execute a function line by line.

```
(gdb) run
Starting program: /class/classes/dgoer001/gdb/src/a.out

Breakpoint 1, main () at ex2.cpp:20
20 int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) s
22 cout << x << endl;
(gdb) s
0
23 bar(x);
(gdb) s
bar (x=0) at ex2.cpp:13
13 x = x + 1;
(gdb) finish
Run till exit from #0 bar (x=0) at ex2.cpp:13
1
2
main () at ex2.cpp:27
27 return 0;
(gdb) s
28 }
(gdb) s
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 21971) exited normally]
```

The `next` or `n` command applies to functions, unlike `step`. If the current line is on a fuction and you use `next`, the entire function will execute and then pause at the following line, instead of executing line by line through the function.

```
(gdb) run
Starting program: /class/classes/dgoer001/gdb/src/a.out

Breakpoint 1, main () at ex2.cpp:20
20 int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) n
22 cout << x << endl;
(gdb) n
0
23 bar(x);
(gdb) n
1
2
27 return 0;
(gdb) n
28 }
(gdb) n
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) n
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 21844) exited normally]

```

#####Backtracing

`backtrace` or `bt` prints the current contents of the stack at the current point in the execution of the program. The stack contains a list of processes that are yet to finish executing.

Backtracing at the point of a bug can help isolate the bug, because it narrows it down to the function or the line that caused the bug. 

```
(gdb) run
Starting program: /class/classes/dgoer001/gdb/src/a.out 

Breakpoint 1, main () at ex2.cpp:20
20	  int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) s
22	  cout << x << endl;
(gdb) s
0
23	  bar(x);
(gdb) s
bar (x=0) at ex2.cpp:13
13	  x = x + 1;
(gdb) s
14	  cout << x << endl;
(gdb) s
1
15	  foo(x);
(gdb) bt
#0  bar (x=1) at ex2.cpp:15
#1  0x0000000000400829 in main () at ex2.cpp:23
(gdb) s
foo (x=1) at ex2.cpp:7
7	  x = x + 1;
(gdb) s
8	  cout << x << endl;
(gdb) s
2
9	}
(gdb) bt
#0  foo (x=2) at ex2.cpp:9
#1  0x00000000004007f2 in bar (x=1) at ex2.cpp:15
#2  0x0000000000400829 in main () at ex2.cpp:23
(gdb) s
bar (x=1) at ex2.cpp:16
16	}
(gdb) s
main () at ex2.cpp:27
27	  return 0;
(gdb) bt
#0  main () at ex2.cpp:27
(gdb) s
28	}
(gdb) s
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 23014) exited normally]
```

#####Conclusion

The examples in this tutorial covered `run`, `quit`, `breakpoint`, `info break`, `backtrace`, `delete`, `continue`, `step`, `next`,and `finish`. In addition, you have seen how `gdb` automatically finds `segfaults`.

By working with these examples, you will be able to debug your future programs more efficiently rather than going through your code, line by line, and trying to find bugs manually. You will save time by using `gdb`.

`gdb`is a powerful debugging tool for programmers of all calibers.
