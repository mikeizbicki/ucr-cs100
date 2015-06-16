#Video Tutorial on GNU Debugger(GDB)

The GNU Debugger, also known as GDB, is a debugger tool designed to debug programs on Unix-like operation systems. It works on the most popular programming languages such as C, C++, Java, and many more. 

##Use
GDB is primarily used to find runtime errors such as infinite loops or segmentation faults. 
Since code can reach millions of lines, using cerr statements is impractical as it would take a while to set them up and find the errors while GDB would point them out for you.

##Basic Commands 
In this video, we would be teaching you how to use most basic commands for GDB.

Basic Commands video

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Zf4F69-n97k
" target="_blank"><img src="http://img.youtube.com/vi/Zf4F69-n97k/0.jpg" 
alt="Basic Commands Video" width="480" height="360" border="10" /></a>

Commands covered in this video

|Command	|Shortcut| Description of Use						|
|---------------|--------|--------------------------------------------------------------|
|run		|r	 |runs the program						|
|break		|b	 |creates a breakpoint at a line# or function name		|
|print		|p	 |prints variable value						|
|continue	|c	 |continues program until next breakpoint or end of program	|
|next		|n	 |executes next line						|
|step		|s	 |executes next line and will step into a function		|
|info 		|i	 |prints info about its arguments				|
|delete 	|d	 |deletes breakpoints						|

##Advanced Commands
In this video, we would be teaching you how to use advanced commands for GDB

Advanced Commands video

<a href="http://www.youtube.com/watch?feature=player_embedded&v=weGpIsbpjZo
" target="_blank"><img src="http://img.youtube.com/vi/weGpIsbpjZo/0.jpg" 
alt="Advanced Commands Video" width="480" height="360" border="10" /></a>


Commands covered in this video

|Command	| Description of Use						|
|---------------|--------------------------------------------------------------|
|watch		|used to monitor changes in a variable
|set		|set values to variables
|tbreak		|temporary breakpoint
|clear		|the same as delete but can delete all breakpoints in a function
|finish		|executes until function is completed
|info signals	|used to see signal occurences
|backtrace	|tells you where you are such as a function within another function
|up		|moves up the backtrace
|down		|moves down the backtrace
|list		|displays source code
|kill		|stops the execution of the program
|until		|a version of next that does not rerun a loop after one execution
|advance	|basically jump to a line execution
|record		|creates an execution log of gdb session for use in replaying executions
|reverse	|go backwards in an execution

##Demonstration of GDB use
In this video, we will be going blindly into a broken program. 

Demonstration video

<a href="http://www.youtube.com/watch?feature=player_embedded&v=H8jU-snQuCE
" target="_blank"><img src="http://img.youtube.com/vi/H8jU-snQuCE/0.jpg" 
alt="Demonstration Video" width="480" height="360" border="10" /></a>



##More commands
There are many more commands that can be used with GDB. 
These the most commonly used commands can be read in the following link.

[GDB Cheat Sheet](../cheatsheets/gdb-cheatsheet.md)
