Advantages
===========
One great advantage of cppcheck is its easy to use interface. Just like vim, 
you will can  customize it when you first start it up. For example, you'll
need to specify the third-party libraries, and integrate Cppcheck with your 
developement environment. After your analysis, it gives you diagnostic messages. 
They have different categories of error messages. They are grouped in the following
messages: Warnings, errors, style warnings, portability warnings, performance warnings,
and information Messages. You can customize which warnings show up in its analysis.

Some issues that Cppcheck can analyze are resource leaks, memory leaks, 
checks if the array goes out of bound, if any variables are uninitialized,
checking input/output operations, and checking if you dereferenced a null
pointer. In a regular compiler, the compiler would not be able to find most
if any of these errors without running the program. Cppcheck saves you an imense amount 
of time while coding. Since you guys have so many assignments,learning how to usecppcheck 
is crucial to your classes. Another great advantage of cppcheck isthe extremely low 
possibility of false positives. This will also help with saving timebecause it will only 
show warnings or errors if it is one hundred percent certain that it's an error. 
Cppcheck not only checks one file, it can check entire directories! Imagine that you 
were working on a big project with multiple files and your job was to debug all the files.
Seems like a tough job right? Everyone hates debugging code. This can all be easily done
with cppcheck. Just run it on an entire directory instead of one by one. Wait a few minutes,
and poof, you get your diagnostic messages. 

Another great advantage of cppcheck is its price. It's a free program that rival 
programs that cost an arm and a leg. In this class, open sourced programs are your friend.
To emphasize my point of great open source projects, You're most likely reading this on a 
computer that's running linux (which is also open sourced). How did I know? because Mike 
makes everyone install Linux on their computers! :).

Disadvantages
===========
However, only using cppcheck to debug your code for bugs is not a good idea. Cppcheck
is a static debugging tool. This means that the debugging routine is used after the program
that is being debugged has run and has stopped. Using cppcheck in conjunction with other 
types of debuggers maximizes cppcheck's potential. Because cppcheck is a static debugger,
you should also use dynamic debuggers to help check your code while it's running. Dynamic debuggers
such as Valgrind and GDB. You'll learn how to use GDB in class so this will help you immensely
with your code in CS100 and future computer science classes. Dynamic debuggers help debug your 
code by having the user control the execution of his or her code. One can set breakpoints, do
step by step execution and look into what the stack and variables are initialized to. Using 
a static debugger with a dynamic debugger is cover most of your code.
	    
With cppcheck having little to no false positives, it can be a blessing or a curse. There will
be times where one will want to know every possible error in their program in order to perfect their code. 
Cppcheck is not the static debugger if you want to know every single possible bug. Programs such 
as Eclipse and VisualStudios are the programs you may want to use to know the full extent of your 
program's bugs.One minor problem with cppcheck is the that the complexity of the analysis grows 
with the amount of lines it checks.

Another drawback of cppcheck is the vague diagnostic messages. Some diagnostic messages are clear and
concise. The other times, the messages are unclear and hard to read. You'll have to try your best to 
to decode these hit or miss obscure messages.

Overall feelings
=================
In the end, the static analysis field is giant and one static debugger cannot cover it. Use other static
and dynamic debuggers to help find bugs where cppcheck does not. And with each update cppcheck has, it 
has the potential of being even better. For instance, with the latest update, the update notes state that it can now 
find unused return values.
