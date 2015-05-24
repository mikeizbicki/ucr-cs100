

###Example 2

From the `ex2` folder, compile `ex2.cpp` with the `-g` flag by using following command

```
$ g++ -g ex2.cpp
```

Then run `ex2.cpp` through `gdb` and create breakpoints at `main`, `bar`, and `foo`.

```
(gdb) break main
Breakpoint 1 at 0x4007fd: file ex2.cpp, line 18.
(gdb) b bar
Breakpoint 2 at 0x4007d6: file ex2.cpp, line 12.
(gdb) b foo
Breakpoint 3 at 0x4007b4: file ex2.cpp, line 7.

```


To remove all the breakpoints, type `delete` or `d` into the prompt of `gdb`. Then it will ask if you want to delete all the breakpoints. Type `y` for yes or `n` for no.

```
(gdb) delete
Delete all breakpoints? (y or n) y
(gdb) info break
No breakpoints or watchpoints.
(gdb)   
```


To check if the breakpoints where deleted properly, run  `info break`. `info break` displays information on all breakpoints that currently exist. If you deleted the breakpoints properly, `info break` will show that there are no breakpoints.

#####Stepping Through Code

Stepping lets you go through the code of the program so you will be able to narrow down the bug in your program.



The `next` command runs the next line of the program.

```
Breakpoint 1, main () at ex2.cpp:20
20		int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.
x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) n
22		cout << x << endl;
(gdb) n
0
23		bar(x);
(gdb) n
1
2
27		return 0;
(gdb) n
28	}
(gdb) 
```
The program continued off of breakpoint 1, which is line 20. The `next` command steps through the program one line at a time.

The `next` or `n` command also applies to functions. If the current line is on a fuction and you use `next`, the entire function will execute and then pause at the following line. Instead of executing line by line of the function.

```
Breakpoint 1, main () at ex2.cpp:20
20		int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.
x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) n
22		cout << x << endl;
(gdb) n
0
23		bar(x);
(gdb) n
1
2
27		return 0;
(gdb) n
28	}
(gdb) n
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) n
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 37248) exited normally]
(gdb) q
```


The `step` or `s` command allows you to progress through the code line by line. `step` will continue running the code line by line through the function until the function ends. After the function finishes, `step` will go back to the next line after the fuction call in the main body of the code and will continue to run the code line by line.

```
Breakpoint 1, main () at ex2.cpp:20
20		int x = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.
x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) s
22		cout << x << endl;
(gdb) s
0
23		bar(x);
(gdb) s
bar (x=@0x7fffffffce4c: 0) at ex2.cpp:13
13		x = x + 1;
(gdb) s
14		cout << x << endl;
(gdb) s
1
15		foo(x);
(gdb) s
foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
7		x = x + 1;
(gdb) s
8		cout << x << endl;
(gdb) s
2
9	}
(gdb) s
bar (x=@0x7fffffffce4c: 2) at ex2.cpp:16
16	}
(gdb) s
main () at ex2.cpp:27
27		return 0;
(gdb) s
28	}
(gdb) s
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 37278) exited normally]
(gdb) q

```

The `step` or `s` command has a similar use as `next`.However, `step` runs the function line by line unlike `next`.


Stepping through code line by line eliminates the need to have lines that print out statements showing that a specific line has been reached or the printing the contents of a variable. 


The `finish` or `f` command has a similar use as `continue`. `finish` allows you to complete the execution of a function that you have accessed by `step`. `finish` can save you time if you do not want to continue to run a function line by line.

```

22		cout << x << endl;
(gdb) s
0
23		bar(x);
(gdb) s
bar (x=@0x7fffffffce4c: 0) at ex2.cpp:13
13		x = x + 1;
(gdb) s
14		cout << x << endl;
(gdb) s
1
15		foo(x);
(gdb) s
foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
7		x = x + 1;
(gdb) finish          
Run till exit from #0  foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
2
bar (x=@0x7fffffffce4c: 2) at ex2.cpp:16
16	}
Value returned is $1 = 6295200
(gdb) s
```



`continue` or `c` is used to continue the program after reaching a breakpoint. The program will only stop when the program ends or reaches another breakpoint.


`backtrace` or `bt` prints the current contents of the stack at the current point in the execution of the program. The stack contains a list of processes that are yet to finish executing.


```
Breakpoint 3, bar (x=@0x7fffffffce4c: 0) at ex2.cpp:13
13		x = x + 1;
(gdb) bt
#0  bar (x=@0x7fffffffce4c: 0) at ex2.cpp:13
#1  0x000000000040093b in main () at ex2.cpp:23
(gdb) c
Continuing.
1

Breakpoint 2, foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
7		x = x + 1;
(gdb) bt
#0  foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
#1  0x0000000000400902 in bar (x=@0x7fffffffce4c: 1) at ex2.cpp:15
#2  0x000000000040093b in main () at ex2.cpp:23
(gdb) c
Continuing.
2
[Inferior 1 (process 37637) exited normally]

```


The command `print` or `p` prints of the contents of a specific variable in the program

```
(gdb) b foo
Breakpoint 1 at 0x40088c: file ex2.cpp, line 7.
(gdb) run
Starting program: /class/classes/dgoer001/hw4/ex2 
0
1

Breakpoint 1, foo (x=@0x7fffffffce4c: 1) at ex2.cpp:7
7		x = x + 1;
(gdb) print x
$1 = (int &) @0x7fffffffce4c: 1

```

The command `list` or `l` list ten lines of code for the current line that you are on.

`list` allows you to view the previous lines to check if the current line is running properly. In addtion, `list` allows you to see upcoming code, so you can anitcipate what you think should happen after the current line of code. Anticipating upcoming results in the code helps you distinguish between your desired results and the actual results.

```
(gdb) list
11	int bar(int &x)
12	{
13		x = x + 1;
14		cout << x << endl;
15		foo(x);
16	}
17	
18	int main()
19	{
20		int x = 0;
```

We are on line 15, which is in the middle of the listed ten lines of the code.

If you want to see code around a specific line of code, you would use `list N`, where `N` is the line number.

```
(gdb) list 5
1	#include <iostream>
2	
3	using namespace std;
4	
5	int foo(int &x)
6	{
7		x = x + 1;
8		cout << x << endl;
9	}
10	
```

Line 5 is in the middle of the listed out lines.

You can also use the `list` command on fuctions. You would type `list nameoffuction`, where `nameoffuction` is the fuction name.

```
(gdb) list bar
7		x = x + 1;
8		cout << x << endl;
9	}
10	
11	int bar(int &x)
12	{
13		x = x + 1;
14		cout << x << endl;
15		foo(x);
16	}
```






