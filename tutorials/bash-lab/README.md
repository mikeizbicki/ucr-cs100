# Introduction to the BASH Command Line

Purpose of this lab
------------------------------------
This lab will familiarize CS 100 students with the command line as they transition from using visual displays on Windows and OS X to the Linux BASH shell.

Introduction
------------------------------------
Only 1.41% of all desktop and laptop computers run Linux as the primary operating system. That means you probably don't have too much experience with Linux either. 

Linux programmers primarily use the command line to interact with the computer and this may seem foreign to Windows and Mac users. 

By the end of this lab, you will be able to execute basic commands in the BASH terminal to create, move, and delete files and directories, as well as a few other useful functions.

Terms and Definitions
-----------------------------------
**Shell:** An interface for the terminal that allows for interaction between the computer and the user. In this class, we will be using the BASH Unix shell. 

**Terminal:** For the sake of this lab, the "terminal" is the program that the user will run to type in commands. Used interchangably with "shell" and "command line".

**Command Line:** The command line is a way for the user to interact with the computer through various text commands. Used interchangably with "shell" and "terminal".

**Directory:** A directory is like a folder. It holds files and other directories.



Let's get started!
-----------------------------------
First of all, you must open the terminal. You can find the terminal by clicking Applications -> System -> Terminal. 

From this point on, you will be using the mouse as little as possible! Efficient programming is one of the main virtues of Unix culture. That means limiting your mouse usage in favor of keyboard usage.

**IMPORTANT:** Before you run any commands, type the following into the terminal:
```
$ ssh <your username>@hammer.cs.ucr.edu
```
You may be promted to log in after you ssh into hammer. Hammer is a server provided by UCR specifically for CS100 to break stuff! You will be doing all of your work in hammer so remember to always ssh into hammer when you go to lab!

Once you are in hammer, you must set the settings to CS100, simply type:
```
$ cs100
```
A pretty window will pop up confirming that you have enabled CS100 settings. Don't forget this step! It's crucial and will save you plenty of headache throughout this quarter.

Every time you open a new terminal, you must ssh into hammer and enable CS100 settings.

PWD (Print Working Directory)
------------------------------------
The first command you will learn is `pwd`. PWD stands for "Print Working Directory" and will output the current directory you are in to the screen. Since you just typed in the ssh command, you should be in the HOME directory. Try it out!
```
$ pwd
```
The output should look something like this:
```
home/csmajs/<your username>
```
You may have noticed the `$` that gets outputted after a command is run. This simply means that the terminal is expecting an input from the user.
