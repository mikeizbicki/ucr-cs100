Bash Shell Cheatsheet
=====================

The main topics we’ll go over include an intro to the shell, navigating around the shell, common commands, environment variables, connectors, piping, I/O redirection, permissions, and keyboard shortcuts.
##Introduction to the Shell
The shell is a program, in our case, called "bash" which stands for Bourne Again Shell. 
Other examples of shells include ksh, tcsh, etc. <br>
How the shell works is it takes your commands and gives them to the operating system to perform.
In order to interact with the shell, we use "terminal emulators" such as the gnome-terminal, eterm, nxterm, etc. 
##Navigating Around The Shell
On a Linus system, files are organized in a hierarchical directory structure. 
This means there is a starting directory called the root directory.
This directory contains files and subdirectories that lead into other subdirectories.
###pwd
The `pwd` command, short for print working directory, displays where you are in the directory structure.
Your location is known as the working directory.
For example, if we call `pwd` and the output is:

  ```
    $ pwd
    /home/user
  ```
then our working directory is `/home/user`.
When you first enter the bash shell, your directory location will be your home directory.
###cd
The `cd` command allows you to enter a new directory.

Syntax | Explanation
--- | ---
cd | navigate to home directory
cd .. | navigate backwards to parent directory
cd - | navigate to previous working directory
cd Directory1 | navigate to directory named Directory1
cd Directory1/Directory2 | navigate to directory, Directory2, through path
###mkdir
The `mkdir` command makes a new directory in your current directory. <br>
For example,
  ````
    $ mkdir Hw1
    $ cd Hw1
    $ pwd
    /home/user/Downloads/CS100/Hw1
  ````
##Common Commands
###cat
The `cat` command will read a file passed as a parameter and by default print its contents to standard output. <br>
For example, the following file contains the phrase "Hello World!".
```
  $ cat file1.txt
  Hello World!
```
Using redirection, you can send the output to a file instead. <br>
Passing multiply files as parameters will concatenate the files and then print to standard output.
For example, "file1.txt" contains the phrase "Hello" while file2.txt contains the phrase "World".
```
  $ cat file1.txt file2.txt
  Hello
  World
```
###grep
The `grep` command is used as a search function. <br>
Passing a string and a file will search the file for the given string and print the occurrences to standard output. 
For example,
```
  $ cat users.txt
  user:student password:123
  user:teacher password:321
  $ grep 'student` file1.txt
  user:student password:123
```
You can pass multiple files as parameters.

Common flags | Description 
--- | ---
  `-i` | remove case sensitivity
  `-r` | search recursively through directories
  `-w` | search only whole words
  `-c` | prints number of times found
  `-n` | prints line found on with phrase
  `-v` | prints invert match
###head
The `head` command reads the first 10 lines of any passed in text and prints its contents to standard output.
You can change the default 10 lines to any number by manualing passing in the desired size.
For example, the following will print all 50 lines of the file.
```
  $ head -50 test.txt
```
###tail
The `tail` command reads the last 10 lines of any passed in text and prints its contents to standard output.
You can change the default 10 lines to any number by manually passing in the desired size.
For example, the following will print all 50 lines of the file.
```
  $ tail -50 test.txt
```
###true
The `true` command will always return the exit status zero to indicate sucess.
###false
The `false` command will always return the exit status non-zero to indicate failure.
###history
The `history` command will print out your command line history. <br>
It is command to use the `grep` command with the `history` command in order to search for a particular command.
For example, the following will search your history for all occurrences of the string `g++`.
```
  $ history | grep g++
  155  g++ file1.txt
  159  g++ file2.txt
```
The history command will also print the line the command was found on in your history.
###sed
The `sed` command is a stream editor that will perform text transformations on an input. <br>
Common use of this command is to replace expressions which takes the form `s/regexp/replacement/`
For example, I will replace all occurrences of the phrase "Hello" with "Hi".
```
  $ cat test.txt
  Hello World
  $ sed 's/Hello/Hi/' test.txt
  Hi World
```
[See sed tutorial](textbook/using-bash/sed)
###man
The `man` command directs you to the command manuals. <br>
For example, the following command will give us all the information we need about the command `cat`.
```
  $ man cat
```
###echo
The `echo` command prints its arguments to standard output. <br>
For example,
```
  $ echo Hello World
  Hello World
```
If you call `echo` without any parameters, the command will print a new line.
###export
The `export` command will set an environment variable to be passed to child processes in the environment. <br>
For example, the following will export the variable "name" with the value "student".
```
  $ export name=student
```
###ps
The `ps` command, short for process status, will print out information about the processes running. <br>
For example,
```
  $ ps
  PID TTY          TIME CMD
  35346 pts/2    00:00:00 bash
  46904 pts/2    00:00:00 ps
```
There will be four items displayed: 
  * process identification number (PID)
  * terminal type (TTY), 
  * how long process has been running (TIME)
  * name of command that launched the process (CMD)

###awk
The `awk` command finds and replaces text by searching through files for lines that have a pattern. <br>
The syntax for the command is
```
  awk 'pattern {action}` test.txt
```
###wget
The `wget` command downloads files from the web using protocols like HTTP, HTTPS and FTP and stores in the current working directory. <br>
For example, the following will download one file and store it in Downloads.
```
  $ pwd
  /home/user/Downloads/
  $ wget https://github.com/mikeizbicki/ucr-cs100
```
###nc
The `nc` command, short for netcat, is a utility used to debug and investigate the network. <br>
[See nc tutorial](textbook/using-bash/nc-tutorial)
###ping
The `ping` command tests a network connection. <br>
For example,
```
  $ ping google.com
  PING google.com (74.125.224.34) 56(84) bytes of data.
  64 bytes from lax17s01-in-f2.1e100.net (74.125.224.34): icmp_req=1 ttl=57 time=7.82 ms
  64 bytes from lax17s01-in-f2.1e100.net (74.125.224.34): icmp_req=2 ttl=57 time=8.29 ms
  ^C
  --- google.com ping statistics ---
  2 packets transmitted, 2 received, 0% packet loss, time 16ms
  rtt min/avg/max/mdev = 7.794/8.422/10.792/0.699 ms
```
The statistics at the end show an overview of how many connections went through before we called `^C` and how long it took.
###git
  [See git tutorial](assignments/lab/lab1-git)
##Environment Variables
Environment variables are named variables that contain values used by one or more applications. 
The `PATH` variable contains a list of directories where systems look for executable files. <br>
The `HOME` variable contains the path to the home directory of the current user. <br>
The `PS1` variable is the default prompt to control appearances of the command prompt. <br>
##Connectors
Connectors allow you to run multiple commands at once.

When using the `&&` connector, the first command will always execute and the next command will only execute if the one before it succeeds.
For example, the command `echo` will execute in the first example but not in the second.
```
  $ true && echo Hello
  Hello
  $ false && echo Hello
```
When using the `||` connector, the first command will always execute and the next command will only execute if the one before it fails.
For example, the command `echo` will execute in the second example but not in the first.
```
  $ true || echo Hello
  $ false || echo Hello
  Hello
```
When using the `;` connector, the first command and the following commands will always execute.
For example, every command passed will execute.
```
  $ echo Hello ; ls
  Hello
  test.txt file1.txt file2.txt
```
##Piping
Pipes allow you to connect multiple commands together by sending the standard output of the first command to the standard input of the next command. 
For example, the following will send the `ls` output to `head` so that only the top 10 items get printed.
```
  $ ls -l | head
```
##Input/Output Redirection
I/O redirection allows the user to send the output of a command somewhere other then the screen or even have a command accept input from somewhere other than the keyboard.
###Output Redirection
Standard output redirection uses the symbols `>` and `>>`. <br>
For example, the following will send the output of `ls` into the file instead of printing to the screen.
```
  ls > files.txt
  $ cat files.txt
  file1.cpp sample.txt
```
We can use the command `cat` to output the contents of a file to the display. <br>
The file doesn't need to exist prior to running the command, if the file isnt already in your working directory, the file will be created.
If the file already exists, then the contents of the command will overwrite what is already in the file. <br>
To avoid overwriting a file, the `>>>` command will do the same thing as the `>` command except it will append to the end of the file instead.
###Input Redirection
Standard input redirection uses the symbol `<`. <br>
For example, the following will cause `sort` to access its input from the file instead of the keyboard.
```
  $ cat files.txt
  a
  c
  b
  $ sort < files.txt
  a
  b
  c
```
The `sort` command will print the contents of the file and print to the screen because we haven't redirected its output.
But we can combine I/O redirection into one command line, such as:
```
  $ sort < files.txt > files_sorted.txt
```
The output is now being sent to the files_sorted.txt file.
###Advanced Redirection
Adding a `&` with the `>` symbol will result in redirecting both standard out and standard error.
For example, running the following command on a file named "test.cpp" that prints the string "stdout" with `cout` and the string "stderr" with `cerr` will result in the following output:
```
  $ g++ test.cpp 
  $ ./a.out >& test.txt
  $ cat test.txt
  stdout
  stderr
```
If we run the same command but without the `&` symbol the result will look like:
```
  $ g++ test.cpp 
  $ ./a.out > test.txt
  stdserr
  $ cat test.txt
  stdout
```
The `>` symbol alone only redirects standard output. <br>
If you only want to redirect a specific file descriptor you can attach the file descriptor number to `>`.

Name | File Descriptor | Description
--- | --- | --- 
stdin | 0 | standard input stream
stdout | 1 | standard output stream
stderr | 2 | standard error output stream
For example, if I only wanted to redirect "stderr" to the file "test.txt" from the above example, I would do the following:
```
  $ g++ test.cpp 
  $ ./a.out 2> test.txt
  stdout
  $ cat test.txt
  stderr
```
##Permissions
When you run the command `ls -l` you will notice that a lot of information shows up about each file.
For example,
```
  $ ls -l test.txt
  -rw-rw-r--  1  user  group  1097374 January 26 2:48 test.txt
```
Output from example above | Description/Possible Outputs 
--- | --- 
- | File type: <br> `-`= regular file <br> `d`= directory 
rw- | Permissions for owner of file: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
rw- | Permissions for memebrs of the gorup owning the file: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
r-- | Permissions for all other users: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
user | name of user
group | name of group
###chmod
The `chmod` command changes the permissions of a file. <br>
There is a combination of letters that need to be known in order to change specific users' permission. 
These are:

Letter | User
--- | ---
u | User who owns it
g | Users in the group
a | All users
You call `chmod` by describing which actions you want to perform and to which file.
For example, the following will deny write permission to everyone:
```
  $ chmod a-w test.txt
  $ ls -l test.txt
  -r--r--r--  1  user  group  1097374 January 26 2:48 test.txt
```
The `-` symbol represents taking away permissions while the `+` symbol represents adding permissions.
This next example will make the file readable and writable to the user who owns it and the group.
```
  $ chmod ug+rw test.txt
  $ ls -l test.txt
  -rw-rw----  1  user  group  1097374 January 26 2:48 test.txt
```
Alternatively, we can use `chmod` with hex numbers.
You can think of each permission setting as a bit where it is a `1` if there is permission for the file and `0` otherwise.
```
  rwx = 111 = 7
  rw- = 110 = 6
  r-x = 101 = 5
  r-- = 100 = 4
```
Each set of permissions represents a single digit. 
For example, the following command will have the same outcome as above.
```
  $ chmod 660 test.txt
  $ ls -l test.txt
  -rw-rw---- 1  user  group  1097374 January 26 2:48 test.txt
```
[See permissions tutorial](textbook/using-bash/file-permission)
##Keyboard Shortcuts

Shortcut | Description
--- | ---
CTRL-A | Move cursor to beginning of line
CTRL-E | Move cursor to end of line
CTRL-R | Search bash history
CTRL-W | Cut the last word
CTRL-U | Cut everything before the cursor 
CTRL-K | Cut everything after the cursor
CTRL-Y | Paste the last thing to be cut
CTRL-_ | Undo
