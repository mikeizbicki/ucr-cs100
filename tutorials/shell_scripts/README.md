#A Quick Tutorial to Write a Simple Shell Script and Making It Work

##What is a shell script?

In one word, a shell script is a file containing a sequence of commands for a UNIX-based operating system.

We also can consider each line of code of the script as a line of command in the terminal.

This tutorial has two parts: 

1. The first part give a simple example and how to make it works. 

2. The second part introduce more simple syntaxs about how to write a shell script.

##Part 1: All start with a simple example

To successfully write a shell script, you have to do three things:

1. Write a script.
2. Give the shell permission to execute it
3. Put it somewhere the shell can find it

###How to write a script?

Let us begin with a "hello world" shell script example to expound how to write a script:

```
	#!/bin/bash

	#Our first script!!!

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

It uses a binary way to represent the the position of permission in '-rwxrwxrwx'. For example, 7 represents 'rwx', 0 represents '---', 1 represents '--x', and etc.  

###How to put shell scripts somewhere shell can find it?

If our current directory does not include the shell script, we will get:

```
$ hello.sh
bash: hello.sh: command not found
```

In order to have more convenience to use the our script at any directory, we always move shell script into certain directories. The shell will search automatically those directories for execucable files:

1. Let us 'cd' to your '$HOME', then creat a directory called 'bin': 

```
$ cd $HOME
$ pwd
/home/me
$ mkdir bin
```

This /bin directory is one of the directories that the system will searche automatically.

2. Then use 'mv' command to move your file to this 'bin/' directory.

3. Finally, your can run your script even your current directory does not include script files:

```
$ hello.sh
Hello world!!!
$ cd ..
$ hello.sh
Hello world!!!
```

and your script will run in any directories.

##Part 2: More syntaxs about how to write a shell

###Variables

In Linux (Shell), there are two types of variable:

* System variables: 

Here are some common system variables:

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
```

* User defined variables:

We define a variable as follows:

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

Tip: we also can use braces to protect your variable. If we want to echo X followed by 'world', we can do following:

```
#!/bin/bash
X="Hello"
echo "${X} world"
```

###Exit status

After a shell script is executed, it returns two types of exit status:

* If the command is successful, it returns value zero(0)

* If the command is not successful, it returns a nonzero value;

We can check exit status of your last command by using variable '$?':

```
$ echo hello
hello
$ echo $?
0
$ dasadafada
bash: dasadafada: command not found
$ echo $?
127
$ rm cs100/
rm: cannot remove 'cs100': Is a directory
$ echo $?
1
``` 

We can see that only first command is successful and it returns zero(0).

###The read statement

The read statement can get input from keyboard and store to variable, the following is an example script:

```
	#!/bin/bash
	echo "please enter your name: "
	read myname
	echo "Hello $myname"
```

###Command line arguments

###If condition

###Loop

##Conclusion

By writing shell scripts and learning more knowledge about shell scripts, It will helps us to have more understand about cs100 and unix system. If you want to learn more advanced things about shell script, you can go to http://www.freeos.com/guides/lsst/

Thank you for reading and have fun in cs100!!!

