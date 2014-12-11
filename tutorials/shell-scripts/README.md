#Tutorial How to Write a Basic Shell Script and Some Syntaxs

##What is a shell script?

In one word, a shell script is a file containing a sequence of commands for a UNIX-based operating system.

We also can consider each line of code of the script as a line of command in the terminal.

This tutorial has two parts: 

Part 1: Give a simple example and how to make it works. 

Part 2: Introduce more simple syntaxs about how to write a shell script.

##Part 1: All start with a simple example

To successfully write and run a shell script, you have to do two things:

1. Write a script.
2. Give the shell permission to execute it

###How to write a script?

Let us begin with a "hello world" shell script example to expound how to write a script:

```
#!/bin/bash
#
#our first script!!!
#
echo 'Hello world!!!'
```

There are three lines of code in the above script:

* The last line is an echo command to show 'Hello world!!!'. It also works on the command line in terminal:

```
$ echo 'Hello world!!!'
Hello world!!!
```

* The second line is a comment, because it begin with '#'. Everything after '#' in the current command lind will be ignored:

```
$ echo 'Hello world!!!' #Our first script!!!
Hello world!!!
```

* We could find that every shell script include the first line. It is looks like a comment since it start with '#'. However, it is created on purpose since it tell the system which interpreter such as bash, ruby, python, and others should be used to execute the followed script. For this script, it run in the bash shell. And '#!' is a special character construct called shebang.

Tip: For this file, I save it called 'hello.sh'. For shell script file try to give file extension such as '.sh', which can be easily identified by you as shell script.

###How to make your script become executable?

There are three ways to run a shell script:

```
$ bash hello.sh
$ sh hello.sh
$ ./hello.sh
```

Here, I just use the last way to run my script.

However, the system is very picky about not treating any text files as program. Then each time we creat a shell script we may meet a problem about permission: 

```
$ ./hello.sh
bash: ./hello.sh: Permission denied
```

Here, we want to check the permission of the file, we can use 'ls -l' command:

```
$ ls -l hello.sh
-rw------- 1 user group 35 Dec  4 04:40 hello.sh
```

We can see that we only have 'rw', which means reading and writing permission for user. How we add executing permission for user? Luckily, we have 'chmod' command to change permission of files:

```
$ chmod u+x hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

Now we have 'x', which means executing permission for user. Let us execute this shell script again:

```
$ ./hello.sh
Hello world!!!
```

Now it works. 

Tip: Here I want add an alterative way to change permission. If you want to enable all permissions for everyone:

```
$ chmod 777 hello.sh
$ ls -l hello.sh
-rwxrwxrwx 1 user group 35 Dec  4 04:40 hello.sh
```
Or you can change back all permission only for yourself:

```
$ chmod 700 hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

It uses a binary way to represent the the position of permission in '-rwxrwxrwx'. For example, 0 represents '---', 1 represents '--x', 7 represents 'rwx', and etc.  

##Part 2: More syntaxs about how to write a shell

###Variables

* System variables: 

There are some build-in variables in Unix:

```
BASH				#shell name

BASH_VERSION		#shell version

HOME				#home directory

PATH				#path settings

SHELL				#shell name

LOGNAME				#our logging name

USERNAME			#our user name

PWD					#current working directory

PS1                	#prompt settings

OSTYPE				#os type

and more...
```

* User defined variables:

Syntax:

```
variable name=value
```

For example:

```
X="Hello"
```

Here I want to denote that bash do not allow us to leave a space on either side of '=' sign. The following will gives a error message:

```
X = "Hello"
```

And access it as follows:

```
$X
```

###Exit status

After a shell script is executed, it returns two types of exit status:

* If the command is successful, it returns value zero(0)

* If the command is not successful, it returns a nonzero value in the range between 1 to 255;

We can examine exit status of your last command by using parameter '$?':

```
$ true; echo $?
0
$ false; echo $?
1
$ echo hello; echo $?
hello
0
$ dasadafada; echo $?
bash: dasadafada: command not found
127
$ rm cs100/; echo $?
rm: cannot remove 'cs100': Is a directory
1
``` 

We can see that only first command is successful and it returns zero(0).

###read

Syntax:

```
read variable_1, variable_2,..., variable_n
```

The read statement can get input from keyboard and store to variable, the following is an example script:

```
#!/bin/bash
#	
#Script to say hello
#
echo "please enter your name: "
read myname
echo "Hello $myname"
```

###if

Syntax: 

```
if commands; then 
commands
[elif commands; then
commands]
[else
commands]
fi
```

Based on the exit status of the commands in the condition, the system can decide which commands to run. For example:

```
#!/bin/bash
#
#Script to see determine argument is positive or negative
#
if [ $# -eq 0 ]; then
echo "$0 : No argument provided"
exit 1
fi

if [ $1 -gt 0 ]; then
echo "$1 is positive"
elif [ $1 -eq 0 ]; then
echo "$1 is 0"
else
echo "$1 is negative"
fi
```

Here '$1' represents your first provided argument. Likewise, '$0' represents the script itself, '$2' represents the second provided argument, ... You can also try following commands:

```
$ echo $0; echo $1; echo $2
```

###test

Syntax:

```
test expression 
```

which is often used with the if command to perform true/false decisions. For example:

```
#
#test expression equals  [ expression ] 
#
if test $# -eq 0; then 
echo "$0 : No argument provided"
exit 1
fi
```

Tip: There is a summary for test operators:

```
-n		#operand non zero length

-z		#operand has zero length

-eq		#equal to(for integer)

-neq	#not equal to

=		#equal to(for string)

!=		#not equal to

-lt		#less than

-gt		#great than

-ge		#great than or equal to

-le		#less than ot equal to

-d		#is directory

-f		#is file

-r		#is writable

-w		#is readable

and more...
```

###Loops

There are three types of loops: while, until, and for.

####while

Syntax:

```
while [condition]; do
	commands
done
```

while the condition is true, run the commands within the loop. For example:

```
#!/bin/bash
#
#This script iterate from 0 to 10
#
X=0
while [ $X -le 10 ]; do
	echo $X
	X=$((X+1))
done
```

####until

Syntax:

```
until [condition]; do
	commands
done
```

until the condition is true, run the command within the loop. In order to do the same work as 'while', the condition of until is 'always' the reverse condition of 'while'. For example:

```
#!/bin/bash
#
#
#
X=0
until [ $X -g 10 ]; do
	echo $X
	X=$((X+1))
done
```

####for

Syntax:

```
for { variable } in { list }; do
	commands
done
```

I will give a example for converting the format of images from '.jpg' to '.png':

```
#!/bin/bash
#
#This script converts the format of images from .jpg to .png in the current directory 
# 
for i in *.jpg; do
	convert "$i" "${i%.*}.png"
done
```

##Conclusion

By writing shell scripts and learning more knowledge about shell scripts, It will helps us to have more understand about cs100 and unix system. If you want to learn more advanced things about shell script, your can go to: http://www.freeos.com/guides/lsst/ or http://linuxcommand.org/lc3_writing_shell_scripts.php

Thank you for reading and have fun in cs100! :)

