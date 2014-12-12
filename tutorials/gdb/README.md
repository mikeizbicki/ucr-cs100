Basic guide for gdb
===================

#####What is gdb?

GDB is a debugger which allows the user to see what is going on inside of an executed program. If the written program crashes, the user can use GDB to step through the program to see where the program crashed. GDB helps the user to find and locate bugs such as segmentation faults, errors in output formating, ect. However, gdb does not find memory leaks. In order to find memory leaks, tools such as valgrind and cppcheck should be used. One thing to remember while using GDB is that it is a tool to help a programmer debug a program. GDB does not ensure the program is perfect if ran with GDB.


#####GDB Download


To download and install GDB, click on the following links

[Download GDB](www.gnu.org/software/gdb/download/)

[How to Install](http://www.tutorialspoint.com/gnu_debugger/installing_gdb.htm)

#####Starting gdb

To use `gdb` properly, we need a compiled and executable program. If you have not downloaded the test program, `test.cpp`, do so now from the repository under in `src` folder. Once downloaded, so you can get familiarized with GDB.

```
#include <iostream>

using namespace std;

int main()
{

int x;
int y;

cout << "Enter first number" << endl;
cin >> x;
cout << "Enter second nunber" << endl;
cin >> y;

int z = x * y;
cout << x << " times " << y << " equals " << z << endl;

return 0;
}
```
Now compile `test.cpp` with the following command 

```
$ g++ -g test.cpp
```
The `-g` flag enables the program to be run with `gdb`. The `-g` allow the usage of `gdb` for debugging and can track the uses variables and fuctions in `gdb`.

Once `test.cpp` compiles, we will start `gdb` with

```
$ gdb ./a.out
```
By entering in this command, you now are in the `gdb` debugging program. This command does not run the program but it opens the `a.out` file in `gdb`.

The prompt in `gdb` will look like

```
(gdb) 
```
You can enter commands after the `(gdb)`

#####Running the program

Now you want to run the program in `gdb`. Type `run` or `r` to run the program.

```
(gdb) run
```
Remember that the commands go after the `(gdb)`.
This runs the `a.out` that was loaded into gdb with the `gdb ./a.out` command from the terminal.

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
r arg1 arg2
```

This runs the program with `arg1` and `arg2` as command line parameters.

#####Breakpoints

You can create breakpoints in `gdb`. A breakpoint causes a pause (break) in the program when it reaches a certain point.

Breakpoints stop the program before executing the line number.

To use breakpoints, type `break` or `b` in the `gdb` prompt followed by the line number that you want to pause (break) at.

In addition, breakpoints can be set at a specific line by entering a phrase instead of a line number. When a phrase is passed in GDB, it will put a breakpoint where the phrase is found in the code.

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

By typing in `continue` in the prompt, the program will execute from the breakpoint, which is line 10. The program executes line 11, which is `Enter first number`.

You can make multiple breakpoints in the program through `gdb`. To make another breakpoint in the program, type `breakpoint` followed by the line number. By setting another breakpoint, you are able to pause at another line in the program.

```
(gdb) break 12
Breakpoint 2 at 0x400957: file test.cpp, line 12.
```
Now there are two breakpoints in `test.cpp` through GDB. Now run the program from `gdb` by typing `run` in the prompt. This will run the program until breakpoint 2 is reached.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb)
```
The program paused at `Breakpoint 1`, which is the first breakpoint. To continue on to the next breakpoint, type `continue` in the prompt. The program will continue until the next breakpoint, which is line 12.

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
If you want to see all the breakpoints that you have made, type `info break` into the prompt.

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
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040092d in main() at test.cpp:10
        breakpoint already hit 1 time
(gdb)    
```
As you can see, we deleted 2, which was breakpoint 2. Then we used `info break` to confirm that it has been deleted.



You can also set breakpoints on fuctions or phrase. To set breakpoints on fuctions or phrase, you need to type out the name of the fuction or phrase right after the `break`

```
(gdb) break nameofthefuction
```

Using `break` with the name of a function or a phrase, will set a breakpoint wherever the name of the function or phrase appears in the code.

Now download `test2.cpp` from the repository in the `src` folder and compile it. Start up GDB then `test2.cpp` through `gdb` and create breakpoints at `main`, `bar`, and `foo`. Then run `test2.cpp`.

```

(gdb) break main
Breakpoint 1 at 0x4007fd: file test.cpp, line 18.
(gdb) b bar
Breakpoint 2 at 0x4007d6: file test.cpp, line 12.
(gdb) b foo
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

The command `list` or `l` list ten lines of code for the current line that you are on.

`list` allows you to view the previous lines to check if the current line is running properly. In addtion, `list` allows you to see upcoming code, so you can anitcipate what you think should happen after the current line of code. Anticipating upcoming results in the code helps you distinguish between your desired results and the actual results.

```
(gdb) list
5       {
6
7       int x;
8       int y;
9
10      cout << "Enter first number" << endl;
11      cin >> x;
12      cout << "Enter second nunber" << endl;
13      cin >> y;
14
(gdb)    
```

We are on line 10, which is in the middle of the listed ten lines of the code.

If you want to see code around a specific line of code, you would use `list N`, where `N` is the line number.

```
(gdb) list 5
1       #include <iostream>
2       using namespace std;
3
4       int main()
5       {
6
7       int x;
8       int y;
9
10      cout << "Enter first number" << endl;
(gdb)     
```

Line 5 is in the middle of the listed out lines.

You can also use the `list` command on fuctions. You would type `list nameoffuction`, where `nameoffuction` is the fuction name.

The `next` command runs the next line of the program.

```
Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb) next
Enter first number
11      cin >> x;
(gdb) next
2
12      cout << "Enter second nunber" << endl;
(gdb) next
Enter second nunber
13      cin >> y;
(gdb) next
7
15      int z = x * y;
(gdb) next
16      cout << x << " times " << y << " equals " << z << endl;
(gdb) next
2 times 7 equals 14
18      return 0;
(gdb) next
19      }
(gdb) 
```
The program continued off of breakpoint 1, which is line 10. The `next` command steps through the program one line at a time.

The `next` or `n` command also applies to functions. If the current line is on a fuction and you use `next`, the entire function will execute and then pause at the following line. Instead of executing line by line of the function.

The `step` or `s` command has a similar use as `next`. `step` allows you to progress through the code line by line just like `next`. However, `step` runs the function line by line unlike `next`. `step` will continue running the code line by line through the function until the function ends. After the function finishes, `step` will go back to the next line after the fuction call in the main body of the code and will continue to run the code line by line.

Stepping through code line by line eliminates the need to have lines that print out statements showing that a specific line has been reached or the printing the contents of a variable. 

The `finish` or `f` command has a similar use as `run`. `finish` allows you to complete the execution of a function that you have accessed by `step`. `finish` can save you time if you do not want to continue to run a function line by line.

#####Backtracing

`backtrace` or `bt` prints the current contents of the stack at the current point in the execution of the program. The stack contains a list of processes that are yet to finish executing.

Now download `test2.cpp` from the repository in the `src` folder and compile it. Then run `test2.cpp` through `gdb`.

By running `test2.cpp` in GDB, `step` and `backtrace` work well together. 

```

(gdb) run
Starting program: /class/classes/dgoer001/./a.out 

Breakpoint 1, main () at test.cpp:18
warning: Source file is more recent than executable.
18		cout << "test1" << endl;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) s
test1
19		bar();
(gdb) s
bar () at test.cpp:12
12		cout << "test2" << endl;
(gdb) backtrace
#0  bar () at test.cpp:12
#1  0x000000000040081e in main () at test.cpp:19
(gdb) s
test2
13		foo();
(gdb) s
foo () at test.cpp:7
7		cout << "test3" << endl;
(gdb) bt
#0  foo () at test.cpp:7
#1  0x00000000004007f7 in bar () at test.cpp:13
#2  0x000000000040081e in main () at test.cpp:19
(gdb) s
test3
8	}
(gdb) bt
#0  foo () at test.cpp:8
#1  0x00000000004007f7 in bar () at test.cpp:13
#2  0x000000000040081e in main () at test.cpp:19
(gdb) s
bar () at test.cpp:14
14	}
(gdb) bt
#0  bar () at test.cpp:14
#1  0x000000000040081e in main () at test.cpp:19
(gdb) s
main () at test.cpp:20
20		return 0;
(gdb) bt
#0  main () at test.cpp:20
(gdb) s
21	}
(gdb) bt
#0  main () at test.cpp:21
(gdb) s
0x000000305081ed5d in __libc_start_main () from /lib64/libc.so.6
(gdb) s
Single stepping until exit from function __libc_start_main,
which has no line number information.
[Inferior 1 (process 28909) exited normally]

```
#####Print


`print` or `p` prints of the contents of a specific variable in the program

#####Continue

`continue` or `c` is used to continue the program after reaching a breakpoint. The program will only stop when the program ends or reaches another breakpoint.


#####Help

`help` or `h` brings up the help topics. It shows a list of commands that you might need help on.

```
(gdb) help
List of classes of commands:

aliases -- Aliases of other commands
breakpoints -- Making program stop at certain points
data -- Examining data
files -- Specifying and examining files
internals -- Maintenance commands
obscure -- Obscure features
running -- Running the program
stack -- Examining the stack
status -- Status inquiries
support -- Support facilities
tracepoints -- Tracing of program execution without stopping the program
user-defined -- User-defined commands

Type "help" followed by a class name for a list of commands in that class.
Type "help all" for the list of all commands.
Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb)    
```
If you need help on `breakpoints`, type `help breakpoints` into the prompt. `gdb` will print out information on `breakpoints`.

```
(gdb) help breakpoints
Making program stop at certain points.

List of commands:

awatch -- Set a watchpoint for an expression
break -- Set breakpoint at specified line or function
catch -- Set catchpoints to catch events
catch assert -- Catch failed Ada assertions
catch catch -- Catch an exception
catch exception -- Catch Ada exceptions
catch exec -- Catch calls to exec
catch fork -- Catch calls to fork
catch syscall -- Catch system calls by their names and/or numbers
catch throw -- Catch an exception
catch vfork -- Catch calls to vfork
clear -- Clear breakpoint at specified line or function
commands -- Set commands to be executed when a breakpoint is hit
condition -- Specify breakpoint number N to break only if COND is true
delete -- Delete some breakpoints or auto-display expressions
delete breakpoints -- Delete some breakpoints or auto-display expressions
delete checkpoint -- Delete a checkpoint (experimental)
delete display -- Cancel some expressions to be displayed when program stops
delete mem -- Delete memory region
---Type <return> to continue, or q <return> to quit---
delete tracepoints -- Delete specified tracepoints
disable -- Disable some breakpoints
disable breakpoints -- Disable some breakpoints
disable display -- Disable some expressions to be displayed when program stops
disable mem -- Disable memory region
disable tracepoints -- Disable specified tracepoints
enable -- Enable some breakpoints
enable delete -- Enable breakpoints and delete when hit
enable display -- Enable some expressions to be displayed when program stops
enable mem -- Enable memory region
enable once -- Enable breakpoints for one hit
enable tracepoints -- Enable specified tracepoints
hbreak -- Set a hardware assisted  breakpoint
ignore -- Set ignore-count of breakpoint number N to COUNT
rbreak -- Set a breakpoint for all functions matching REGEXP
rwatch -- Set a read watchpoint for an expression
tbreak -- Set a temporary breakpoint
tcatch -- Set temporary catchpoints to catch events
tcatch assert -- Catch failed Ada assertions
tcatch catch -- Catch an exception
tcatch exception -- Catch Ada exceptions
tcatch exec -- Catch calls to exec
tcatch fork -- Catch calls to fork
---Type <return> to continue, or q <return> to quit---
tcatch syscall -- Catch system calls by their names and/or numbers
tcatch throw -- Catch an exception
tcatch vfork -- Catch calls to vfork
thbreak -- Set a temporary hardware assisted breakpoint
trace -- Set a tracepoint at specified line or function
watch -- Set a watchpoint for an expression

Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb)    
``` 


#####Quit

To quit `gdb`, all you have to do is type `quit` or `q` in the prompt. It brings you back to your current working directory.

```
(gdb) quit
```

#####Finding Segfaults

Now download `test3.cpp` from the repository in the `src` folder and compile it. Then run `test3.cpp` through `gdb`.


```
(gdb) run
Starting program: /class/classes/dgoer001/./a.out 
0
1
2
3
4
5
6
7
8
9

Program received signal SIGSEGV, Segmentation fault.
0x0000000700000006 in ?? ()
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64

```
As you can see, `test3.cpp` has a segfault. 

To locate the segfault, you will be using `break`, `next`, and `print` commands.

Before running it with `run` or `r`, create a `break` at line 6, where `main` is located at. Then use `next` or `n` to go through the code. You are not using the `step` command because there are no functions other than `main` in the `test3.cpp`.


```

(gdb) run
Starting program: /class/classes/dgoer001/./a.out 

Breakpoint 1, main () at test.cpp:10
warning: Source file is more recent than executable.
10	        for(int i = 0; i < 10; ++i)
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) n
12	                cout << i << endl;
(gdb) n
0
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
1
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
2
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
3
13	                arr[i] = i;
(gdb) print i
$1 = 3
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
4
13	                arr[i] = i;
(gdb) print i
$2 = 4
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
5
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) print i
$3 = 6
(gdb) n
6
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
7
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) print i
$4 = 7
(gdb) n
12	                cout << i << endl;
(gdb) n
8
13	                arr[i] = i;
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
12	                cout << i << endl;
(gdb) n
9
13	                arr[i] = i;
(gdb) print i
$5 = 9
(gdb) n
10	        for(int i = 0; i < 10; ++i)
(gdb) n
16	        return 0;
(gdb) print i
No symbol "i" in current context.
(gdb) n
17	}
(gdb) n
0x0000000700000006 in ?? ()
(gdb) n
Cannot find bounds of current function
(gdb) n
Cannot find bounds of current function
(gdb) q
A debugging session is active.

	Inferior 1 [process 42294] will be killed.

Quit anyway? (y or n) y

```

The example above shows how `next` was used to go through the for loop and `print` displayed the value of the loop counter. By using the two commands together you can determine that the cause of the segfault was an out of bounds array. The `i` value forced the array out of bounds, that is what caused the segfault.

With these commands, you will be able to debug your future programs more efficiently rather than going through your code, line by line and trying to find bugs. You will save time by using `gdb`.


