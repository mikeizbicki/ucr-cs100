#A Quick Tutorial to Write a Simple Shell Script

##What is a shell script?

In one word, a shell script is a file containing a sequence of commands for a UNIX-based operating system.

##How to write a script?

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

* We could find that every shell script include the first line. It is looks like a comment since it start with '#'. However, it is created on purpose since it tell the system which interpreter such as bash, ruby, python, and others should be used to execute the followed script. For this script, it use bash. And '#!' is a special character construct called shebang.

##How to make your script become executable?

The system is very picky about not treating any text files as program. Then each time we creat a shell script we may meet a problem about permission: 

```
$ ./hello.sh
bash: ./hello.sh: Permission denied
```

Here, we want to check the permission of the file, we can use 'ls -l' command:

```
$ ls -l hello.sh
-rw------- 1 user group 35 Dec  4 04:40 hello.sh
```

We can see that we only have 'rw', which means reading and writing permission for user. How we add executing permission for user? Luckly, we have 'chmod' command to change permission of files:

```
$ chmod u+x hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

Now we have 'x', which means executing permission for user. Let us run this shell script again:

```
$ ./hello.sh
Hello world!!!
```

Now it works. 

FYI: Here I want add an alterative way to change permission. If you want to enable all permissions for everyone, just type following command:

```
$chmod 777 hello.sh
$ ls -l hello.sh
-rwxrwxrwx 1 user group 35 Dec  4 04:40 hello.sh
```
Or you can change back all permission only for yourself:

```
$chmod 700 hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

It uses a binary way to represent the the position of permission in '-rwxrwxrwx'. For example, 7 represents 'rwx', 0 represents '---', 1 represents 'r--', and etc.  

##How to move the script to reachable directories?


