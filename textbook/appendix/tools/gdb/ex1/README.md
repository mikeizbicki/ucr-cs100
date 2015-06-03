






###Example 1

From the `ex1` folder, compile `ex1.cpp` with the `-g` flag by using following command

```
$ g++ -g ex1.cpp
```
The `-g` flag enables the program to be run with `gdb`. The `-g` allow the usage of `gdb` for debugging and can track the uses variables and fuctions in `gdb`.

Once `ex1.cpp` compiles, we will start `gdb` with

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

#####Quit

To quit `gdb`, all you have to do is type `quit` or `q` in the prompt. It brings you back to your current working directory.

```
(gdb) quit
```
You can exit `gdb` any time in the `gdb` command prompt.

```
(gdb) run
Starting program: /class/classes/dgoer001/hw4/ex1 
Enter first number
3
Enter second nunber
4
3 times 4 equals 12
[Inferior 1 (process 35915) exited normally]
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.
el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
(gdb) quit
dgoer001@cs100 $
```

#####Breakpoints

You can create breakpoints in `gdb`. A breakpoint causes a pause (break) in the program when it reaches a certain point.

Breakpoints stop the program before executing the line number.

To use breakpoints, type `break` or `b` in the `gdb` prompt followed by the line number that you want to pause (break) at.

In addition, breakpoints can be set at a specific line by entering a fuction instead of a line number. When a function is passed in GDB, it will put a breakpoint where the function is found in the code.

```
(gdb) break 10
Breakpoint 1 at 0x40092d: file ex1.cpp, line 10.
```
As you can see, it creates a breakpoint on line 10.

When you `run` the program, it will output

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at ex1.cpp:10
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
Breakpoint 2 at 0x400957: file ex1.cpp, line 12.
```
Now there are two breakpoints in `ex1.cpp` through GDB. Now run the program from `gdb` by typing `run` in the prompt. This will run the program until breakpoint 2 is reached.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at ex1.cpp:10
10      cout << "Enter first number" << endl;
(gdb)
```
The program paused at `Breakpoint 1`, which is the first breakpoint. To continue on to the next breakpoint, type `continue` in the prompt. The program will continue until the next breakpoint, which is line 12.

```
(gdb) run
Starting program: /home/csmajs/kle016/Desktop/gdb/a.out
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x2aaaaaaab000

Breakpoint 1, main () at ex1.cpp:10
10      cout << "Enter first number" << endl;
(gdb) continue
Continuing.
Enter first number
6

Breakpoint 2, main () at ex1.cpp:12
12      cout << "Enter second nunber" << endl;
(gdb)       
```
If you want to see all the breakpoints that you have made, type `info break` into the prompt.

```
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040092d in main() at ex1.cpp:10
        breakpoint already hit 1 time
2       breakpoint     keep y   0x0000000000400957 in main() at ex1.cpp:12
        breakpoint already hit 1 time
(gdb)      
```


To delete a breakpoint, type `delete N`, where `N` is the breakpoint number.

```
(gdb) delete 2
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040092d in main() at ex1.cpp:10
        breakpoint already hit 1 time
(gdb)    
```
As you can see, we deleted 2, which was breakpoint 2. Then we used `info break` to confirm that it has been deleted.



You can also set breakpoints on fuctions. To set breakpoints on fuctions, you need to type out the name of the fuction or right after the `break`

```
(gdb) break nameofthefuction
```

Using `break` with the name of a function, will set a breakpoint to wherever the name of the function appears in the code.

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

For additional options on how to use `help`,  it can be found at the bottom of the text after you run the `help` command.

For example, if you need help on `breakpoints`, type `help breakpoints` into the prompt. `gdb` will print out information on `breakpoints`.


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
