# GDB Video Tutorial

Intereseted in learning to about GDB? 
Well, you might be interested in this tutorial.
GDB is used amongst professionals, hobbyists and beginning level coders across the globe.
Debugging can be quite labor intensive, luckily GDB can make that struggle a whole lot easier.
In this tutorial we'll go over some basic to advanced debugging techniques using GDB.
I hope in the end you'll find that debugging without GDB to be a thing you once did in the past.

What is GDB
====
Well, GDB is just software you can use to debug your code.
You can use GDB on a number of different languages. 
GDB is used to debug efficiently and professionally.
And it is constantly being maintained and updated.
You can find out more at https://www.gnu.org/software/gdb/

Commands used in Tutorial:
===
There are quite a bit of commands supported by GDB;
 however, we'll use only a select few in the tutorial.
These are all the commands we'll look at in the tutorial.
Keep in mind though, there are a lot more. 

| Commands(Alias)| Example | Description |
|:-----------:|:--------------:|:----------------------------:|
| `quit(q)` | `(gdb)` q | used to quit gdb|
| `delete` | `(gdb) d `| used to delete breakpoints|
| `continue(c)`|`(gdb) c`| continue running program|
| `run(r)`  | `(gdb) r`    | runs gdb on the given file |
| `list(l)` | `(gdb) l`    | lists 10 lines by default  |
| `print(p)`| `(gdb) p i ` | print a variable, where i is the variable|
| `list(l)` | `(gdb) l f(x)`| lists lines centered around function f(x)|
| `watch` | `(gdb) watch var` | prompts user when watch var has changed|
| `set var` | `(gdb) set var x = #` | Sets variable x to value right of `=`|
| `backtrace(bt)`| `(gdb) bt` | |outputs summary of calls to current location|
| `list(l)` | `(gdb) l 20` | lists lines centered around #,where # is a line number |
| `record full` | `(gdb) record full` | This command allows us to record gdb and it's execution|
|`set follow-fork-mode`| `(gdb)set follow-fork-mode w`| follow `w` process, `w` is (child/parent)|
| `reverse-step` | `(gdb) rs` | This command allows us to step back within gdb (must have enabled record)|


GDB Intro/Segfaults
----------------
In this introduction video, we'll go over setting up GDB, as well as using some very basic GDB commands.
In Particular, we'll look at how we can go about finding and fixing segfaults.
Finding and fixing segfaults is one of the best features that GDB offers.
You should be able to follow along fairly easily with this tutorial and see just why gdb is so useful.
Remember there are much more commands.
This video just scratches the surface of how vital GDB is. 

<a href="https://www.youtube.com/watch?v=vcVmWbYEIsk" target="_blank"><img src="https://i.ytimg.com/vi/vcVmWbYEIsk/2.jpg?time=1427005811814" 
alt="GDB_Segfault" width="480" height="280" border="10" /></a>


GDB with watch/Record/Reverse
---------------
In this video, we'll go over a few of the commands you likely have seen before.
We'll also introduce commands that may be new to you. 
The `watch` command allows you to see what a variable has changed to.
It's actually not too difficult to implement.
We'll also be looking at the `record full` command, which allows you to record gdb as you go.
Now, if we have `record` set, we can use the command `rs`.
This command allows us to traverse backwards within gdb and change the programs data.

<a href="https://www.youtube.com/watch?v=Yq6XFl-u00o" target="_blank"><img src="https://i.ytimg.com/vi/Yq6XFl-u00o/2.jpg?time=1427006544555" 
alt="GDB_Commands" width="480" height="280" border="10" /></a>

GDB with fork()
---------------
If you're new to system programming and using system calls, GDB has got your back.
In this video, we'll look at a particular function that apparently forgot how many children it had.
We'll use GDB to fix that. 

<a href="https://www.youtube.com/watch?v=FHjK7E0XCUY" target="_blank"><img src="https://i.ytimg.com/vi/FHjK7E0XCUY/2.jpg?time=1427055731015" 
alt="GDB_fork" width="480" height="280" border="10" /></a>


Using GDB
=========
Now that you have some familiarity of GDB, I hope you incorporate using bit of awesomeness in your future projects!
