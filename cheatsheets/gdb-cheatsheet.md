GDB Cheatsheet
===

###Starting GDB

After you finish up your sweet program, you should generally compile it with your standard flags, but also with the `-g` flag.
The `-g` flag lets gdb debug our executable and gives us a bunch of helpful feedback.
Without it, gdb will still run your program, but it won't allow you to step through to see if there are any errors, and where they occur. 

```
  $ g++ -g -Werror -Wall -ansi -pedantic moo.cpp
```

After compilation, you want to run it in the following format:

```
  $ gdb a.out <flags>
```

Doing it this way is the quickest way to start debugging.
You can also just run `gdb` and start your program within gdb like so:

```
  $ gdb <flags>
  (gdb) file <executable>
```


`file` is the command that tells gdb that the following argument is the program to be debugged.
If there is already a current executable in gdb, then you can use `file` to a new executable, instead of restarting gdb.
This is useful whenever you have multiple executables that you need to debug.

###GDB Flags

There are many GDB flags, but most of them aren't too useful.
The most useful so far in this class are: <br>

```
  $ gdb --args <program> <arguments>
```

This allows us to pass command line arguments into our program which runs through gdb.
This is like program-caption. 
This argument can only be used once, and anything after the program will be considered an argument, even successive flags.
Anything before it will act normally. 

```
  $ gdb -quiet <program> 
  or 
  $ gdb -q <program>
```

If you don't want your terminal to be flooded with nonsense, then you can use this flag.
It omits the many lines of text explaining legal issues.
This flag can be placed anywhere except after the `--args` flag. 

```
  $ gdb --command=command-file <program>
  or
  $ gdb -x command-file <program>
```

If you already know what commands you want to execute, you can store them in a file and pass it in with the `-x` flag.
The command-file acts like a gdb script.
This will effectively automate the gdb process and can be a useful tool when debugging and can save a lot of time.
For instance, useful case is using this file to setup gdb such as creating breakpoints.

```
  $ gdb <program> -tui
```

`-tui` enables the text user interface, which displays the source code of the program.
It highlights the next line to be executed.
All normal gdb commands are enabled in this mode.
When `-tui` is enabled, stepping through your program will not print out `cout` statements; because of this, it is recommended to only use `-tui` to trace variables in source code alongside `display` and `print`.

You can also chain flags together. 

###Running GDB

All gdb commands can be shortened to the shortest recognizable command (usually a single letter).

```
  (gdb) breakpoint <line number>
  or 
  (gdb) breakpoint <function name>
```

`breakpoint` can be replaced with `b`.
Breakpoints are useful because it allows the user to stop anywhere they want. 
Otherwise, the program would just run.
This lets you step through the program after the break, and shows when and where any errors or outputs occur. 

```
   (gdb) tbreak
```

'tbreak' can be shortened to `tb`.
This commands acts like `breakpoint` and can take the same arguments such as a line number and a function name.
The difference between the two is `tbreak` creates a temporary breakpoint.
The breakpoint will only "break" once and then it is removed. 
This can be useful if you only want to stop once and not every time, for instance when breaking inside of a function.

```
  info breakpoint
```

`info breakpoint` will print out the number of breakpoints, the type, the location, and any conditions associated with the breakpoint.
It will also tell you however many times you've hit the breakpoint.
Additionally, temporary breakpoints will be displayed, as long as the program has not hit them yet and they have not been removed.
It will also print out any watchpoints.

```
  (gdb) clear
```

`clear` will delete all breakpoints set so far.

```
  (gdb) delete <breakpoint> <break numbers>
```

`delete` will delete any specified breakpoints.
If no arguments are specified, it will just delete all breakpoints.

```
  (gdb) disable <break numbers> 
  or 
  (gdb) dis <break numbers>
```

`disable` will disable any specified breakpoints.
If no arguments are specified, it will just disable all breakpoints.
Disabling disabled breakpoints will do nothing.
This is useful if you don't want a breakpoint to stop anymore, but it's there if you feel like you might need it later. 

```
  (gdb) enable <break numbers>
  or 
  (gdb) en <break numbers>
```

`enable` will enable any disabled breakpoints.
If no arguments are specified, it will just enable all breakpoints.
Enabling enabled breakpoints will do nothing. 

```
  (gdb) list
```

OR

```
   (gdb) list <line-number>
```

OR

```
    (gdb) list <function-name>
```

`list` can be shortened to `l`.
The `list` command prints displays the source code which can be useful when looking for breakpoints while running gdb.
By default, the `list` command will display 10 lines of source code that follow the line number of the argument.
However, the user can change the number of lines displayed with `set listsize count` where count is the number of lines displayed.

```
  (gdb) run
  or 
  (gdb) r
```

`run` runs the program until it ends, accepts input, or until it reaches a breakpoint.
Any runs before the program finishes prompts a restart, which keeps all breakpoints or any other commands.
Any runs after the program finishes will still keep its breakpoints or commands as well.

###Using GDB

After using `run` and reaching a line with input or a breakpoint, there are many commands that you can use.

```
  (gdb) watch <variable name>
  or 
  (gdb) wa <variable name>
```

`watch` will cause the program to pause whenever the value of an expression changes.
In most cases, this expression will generally be a single variable.
This is useful when you are sure that a variable shouldn't change, but it does anyways. Watchpoints will not trigger if it is not in the current scope.
That means if you're trying to watch a value in a function, but you never go inside the function in gdb, then the program will not pause.
In order to fix this, you simply need to add a breakpoint in the function.
Deleting or disabling watchpoints is the same as for a breakpoint. 

```
  (gdb) condition <breakpoint number> <condition>
  or 
  (gdb) cond <breakpoint number> <condition>
```

OR

```
  (gdb) breakpoint <line or function name> if <condition>
```

`condition` breakpoints will cause the program to pause when the condition is set.
The condition can be any conditional
in the language you are using.
This is super useful for loops, when you need to check when the condition will be set.
Be careful when setting the breakpoints, as breakpoints in the loop definitions will not work.
It must be inside of the loop.
Any additional conditions will overwrite the previous ones.
In order to set multiple conditions, you must create another breakpoint at the same spot.

```
  (gdb) continue
  or 
  (gdb) cont
```

`continue` continues running the program from wherever it stopped at, such as a breakpoint, a watchpoint, or a conditional breakpoint.
The program will continue running until it stops or another pause point is reached.

```
  (gdb) step
  or 
  (gdb) s
```

`step` steps through your code line by line and also lets you walk through any function calls line by line.
Step has an optional argument, which is just the amount of steps that you want gdb to take.
For example, `(gdb) step 5` will step through 5 lines of code.
However, it's normally recommended to step through it once and check the variables and outputs, to see if anything is off.

```
  (gdb) next
  or 
  (gdb) n
```

`next` steps through your code line by line, but will run function calls automatically.
Similarly to step, next has an optional argument that will go through the code however many lines specified.
For example, `(gdb) next 5` will step through 5 lines of code, however it will still not go into function calls.  

```
  (gdb) until
  or
  (gdb) u
```

`until` takes in the same arguments as breakpoint.
This commands acts very similarly to `tbreak`; the program will run until a specified line number or function name.
The difference is that no breakpoints will be created and the program doesn't "break".

```
  (gdb) finish
```

`finish` is used inside functions.
It will run until the function is complete, doing everything normally, and print out the return value of the function.
Once the function is finished, it pauses, so the user has to continue it or do other things.

```
  (gdb) print <variable name>
  or
  (gdb) p <variable name>
```

`print` is what makes gdb a very powerful tool!
It prints out the value in any variable once.
However, `print` is not constrained to just variables; `print` can also display entire structs and classes.
Here's an example of printing out an entire struct:

```
  1 #include <iostream>
  2 using namespace std; 
  3
  4 struct food {
  5     int taco;
  6     string beef;
  7     string chicken;
  8 };
  9 
 10 int main() {
 11     food yay;
 12     yay.taco = 7;
 13     yay.beef = "ground";
 14     yay.chicken = "shredded";
 15     return 0;
 16 }
```

Running `p yay` after line 14 will produce this result from gdb:

```
(gdb) p yay
$1 = {taco = 7, beef = "ground", chicken = "shredded"}
```

This is extremely useful in tracking your variables.
`print` can also be used to find segfaults in your code.
If gdb tells the user it cannot access the memory of the variable, it is likely due to a segfault.
With gdb you don't have to output your variables in your source code.
Instead, you can just print it here.
Be wary though, for the scope of the variable is very important.
This can only print out variables in the same scope, so if you're in your main function, and you're trying to print out a variable in another function, and you're going to have a bad time.
Print can also change a variable.
For example, `(gdb) print <variable> = 50` will change variable to 50.
You can also call your own functions inside gdb with `print`.
For example, `p foo(7,"ground","shredded")` will call you function.
If you pass a variable into it and the function changes the value, after exiting the value will be the new value.

```
(gdb) backtrace full
```

`backtrace full` is a useful command that will print out all local variables and their values.
Additionally, the command tells the user which function they are currently in.
As with the `print` command, the scope is within the function that the program is currently in.
In small programs, the `print` command may be used, but if there are many variables, `backtrace full` is much more useful.
When `backtrace full` is ran after line 14 in the above program, the output is as follows:

```
#0 main () at main.cpp:14
    yay = {taco = 7, beef = "ground", chcicken = "shredded"}
```

If the user wants to keep track of individual variables, the `display` command can be used instead.

```
  (gdb) display <variable name>
  or 
  (gdb) disp <variable name>
```

`display` prints out `<variable name>` after every `step` or `next` so you can see what value is contained in the variable.
You can use `display` to keep track of multiple variables and only have to declare it once within gdb, unlike `print`.
Similarly to print, you can only display variables in your current scope.
That means, whenever you leave that scope, it will automatically undisplay your variable.
Display is useful for finding scoping errors, so if you display a variable and it disappears, you know you've had a bad time.

```
  (gdb) undisplay <variable name>
```

`undisplay` will undisplay any variable in case you don't need to see it anymore.

```
  (gdb) whatis <variable name>
```

`whatis` will tell you what type the variable is. 

```
   (gdb) where
```

`where` displays the current line number along with the function you are currently in.

```
  (gdb) set var <variable name>=<value>
```

`set var` allows you to change a variable. 

```
  (gdb) set follow-fork-mode child
```

Gdb will follow the child process after the fork occurs.
Additionally, the parent process can be followed instead.

```
  (gdb) record
  or 
  (gdb) rec 
  after 
  (gdb) run
```

`record` will enable the reverse commands so the user can rewind their program. 

*Note: Using `record` will cause your program to run much slower because it requires a lot of memory to keep track of previous actions.

```
  (gdb) reverse-step or (gdb) rs 
  and 
  (gdb) reverse-next or (gdb) rn
```

Sometimes you may go too far in your debugging.
Luckily, these commands allow you to move one line backwards in your code.
These are exactly the same, except they go in reverse order.
It undoes everything the program did, including reverting all variable changes.

```
  (gdb) reverse-continue
  or 
  (gdb) rc
```

`Reverse-continue` rewinds your program until it hits a breakpoint or until it's at the beginning of the program.
It functions exactly the same as normal continue, except it goes backwards!

```
  (gdb) signal
```

With the `signal` command, gdb can send signals such as SIGINT and SIGSTOP to the program.
This can be very useful when testing a signal handler.
This will prove to be useful on homework 3.

```
  (gdb) kill
  or 
  (gdb) k
```

`kill` kills the current program being run through gdb, but does not close gdb itself.
This allows you to restart the debugging process with all breakpoints intact.

```
  (gdb) quit
  or 
  (gdb) q
```

`quit` does what it sounds like; it quits gdb!

###GDB Settings

```
  (gdb) set logging on
  or
  (gdb) set logging off
```

Once logging is turned on, it will record everything from that point to when the user turns it off or exits gdb.
Storing the gdb session can be useful for debugging and saving time.
Gdb will store the current session into `gdb.txt` by default.
The user can change this with `set logging file log-file` where `log-file` is the name of the file to store the session.

```
  (gdb) set print array on
  or 
  (gdb) set print array off
```

Gdb by default displays arrays in a compact form such as

```
(gdb) p arr
$1 = {1, 2, 3}
```

After running `set print array on gdb will now print the array with each index on its own line:

```
(gdb) p arr
$1 = {1,
2, 
3}
```

The advantage to using this is that the contents of the array are easier to read.
The disadvantage comes when the size of your array is large and the output goes off of the screen.

```
  (gdb) set print array-indexes on
  or
  (gdb) set print array-indexes off
```

After running `set print array-indexes on`, gdb will now print the index of the array alongside the contents of each index.
Without being turned on, printing an array will look like:

```
(gdb) p arr
$1 = {1, 2, 3}
```

After turning on print array-indexes, the output will become:

```
(gdb) p arr
$1 = {[0] = 1, [1] = 2, [2] = 3}
```

This allows the user to keep track of an array without having to count out which value corresponding to which index of the array.
This can be extremely useful when the size of the array is above a size of 10 and can speed up debugging time.
