#A Quick Tutorial to Write a Simple Shell Script

##What is a shell script?

A shell script is a file containing a sequence of commands for a UNIX-based operating system.

##How to write a script?

Let us begin with a "hello world" shell script example to expound how to write a script:

```
	#!/bin/bash

	#Our first script!!!

	echo 'Hello world!!!'
```

There are three lines of code in the above script:

	1. The last line is an echo command to show 'Hello world!!!'. It also works on the command line in terminal:

```
$ echo 'Hello world!!!'
Hello world!!!
```

	2. The second line is a comment, because it begin with '#'. Everything after '#' in the current command lind will be ignored:

```
$ echo 'Hello world!!!' #Our first script!!!
Hello world!!!
```

	3.We could find that every shell script include the first line. It is looks like a comment since it start with '#'. However, it is created on purpose since it tell the system which interpreter such as bash, ruby, python, and others should be used to execute the followed script. For this script, it use bash. And '#!' is a special character construct called shebang.

##How to make your script become executable?



##How to move the script to the reachable directories?


