# Introduction to the BASH Command Line

Purpose of this lab
------------------------------------
This lab will familiarize CS 100 students with the command line as they transition from using visual displays on Windows and OS X to the Linux BASH shell.

Introduction
------------------------------------
Only 1.41% of all desktop and laptop computers run Linux as the primary operating system. That means you probably don't have too much experience with Linux either. 

Linux programmers primarily use the command line to interact with the computer and this may seem foreign to Windows and Mac users. 

By the end of this lab, you will be able to execute basic commands in the BASH terminal to create, move, and delete files and directories, as well as a few other useful functions.

Let's get started!
-----------------------------------
First of all, you must open the terminal. You can find the terminal by clicking Applications -> System -> Terminal. 

From this point on, you will be using the mouse as little as possible! Programming as efficiently as possible is one of the main virtues of Unix culture. That means limiting your mouse usage in favor of keyboard usage.

**IMPORTANT:** Before you run any commands, type the following into the terminal:
```
$ ssh <your username>@hammer.cs.ucr.edu
```
You may be promted to log in after you ssh into hammer. Hammer is a server provided by UCR specifically for CS100 to break stuff! You will be doing all of your work in hammer so remember to always ssh into hammer when you go to lab!

Once you are in hammer, you must set the settings to CS100, simply type:
```
$ cs100
```
A pretty window will pop up confirming that you have enabled CS100 settings. Don't forget this step! It's crucial and will save you plenty of headache.

Every time you open a new terminal, you must ssh into hammer and enable CS100 settings.
