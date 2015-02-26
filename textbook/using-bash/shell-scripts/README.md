#Tutorial: Simple Syntaxes For Bash Script

##All begin with a simple example

Let us begin with a "hello world" shell script example to expound how to write a script:

```
#!/bin/bash
#our first script
echo 'Hello world!!!'
```

There are three lines of code in the above script:

* The last line is an echo command to show 'Hello world!!!'. It also works on the command line in the terminal:

```
$ echo 'Hello world!!!'
Hello world!!!
```

* The second line is a comment, because it begins with '#'. Everything after '#' in the current command line will be ignored:

```
$ echo 'Hello world!!!' #Our first script!!!
Hello world!!!
```

* We can see that every shell script includes the first line. It looks like a comment since it starts with '#'. However, it is created on purpose because it tells the system which interpreter (such as bash, ruby, python, and others) should be used to execute the followed script. For this script, it runs in the bash shell. And '#!' is a special character construct called shebang.

A shell script is a file containing a sequence of commands for a UNIX-based operating system. We also can consider each line of code of the script as a line of command in the terminal.

The following tutorial has two parts: 

##Part 1: How to make your script become executable

To successfully run our shell script, we need to make our script become executable. For the above "hello world" example, I save it as 'hello.sh'. For a shell script file, try to use the file extension as '.sh'. So it can be easily identified by us as shell script.

There are two ways to execute a shell script:

```
$ bash hello.sh
$ ./hello.sh
```

Here, I use the second way to run my script. However, the system is very picky about not treating any text files as a program. Then each time we create a shell script we may meet a problem about permission: 

```
$ ./hello.sh
bash: ./hello.sh: Permission denied
```

Here, if we want to check the permission of the file, we can use 'ls -l' command to check the details of the file:

```
$ ls -l hello.sh
-rw------- 1 user group 35 Dec  4 04:40 hello.sh
```

We can see that we only have 'rw', which means a reading and writing permission for the user. How do we add executing permission for the user? Luckily, we have the 'chmod' command to change the permission of the files:

```
$ chmod u+x hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

Now we have 'x' added, which means executing permission has been given to the user. Let us execute this shell script again:

```
$ ./hello.sh
Hello world!!!
```

Tip: there is an alternative way to change permission. If you want to learn more about it, you can go to this link: http://linuxcommand.org/lts0070.php 

##Part 2: More syntax about shell scripts

###Variables

The following line of command shows how to define a variable:

```
x="Hello"
```

Bash does not allow us to leave a space on either side of '=' sign. The following will gives an error message:

```
x = "Hello"
```

And we can access it as follows:

```
$x
```

We can also access our argument variables by using '$0', '$1', '$2',... The following script will show the value for those variables:

```
#!/bin/bash
echo $0
echo $1
echo $2
echo $#
```

we save our script as 'showargv.sh' and change the permission for it, then we run the script:

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

There are also some preset variables in Unix, and you can use those variables in any other programs:

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

Do not use single or double quotes, it only works in the back quote. If you want to perform mathematic operations to assign value to a variable, you can look at the following example:

```
#!/bin/bash
x=0             #assign 0 into x
x=$((x+1))      #add 1 to x
```

###Exit status

After a shell script is executed, it returns two types of exit statuses:

* If the command is successful, it returns value zero(0)

* If the command is not successful, it returns a nonzero value in the range between 1 and 255;

We can examine the exit status of your last command by using parameter '$?':

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

We can see that only the first command is successful and it returns zero(0).

###read

The read statement can get a line from standard input and store it into a variable, the following is an example script:

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

The above line changed the format of the image from '.jpg' to '.png'.

For more details, please check this link: http://linux.die.net/man/1/convert

###test

Before I introduce the 'if' statement, I want to introduce the 'test' statement first, because it is often used with the 'if' statement to perform true/false decisions. The following example tests whether there are arguments provided:

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

For the first 'if', I already introduced that it decides whether there are provided arguments. For the second 'if', the condition is: if the first provided argument is greater than 0, then the command is echo "$1 is positive". Then 'elif' represents 'else if'. Finally, we use 'fi' to end this 'if/else' statement.

For more details, please check this link: http://ss64.com/bash/if.html

###Loops

There are three types of loops: 'while', 'until', and 'for'.

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

At first, I set variable 'X' equal to 0; the condition of the 'while' loop is $X if it is less than or equal to 10. Then 'do' the commands. We use 'done' to finish the loop.

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

I will give an example for converting the format of images in the current directory from '.jpg' to '.png':

```
#!/bin/bash
for i in *.jpg; do
    convert "$i" "${i%.*}.png"
done
```

For more details, please check this link: http://www.cyberciti.biz/faq/bash-for-loop/

##Conclusion
By writing shell scripts and gaining more knowledge about shell scripts, it helps us to have a better understanding about cs100 and the Unix system. If you want to learn more advanced skills and more details about shell script, here is the link: http://linux.die.net/man/1/bash or http://linuxcommand.org/lc3_writing_shell_scripts.php

Thank you for reading and have fun in cs100! :)


