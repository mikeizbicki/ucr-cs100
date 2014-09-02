Basic guide for gdb
===================

#####What is gdb?

GDB is a debugger which allows the user to see what is going on in the executed program. If the written program crashes, the user can use GDB to step through the program to see why the program crashed. GDB helps the user to find and locate bugs, segmentation faults, etc. By using GDB, it is more efficient than looking for bugs on your own.

#####Starting gdb

To start `gdb`, we need a program. Using a text editor, such as `vim`, write this simple program and name it `test.cpp`

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
Make sure that `test.cpp` compiles by typing

```
$ g++ -g test.cpp
```
And then press the enter key. The `-g` flag enables debugging and will use the variables and fuctions in `gdb`.

Once `test.cpp` compiles, we will start `gdb` with

```
$ gdb ./a.out
```
By entering in this command, you now are in the `gdb` debugging program. This command does not run the program but it opens the `a.out` file in `gdb`.

The command line in `gdb` will look like

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
The program runs normally just `$ ./a.out`.

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

Another way to run the program though `gdb` is to passing arguments.
```
r arg1 arg2
```

This runs the program with `arg1` and `arg2` already in place

#####Breakpoints

You can create breakpoints in `gdb`. A breakpoint causes a pause (break) in the program when it reaches a certain point.

To use breakpoints, type `break` or `b` in the `gdb` command line followed by the line number that you want to pause (break) at.

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

This is useful for because it suspends other lines of code from executing so that you can inspect the variables and exection of the program.

If you want to continue the program, type in `continue` in the command line

```
(gdb) continue
Continuing.
Enter first number
```

By typing in `continue` in the command line, the program will execute from the breakpoint, which is line 10. The program executes line 11, which is `Enter first number`.

You can make multiple breakpoints in the program through `gdb`. To make another breakpoint in the program, type `break point` followed by the line number. By setting another breakpoint, you are able to pause at another line in the program.

```
(gdb) break 12
Breakpoint 2 at 0x400957: file test.cpp, line 12.
```
Now there are two breakpoints in `test.cpp`. Now run the program from `gdb` by ttyping `run` in the command line

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at test.cpp:10
10      cout << "Enter first number" << endl;
(gdb)
```
The program paused at `Breakpoint 1`, which is the first breakpoint. To continue on to the next breakpoint, type `continue` in the command line. The program will continue until the next breakpoint, which is line 12.

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
If you want to see all the breakpoints that you have made, type `info break` into the command line.

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






You can also set breakpoints on fuctions. To set breakpoints on fuctions, you need to type out the name of the fuction right after the `break`

```
(gdb) break nameofthefuction
```

What this does is that it pauses that this fuction, just like how it paused when we used `break`.

To remove all the breakpoints, type `delete` or `d` into the command line of `gdb`. Then it will ask if you want to delete all the breakpoints. Type `y` for yes or `n` for no.

```
(gdb) delete
Delete all breakpoints? (y or n) y
(gdb) info break
No breakpoints or watchpoints.
(gdb)   
```
By running `info break`, there are no breakpoints showing up because we deleted them all.


#####Stepping Through Code

Stepping lets you go through the code of the program so you will be able to narrow down the bug in your program.

The command `list` or `l` list ten lines of code for the current like that you are on.

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

The `step` or `s` command acts like `next` only if the current line is setting a variable. And if the current line is on a function, the `step` command will only execute the first line of the fuction.

The `finish` or `f` command pauses the executing fuction if you accidently step througha fuction that you did not want to.

#####Backtracing

`backtrace` or `bt` tells you where you are in the execution of the program. It shows where you are in the current program. `backtrace` prints the contents of the stack. The stack lists of function calls.

```
(gdb) backtrace
#0  main () at test.cpp:12
(gdb)   
```
Since `test.cpp` has only one function, `main()`, there is only one on the stack. So `backtrace` prints out `main()`.

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
If you need help on `breakpoints`, type `help breakpoints` into the command line. `gdb` will print out information on `breakpoints`.

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

To quit `gdb`, all you have to do it type `quit` or `q` in the command line. It brings you back to your current working directory.

```
(gdb) quit
```
With these commands, you will be able to debug your future programs more efficiently rather than going through your code, line by line and trying to find bugs. You will save time by using `gdb`.



