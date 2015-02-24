Bash Shell Cheatsheet
=====================

This cheatsheet will go over commands within the bash shell to perform various tasks.
The main topics we'll go over include an intro to the shell, navigating around the shell, input/output redirection, and permissions.

##Introduction to the Shell
The shell is a program, in our case, called "bash" which stands for Bourne Again Shell. 
Other examples of shells include ksh, tcsh, etc.

How the shell works is it takes your commands and gives them to the operating system to perform.
In order to interact with the shell, we use "terminal emulators" such as the gnome-terminal, eterm, nxterm, etc. 

##Navigating Around The Shell
A very important command that allows you to move around from directories is `cd`. 
A helpful command that accompanies the `cd` command is `pwd` which displays your working directory.

On a Linus system, files are organized in a hierarchical directory structure. 
This means there is a starting directory called the root directory.
This directory contains files and subdirectories that lead into other subdirectories.

###Print working Directory
The `pwd` command displays where you are in the directory structure. 
Your location is known as the working directory.
For example, if we call `pwd` and the output is:

  ```
    $ pwd
    /home/user
  ```
then our working directory is "/home/user".
When you first enter the bash shell, your directory location will be your home directory.

###Change Directory
In order to enter a new directory you will use the `cd` command.
Calling `cd` followed by a directory name will send you into that directory.
For example,
  ````
    $ pwd
    /home/user
    $ cd Downloads
    $ pwd
    /home/user/Downloads
  ````
We are now in the "Downloads" directory verse being in the home directory like before.
You can also pass a path into cd instead of a single directory such as:
  ````
    $ pwd
    /home/user
    $ cd Downloads/CS100/Homework
    $ pwd
    /home/user/Downloads/CS100/Homework
  ````
To navigate backwards, you can use paths like above or take the lazy route and pass ".." instead.
The ".." symbol will send you to your working directory's parent directory.
For example,
  ````
    $ pwd
    /home/user/Downloads/CS100/Homework
    $ cd ..
    $ pwd
    /home/user/Downloads/CS100
  ````
To go back to your home directory, call `cd` followed by nothing. For example,
  ````
    $ pwd
    /home/user/Downloads/CS100
    $ cd
    $ pwd
    /home/user
  ````
If you would like to create a directory from your working directory you would call `mkdir` followed by the name of the directory you are creating. For example,
  ````
    $ pwd
    /home/user/Downloads/CS100
    $ mkdir Hw1
    $ cd Hw1
    $ pwd
    /home/user/Downloads/CS100/Hw1
  ````

##Input/Output Redirection
I/O redirection is a handy tool that allows the user to send the output of a command somewhere other then the screen or even have a command accept input from somewhere other than the keyboard.

###Standard Output
Standard output redirection uses the symbols `>` and `>>`.

Most commands such as `ls` send their results to standard output, which prints to the screen.
Instead of printing to the screen we can redirect the standard output to print into a file.
The command goes before the symbol and the file goes after the symbol, as follows:
```
  ls > files.txt
```
If we ran `ls` on its own we may get a results such as:
```
  $ ls
  file1.cpp sample.txt
```
But if we run the above command with output redirection, there will be no output to the display, the output will be in a file, such as:
```
  $ ls > files.txt
  $ cat files.txt
  file1.cpp sample.txt
```
We can use the command `cat` to output the contents of a file to the display.

The file doesn't need to exist prior to running the command, if the file isnt already in your working directory, the file will be created.
If the file already exists, then the contents of the command will overwrite what is already in the file.

To avoid overwriting a file, the `>>>` command will do the same thing as the `>` command except it will append to the end of the file instead.

###Standard Input
Standard input redirection uses the symbol `<`.

Just like standard output redirection, the command goes before the symbol and the file that the command will be getting its input from goes after the symbol.
Running the command `sort` with `<` will cause sort to access the imput necessary to execute from the input file instead of standrd input, such as:
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
Notice that nothing got printed to the screen. 
That is because the output was now sent to the files_sorted.txt file.

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
The `>` symbol alone only redirects standard output.

If you only want to redirect a specific file descriptor you can attach the file descriptor number to `>`.

Name | File Descriptor | Description
--- | --- | --- 
stdin | 0 | standard input stream
stdout | 1 | standrad output stream
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
Interpreting this information could be tricky at first if you dont understand wha each section means.

Running the command `ls -l` on a file will result in an output such as:
```
  $ ls -l test.txt
  -rw-rw-r--  1  user  group  1097374 January 26 2:48 test.txt
```
But what does all this mean?

Output from example above | Description/Possible Outputs 
--- | --- 
- | File type: <br> `-`= regular file <br> `d`= directory 
rw- | Permissions for owner of file: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
rw- | Permissions for memebrs of the gorup owning the file: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
r-- | Permissions for all other users: <br> `r`= has read permission <br> `w`= has write permission <br> `x`= has executable permission <br> `-`= has no permission for either read/write/execute
user | name of user
group | name of group

###Change Mode
To change the permissions of a file, you use the command `chmod`.
There is a combination of letters that need to be known in order to chang specific users' permission. 
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
  -rw-rw-rw-  1  user  group  1097374 January 26 2:48 test.txt
```

