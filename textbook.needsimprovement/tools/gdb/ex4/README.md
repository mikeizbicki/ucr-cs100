#Example 4

Within the `ex4` folder, compile `ex4.cpp` with the `-g` flag by using the following command

```
g++ -g ex4.cpp -o ex4.out
```

After compiling `ex4.cpp` run gdb on the executable file such as

```
gdb ./ex4.out
```
##Using Watch

The `watch`command allows you to keep track of a variable passed into it. 
It will output the previous value and the new value.
Like breakpoints, watchpoints have numbers assigned to them and can be deleted with the `delete` command.
Also like breakpoints, you can use `info` on watchpoints.
In order to use watch, you first set a breakpoint somewhere, such as main, for example

```
(gdb) b main
Breakpoint 1 at 0x4009d8: file ex4.cpp, line 9.
```

Now you run the program using 'r'. 

```
(gdb) r 
Breakpoint 1, main () at ex4.cpp:9
9       int n = 0;
```

Set a watchpoint using `watch` with a variable name, in this case `val`.

```
(gdb) watch val
Hardware watchpoint 2: val
```

Now if you continue using the `continue` command then you can see that the program stops at the watchpoint we had set previously at val.


```
(gdb) c
Continuing.
Enter number to take factorial of: 4
Hardware watchpoint 2: val

Old value = 0
New value = 24
main () at ex4.cpp:13
13      cout << val << endl;
```

As you can see, `watch` gives us the old and new values in val.

`watch` works in a similar way to break; it stops the program, but instead of stopping at a certain line or function, `watch` stops when the variable passed into it changes.

Unlike break, watchpoints set by `watch` are deleted when the variable being watched goes out of scope.

##Using Record and Reverse

The `record` function allows you to record the session of gdb and reverse into it step by step using `reverse`.

In order to use `record`, we again must compile the program with the`-g` flag and then run its executable with gdb.

```
g++ -g ex4.cpp -o ex4.out
gdb ./ex4.out
```
We can then, again, set a `break` at the main function.
```
b main
```
Then, we can use the `record` command

```
(gdb) record full
```
Now, if we use `continue`, it will just continue to the end of the program.

```
(gdb) c
Continuing.
Enter number to take factorial of: 4
24
The next instruction is syscall exit_group.  It will make the program exit.  Do you want to stop the program?([y] or n) y
Process record: inferior program stopped.

[process 24131] #1 stopped.
0x00000033588acd86 in _exit () from /lib64/libc.so.6
```

Now we can use `reverse`, or `rs`, and step backwards through the file, step by step.

```
(gdb) rs
Single stepping until exit from function _exit,
which has no line number information.
0x0000003358835acd in exit () from /lib64/libc.so.6
(gdb) rs
Single stepping until exit from function exit,
which has no line number information.
0x000000335881ed5f in __libc_start_main () from /lib64/libc.so.6
(gdb) rs
Single stepping until exit from function __libc_start_main,
which has no line number information.
main () at ex4.cpp:16
16  }
(gdb) rs
15      return 0;
(gdb) rs
14      cin.get();
(gdb) rs
13      cout << val << endl;
```

As you can see, using `rs`, or `reverse`, we go back through the program.

