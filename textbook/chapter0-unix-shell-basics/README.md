#Chapter 0: Unix Shell Basics

This chapter covers the basic concepts and tools you will need in order to understand how to write a simple command line shell.  

##Section 0 : system calls
This section contains files which cover three basic system calls that will be used in the homework assignment, as well as an error-checking function. 
 
* **README.md** - this file covers perror, an error-checking function for your system calls (a requirement throughout the course), as well as an overview of syscalls.

* **exec.md** 
This file covers the following syscalls:

	* fork - creates copies of the parent process, or "child" processes, necessary to execute commands from the command line.

	* wait - allows program to wait for child processes to finish executing before continuing.

	* exec -  executes executables. 

##Section 1 : parsing
This section covers a couple of parsing tools that may be useful for your homework assignment

*  **strtok** - 
this folder covers the C library function ```strtok``` to tokenize, or break apart, a c-string.

*  **Boost Tokenizer** - 
this folder covers this Boost library class that tokenizes strings, examples included.

##Section 2 : Makefile
This section covers how to write Makefiles.

* **Makefile** - 
this file houses an example Makefile.

* **make** - 
this folder contains a tutorial on using ```make``` to compile and install programs easily with Makefiles, as well as numerous examples.

##lab0 - vim

Introduces Vim, the text editor of choice for the class, and how to navigate it. Learn how to configure your .vimrc file to your liking. 

##lab1 - git

Practice with using git for version control, creating and forking repositories to your local machine, updating repositories, and sharing them through github.

##hw0 - rshell

Write your own basic Unix shell to execute simple commands with parameters, and to handle connectors.
