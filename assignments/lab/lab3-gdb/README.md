# Introduction to gdb

The GNU DeBugger (`gdb`) is one of the most powerful tools you have to find and fix bugs in your programs.
This lab contains three exercises to learn about how it works.

Beginners often don't see the benefit of using `gdb`.
They ask: "Why go through all the hassle of `gdb` when I can just add `cerr` statements to my code?"
Both methods work on small projects.
But on large projects `cerr` statements won't work.
And with practice, you'll be much faster at debugging using `gdb` than you would be with `cerr` statements.
At first it will be weird, but stick with it!
I promise it will pay off!
**If you ever catch yourself putting in `cerr` statements, STOP!
Switch to using `gdb`!**

This lab contains three exercises.
The first two exercises were written by Chetas Manjunath (a former cs100 student) to introduce you to the basic `gdb` commands.
The third exercise will challenge you to use those commands in a real-world debugging disaster!

1. (required) [Exercise 1](ex1/): an introduction to the `gdb` commands

3. (optional) [Exercise 2](ex2/): practice on a simplified version of `ls`

2. (required) [Exercise 3](ex3/): debugging the GNU `ls` command, a program with >5000 lines of code

## deliverables

When finished, show the TA the written answers to exercise 1 and the working `ls` program from exercise 3.
Your score on this lab will be 2 points for exercise 1, plus 1 point for each bug you fix in exercise 3.
There are 10 bugs, so it is possible to get a 12/10 on this lab.
