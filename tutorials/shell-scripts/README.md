#Tutorial: Some Syntaxs For The Bash Script And How To Write A Simple One.

##What is a shell script?

In one word, a shell script is a file containing a sequence of commands for a UNIX-based operating system.

We also can consider each line of code of the script as a line of command in the terminal.

This tutorial has two parts: 

Part 1: Give a simple example and how to make it works. 

Part 2: Introduce more simple syntaxs about how to write a shell script.

##Part 1: All start with a simple example

To successfully write and run a shell script, you have to do two things:

###1. How to write a script?

Let us begin with a "hello world" shell script example to expound how to write a script:

```
#!/bin/bash
#our first script
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

###2. How to make your script become executable?

There are two ways to run a shell script:

```
$ bash hello.sh
$ ./hello.sh
```

Here, I just use the second way to run my script.

However, the system is very picky about not treating any text files as program. Then each time we creat a shell script we may meet a problem about permission: 

```
$ ./hello.sh
bash: ./hello.sh: Permission denied
```

Here, we want to check the permission of the file, we can use 'ls -l' command to check the details of the file:

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

Tip: there is an alterative way to change permission. If you want to learn more about it, you can go to this link: http://linuxcommand.org/lts0070.php 

##Part 2: More syntaxs about how to write a shell

###Variables

The following shows how to defined a variable:

```
x="Hello"
```

bash do not allow us to leave a space on either side of '=' sign. The following will gives a error message:

```
x = "Hello"
```

And we could access it as follows:

```
$x
```

We also could access our arguments variables by use '$0', '$1', '$2',... The following script will show the value for those variables:

```
#!/bin/bash
echo $0
echo $1
echo $2
echo $#
```

we save our script called 'showargv.sh' and change the permission for it, then we run the script:

```
$ ./showargv.sh first second
./showargv.sh
first
second
3
$ ./showargv.sh a b c d
./showargv
a
b
c
d
5
```

'$#' represents the number of the total arguments. '$0' represents the first argument which is script itself. '$1' represents your first provided argument. Likewise, '$2' represents the second provided argument, '$3' represents the third provided argument, and etc.

There are some preset variables in Unix, and you can use those variables in any other programs:

```
BASH                #shell name
BASH_VERSION        #shell version
HOME                #home directory
PATH                #path settings
SHELL               #shell name
LOGNAME             #our logging name
USERNAME            #our user name
PWD                 #current working directory
PS1                 #prompt settings
OSTYPE              #os type
and more...
```

###Math operation

The following are some examples to perform math operations:

```
$ expr 1 + 1
$ expr 4 - 1
$ expr 3 * 4
$ expr 15 / 3
$ expr 30 % 7
$ echo `expr 30 % 7`
```

Do not use single quote or double quote, it only works in the back quote.

If you want to perform arithmetic operation to assign value into variable, you can see following example:

```
#!/bin/bash
x=0
x=$((x+1))
```

Here we set x equals to 0 first, then we add 1 into x.

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

The read statement can get input from keyboard and store to variable, the following is an example script:

```
#!/bin/bash
echo "please enter your name: "
read myname
echo "Hello $myname"
```

For more details, you can check this link: http://www.lehman.cuny.edu/cgi-bin/man-cgi?read+1

###convert

'convert' between image formats as well as resize an image, blur, crop, despeckle, dither, draw on, flip, join, re-sample, and much more. For example:

```
$ convert image.jpg image.png
```

we just change the format of of image from '.jpg' to '.png'.

For more details, please check this link: http://linux.die.net/man/1/convert

###test

Before starting to introduce 'if' statement, I want to introduce 'test' statement first, because it is often used with the 'if' statement to perform true/false decisions. The following example tests whether there are arguments provided:

```
#!/bin/bash
if test $# -eq 0; then 
echo "$0 : No argument provided"
exit 1
fi
```

or you can just use "[ $# -eq 0 ]" instead of "test $# -eq 0":

```
#!/bin/bash
if [ $# -eq 0 ]; then 
echo "$0 : No argument provided"
exit 1
fi
```

'-eq' is a test operator which means equal to. There is a summary for test operators in the man page, here is the link: http://linux.die.net/man/1/test

###if

Based on the exit status of the commands in the 'if' condition, the system can decide which commands to run. For example:

```
#!/bin/bash
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

For the first 'if', I already introduced that it decides whether there are provided arguments.

For the second 'if', the condition is if the first provided argument is great than 0, then the command is echo "$1 is positive". then 'elif' represents 'else if'. Finally, we use 'fi' to end this 'if/else' statements.

For more details, please check this link: http://ss64.com/bash/if.html

###Loops

Three types of loops: 'while', 'until', and 'for'.

####while

Example:

```
#!/bin/bash
x=0
while [ $x -le 10 ]; do
    echo $x
    x=$((x+1))
done
```

At first, I set variable 'X' equals to 0; then the condition of 'while' loop is $X is less than or equal to 10. Then 'do' the commands. We use 'done' to finish the loop.

For more details, please check this link: http://linux.die.net/man/1/while

####until

In order to do the same work as 'while', the condition of 'until' is the reverse condition of 'while'. For example:

```
#!/bin/bash
x=0
until [ $x -g 10 ]; do
    echo $x
    x=$((x+1))
done
```

For more details, please check this link: http://bash.cyberciti.biz/guide/Until_loop

####for

I will give a example for converting the format of images from '.jpg' to '.png':

```
#!/bin/bash
for i in *.jpg; do
    convert "$i" "${i%.*}.png"
done
```

For more details, please check this link: http://www.cyberciti.biz/faq/bash-for-loop/

##Conclusion
By writing shell scripts and learning more knowledge about shell scripts, It will helps us to have more understand about cs100 and unix system. If you want to learn more advanced skills and more details about shell script, here is the link: http://linux.die.net/man/1/bash or http://linuxcommand.org/lc3_writing_shell_scripts.php

Thank you for reading and have fun in cs100! :)

