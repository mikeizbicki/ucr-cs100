Bash Shell Cheatsheet
=====================
The main topics of this cheatsheet include an intro to the shell, navigating around the shell, common commands, environment variables, connectors, piping, I/O redirection, permissions, and keyboard shortcuts.

##Table of Contents
* [Introduction to the Shell](#introduction-to-the-shell)
* [Navigating Around The Shell](#navigating-around-the-shell)
* [Common Commands](#common-commands)
  - [Using Input](#using-input)
  - [Processes](#processes)
  - [Files](#files)
  - [Getting Information](#getting-information)
  - [Network](#network)
  - [Miscellaneous](#miscellaneous)
* [Environment Variables](#environment-variables)
* [Connectors](#connectors)
* [Piping](#piping)
* [Input and Output Redirection](#input-and-output-redirection)
  - [Output Redirection](#output-redirection)
  - [Input Redirection](#input-redirection)
  - [Advanced Redirection](#advanced-redirection)
* [Permissions](#permissions)
* [Keyboard Shortcuts](#keyboard-shortcuts)

##Introduction to the Shell
The shell is a program, in our case, called "bash" which stands for Bourne Again Shell. 
How the shell works is it takes your commands and gives them to the operating system to perform.
In order to interact with the shell, we use "terminal emulators" such as the [gnome-terminal](https://help.gnome.org/users/gnome-terminal/stable/), [eterm](http://www.eterm.org/), nxterm, etc. 
##Navigating Around The Shell
On a Linux system, files are organized in a hierarchical directory structure. 
This means there is a starting directory called the root directory.
This directory contains files and subdirectories that lead into other subdirectories.
###pwd
The `pwd` command, short for print working directory, displays your current location in the directory structure.
###cd
The `cd` command allows you to enter a new directory.

Syntax | Explanation
--- | ---
cd | navigate to home directory
cd ~ | navigate to home directory
cd .. | navigate backwards to parent directory
cd - | navigate to previous working directory
cd Directory1 | navigate to directory named Directory1
cd Directory1/Directory2 | navigate to directory, Directory2, through path
###mkdir
The `mkdir` command makes a new directory in your current directory. 
##Common Commands
####man
The `man` command directs you to the command manuals. 
For example, the following command gives us all the information we need about the command `cat`. 
```
  $ man cat
```
###Using Input
####grep
The `grep` command is a search function. 
Passing a string and a file searches the file for the given string and prints the occurrences to standard output. 
```
  $ cat users.txt
  user:student password:123
  user:teacher password:321
  $ grep 'student' file1.txt
  user:student password:123
```
`grep` can take multiple files as parameters and regular expressions to specify a pattern in text.

Common flags | Description 
--- | ---
  `-i` | remove case sensitivity
  `-r` | search recursively through directories
  `-w` | search only whole words
  `-c` | prints number of times found
  `-n` | prints line found on with phrase
  `-v` | prints invert match
[See regex tutorial](../../textbook/using-bash/regex)
####sed
The `sed` command is a stream editor that performs text transformations on an input. 
Common use of this command is to replace expressions which takes the form `s/regexp/replacement/g`
For example, the following replaces all occurrences of the phrase "Hello" with "Hi".
```
  $ cat test.txt
  Hello World
  $ sed 's/Hello/Hi/g' test.txt
  Hi World
```
[See sed tutorial](../../textbook/using-bash/sed)
####sort
Outputs given input in sorted order.
Takes in a file, reads it, and outputs each line.
If no files are specified, it takes in stdin.
```
sort [flags] file1 file2 file2...
```
`-n` sorts numerically, `-r` is for reverse order
####tee
Used for redirecting output to multiple files,
this command copies standard input into standard output as well as any files given as arguments. 
```
tee [flags] File1
```
Used a lot with [pipes](#piping).
The below example has `tee` taking the given input and puting it into outputFile,
and also sending the input to stdout.
```
 $ cat inputFile | tee outputFile | grep word
 This line has word in it.
```
The `-a` flag is used to append the standard input to the end of the files, rather than overwriting them.
###Processes

####ps
The `ps` command, short for process status, prints out information about the processes running. 
```
  $ ps
  PID TTY          TIME CMD
  35346 pts/2    00:00:00 bash
```
There are four items displayed: 
  * process identification number (PID)
  * terminal type (TTY), 
  * how long process has been running (TIME)
  * name of command that launched the process (CMD)

####kill
Sends a signal to processes, usually used to terminate them.
```
kill [-s sigspec] [-n signum] [-sigspec] pid
kill -l [exit_status]
kill -l [sigspec]
```
`pid` is the the process id of the process you want to send the signal to.
`sigspec` is the signal name.
`kill -l [sigspec]` will list the `signum`, the number, for each `sigspec`.
To get a full list of the signals, use `kill -l` with nothing else. 
This command is usually used to kill processes, using the `ps` command to get a processes’ pid.
For example, to send SIGKILL, the kill signal, to a currently running process, a.out, with pid 23456
```
 $ kill -9 23456
 [1]+  Killed                  ./a.out
```
####jobs
The `jobs` command lists the processes running in the background.
```
jobs [flags] [jobspec]
```
The jobspec is a % followed by a number (starting from 1) given to each job.
The `-l` flag lists pids along with the normal info.
If `jobs` is run on its own, all processes running in the background are listed.
####fg
Used to bring a command in the background to the foreground.
```
fg [jobspec]
```
If no jobspec is given, it will bring the recent background job to the foreground, making it the current process. 
The jobspecs are listed using the `jobs` command, with % followed by the number.
For example,
```
 $ jobs
 [1]+  Stopped                 ./a.out
 $ fg %1
 ./a.out
```
###Files
####awk
The `awk` command finds and replaces text by searching through files for lines that have a pattern. 
Syntax: `awk 'pattern {action}' test.txt`
####cat
The `cat` command reads a file passed as a parameter and by default print its contents to standard output. 
Passing multiply files as parameters concatenates the files and then prints to standard output.
####cp 
Copies files and directories.
```
cp [flags] FileToCopy DestinationPath
```
You can copy many files at a time into a directory, or just copy one file.
```
cp [flags] FileToCopy1 FileToCopy2 FileToCopy3 DestinationPath
```
To copy a directory, you need to use the `-r` or `-R` flags to recursively copy everything in.
Files will keep their name unless you don’t enter a path or directory that is the current directory, and instead enter a new name for the copy file.
```
cp [flags] file1 file1WithNewName
cp -r testfile1 newfile
```
Another flag is the `-v` flag which outputs the files as they are copied, which is useful for recursive copies.
```
$cp -r -v test1 test2
test1 -> test2
test1/b -> test2/b
test1/c -> test2/c
```
####head
The `head` command reads the first 10 lines of any passed in text and prints its contents to standard output.
You can change the default 10 lines to any number by manually passing in the desired size.
For example, the following prints all 50 lines of the file. 
```
$ head -50 test.txt
```
####tail
The `tail` command reads the last 10 lines of any passed in text and prints its contents to standard output.
You can change the default 10 lines to any number by manually passing in the desired size.
For example, the following prints all 50 lines of the file. 
```
  $ tail -50 test.txt
```
####mv
Used for moving or renaming files. 
If the last parameter is a directory, the file is moved into the directory.
You can move many files at a time into a directory, or just one file.
```
mv [flags] FileToMove DestinationPath
mv [flags] FileToMove1 FileToMove2 FileToMove3 DestinationPath
```
If the last parameter is a file name, the first file is renamed to the second.
```
mv [flags] FileToRename NewNameForFile
```
The `-b` flag makes a backup of every file that would otherwise be overwritten or removed.
####rm
Used to remove files, and you can remove multiple files at once. 
```
rm [flags] FileToRemove1 FileToRemove2
```
The `-r` and `-R` flags remove directories and their content recursively.
Without one of these flags, directories require the `rmdir` command to remove them instead.
####rmdir
The `rmdir` command is for removing empty directories. 
```
rmdir [flags] DirectoryToRemove1 DirectoryToRemove2
```
####stat
Reports the status of the files passed in.
```
stat [flags] File1 File2
```
An example of stat used on file index.htm,
```
 $ stat index.htm
   File: 'index.htm'
   Size: 17137 Blocks: 40 IO Block: 8192 regular file
 Device: 8h/8d Inode: 23161443 Links: 1
 Access: (0644/-rw-r--r--) 
 Uid: (17433/comphope) Gid: ( 32/ www)
 Access: 2007-04-03 09:20:18.000000000 -0600
 Modify: 2007-04-01 23:13:05.000000000 -0600
 Change: 2007-04-02 16:36:21.000000000 -0600
```
The first `Access:` shows the [permissions](#permissions) of the file.
The bottom three things are listing the dates the file was last accessed, modified, and its status changed. 
The `-f` flag is used to get the status of a file system instead of a file.
```
 $ stat -f testfile.md
   File: "testfile.md"
     ID: 0        Namelen: 255     Type: nfs
 Block size: 32768      Fundamental block size: 32768
 Blocks: Total: 22319030   Free: 760709     Available: 760709
 Inodes: Total: 24798928   Free: 8265892
```
####touch
The `touch` command is used to update file timestamps, or create empty files. 
```
touch [flags] File1ToUpdate File2ToUpdate
```
If the filename you use isn’t an existing file it creates that file.
If it does, the timestamps are updated to the current time.
The flag `-c` will prevent a file that doesn’t exist from being created.
The flag `-a` will updates only the access timestamp, while `-m` updates only the modification timestamp.
####wc
The `wc` command, short for word count, counts and then prints the number of newlines, whitespace-separated words, and bytes/characters (in that order)
given by the file passed in, or standard input if no files are given. 
```
wc [flags] File1 File2
wc [flags]
```
For multiple files, each file’s info is given individually, then a running total at the bottom.
```
 $ wc testfile.md
   341  2011 12397 testfile.md
   230  1341  7639 anotherFile.md
   571  3352 20036 total
```
The `-l` flag prints only the newline count, `-w` only the word count, and `-c` only the byte count.
###Getting Information
####date
The `date` command outputs the date.
```
date [flags] [+format]
```
`date` by itself prints the current date. 
The flag `date==string` displays the time described by `string`, with '1 day ago', 'yesterday', '3 months', and such, as valid strings.
The flag `-u` gives the current Coordinated Universal Time.
The format controls the output, with `+D` printing date in mm/dd/yy format.
See [the man page](http://ss64.com/bash/date.html) for a full list of formats.
####groups
Prints the group names a user is in.
```
groups [username]
```
Multiple usernames can be passed in.
####history
The `history` command prints out an incremented command line history. 
It is common to use the `grep` command with the `history` command in order to search for a particular command.
For example, the following searches your history for all occurrences of the string `g++`.
```
  $ history | grep g++
  155  g++ file1.txt
  159  g++ file2.txt
```
####hostname
This command is used to print or set the system name.
```
hostname [NewName]
```
If NewName is not given, the name of the current host system is printed.
If you have the appropriate privileges, the host name will be set to NewName.
####id
The `id` command prints the user id (uid), group id (gid), and identity info about the given user.
```
id [flags] [username]
```
If no options or username is given, it prints the real user id,
real group id, effective user id if different from the real user id,
effective group id if different from the real group id, and supplemental group ids.
The flag `-g` prints only the group id, `-G` only the supplementary groups, `-u` only the user id.
####uname
The `uname` command is used to print system info.
```
uname [flags]
```
No flags given prints the kernal name.
The `-m` flag prints the machine (hardware) type,
the `-p` the machine's processor type,
the `-o` flag prints the operating system,
and the `-a` flag is prints all the flag's info.
####whoami
Prints current user name.
```
 $ whoami
 tgilli1969
```
###Network
####nc
The `nc` command, short for netcat, is a utility used to debug and investigate the network. 
[See nc tutorial](../../textbook/using-bash/nc-tutorial)
####ping
The `ping` command tests a network connection. 
```
  $ ping google.com
  PING google.com (74.125.224.34) 56(84) bytes of data.
  64 bytes from lax17s01-in-f2.1e100.net (74.125.224.34): icmp_req=1 ttl=57 time=7.82 ms
  --- google.com ping statistics ---
  1 packets transmitted, 1 received, 0% packet loss, time 8ms
  rtt min/avg/max/mdev = 7.794/8.422/10.792/0.699 ms
```
The statistics at the end show an overview of how many connections went through before we called `^C` and how long it took.
####wget
The `wget` command downloads files from the web and stores it in the current working directory. 
```
  $ wget https://github.com/mikeizbicki/ucr-cs100
```
###Miscellaneous
####echo
The `echo` command prints its arguments to standard output. 
```
  $ echo Hello World
  Hello World
```
If you call `echo` without any parameters, the command prints a new line.
####false
The `false` command always returns the exit status non-zero to indicate failure.
####true
The `true` command always returns the exit status zero to indicate success.
###git
`Git` is a version control system that is commonly used in the industry and in open source projects. 
[See git tutorial](../../assignments/lab/lab1-git)
####sleep
The `sleep` command is used to have bash wait or delay for a specific amount of time.
```
sleep number[suffix]
```
If no suffix is given, bash will wait in seconds.
The other suffixes are 'm' for minutes, 'h' for hours, and 'd' for days.
So to have bash wait for 3 days,
```
 $ sleep 3d
```
##Environment Variables
Environment variables are named variables that contain values used by one or more applications. 
The `PATH` variable contains a list of directories where systems look for executable files. 
The `HOME` variable contains the path to the home directory of the current user. 
The `PS1` variable is the default prompt to control appearances of the command prompt. 
###env
The `env` command is used to display, set or, remove environment variables.
```
env [flags] [VariableName=value] [command [arguments]]
```
Having nothing after `env` just prints all the environment variables.
Use `VariableName=value` to set the VariableName to the value.
The flag `-u VariableName` removes the variable VariableName from the environment.
###export
The `export` command sets an environment variable to be passed to child processes in the environment. 
For example, the following exports the variable "name" with the value "student". 
```
  $ export name=student
```
####printenv
The `printenv` command prints environment variables. 
```
printenv [variables]
```
Using variables prints the values of each.
```
 $printenv PWD HOSTNAME SHELL
 /home/csmajs
 hammer.cs.ucr.edu
 /bin/bash
```
If no variables are given, all environment variables are printed instead.
##Connectors
Connectors allow you to run multiple commands at once.

Connector | Description
--- | --- | ---
`&&` | first command always executes and the next command will only execute if the one before it succeeds
`||` | first command always executes and the next command will only execute if the one before it fails
`;` | first command and the following commands always execute
```
  $ true && echo Hello
  Hello
  $ false || echo Hello
  Hello
  $ echo Hello ; ls
  Hello
  test.txt file1.txt file2.txt
```
##Piping
Pipes connect multiple commands together by sending the stdout of the first command to the stdin of the next command. 
For example, the following sends the `ls` output to `head` so that only the top 10 items get printed. 
```
  $ ls -l | head
```
##Input and Output Redirection
###Output Redirection
Standard output redirection uses the symbols `>` and `>>`. 
For example, the following sends the output of `ls` into the file instead of printing to the screen.
```
  ls > files.txt
  $ cat files.txt
  file1.cpp sample.txt
```
If the file isn't already in your working directory, the file gets created.
If the file already exists, then the contents of the command overwrites what is already in the file. 
To avoid overwriting a file, the `>>` command appends to the end of the file instead.
###Input Redirection
Standard input redirection uses the symbol `<`. 
For example, the following causes `sort` to access its input from the file instead of the keyboard.
```
  $ cat files.txt
  c
  b
  $ sort < files.txt
  b
  c
```
The `sort` command prints the contents of the file and prints to the screen because we haven't redirected its output.
But we can combine I/O redirection into one command line, such as:
```
  $ sort < files.txt > files_sorted.txt
```
###Advanced Redirection
Adding a `&` with the `>` symbol results in redirecting both standard out and standard error.
For example, the `test.cpp` file prints the string "stdout" with `cout` and the string "stderr" with `cerr`.
```
  $ g++ test.cpp 
  $ ./a.out >& test.txt
  $ cat test.txt
  stdout
  stderr
```
The `>` symbol alone only redirects standard output. 
If you only want to redirect a specific file descriptor you can attach the file descriptor number to `>`.

Name | File Descriptor | Description
--- | --- | --- 
stdin | 0 | standard input stream
stdout | 1 | standard output stream
stderr | 2 | standard error output stream
For example, if I only wanted to redirect "stderr" to the file `test.txt` from the above example, I would do the following:
```
  $ g++ test.cpp 
  $ ./a.out 2> test.txt
  stdout
  $ cat test.txt
  stderr
```
##Permissions
The command `ls -l` prints out a lot of information about each file that is informative about the permissions.
```
  $ ls -l test.txt
  -rw-rw-r--  1  user  group  1097374 January 26 2:48 test.txt
``` 

Output from example above | Description/Possible Outputs 
--- | --- 
- | File type:  `-`= regular file  `d`= directory 
rw- | Permissions for owner of file
rw- | Permissions for members of the group owning the file
r-- | Permissions for all other users
user | name of user
group | name of group
###chmod
The `chmod` command, short for change mode, changes the permissions of a file. 
There is a combination of letters that need to be known in order to change specific users' permission. 

Letter | User
--- | ---
u | User who owns it
g | Users in the group
a | All users
You call `chmod` by describing which actions you want to perform and to which file.
The `-` symbol represents taking away permissions while the `+` symbol represents adding permissions.
The following example makes the file readable and writable to the user who owns it and the group.
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
Each set of permissions represents a single digit so the following commands have the same outcome as above.
```
  $ chmod 660 test.txt
```
[See permissions tutorial](../../textbook/using-bash/file-permission)
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
CTRL-L | Clears terminal screen
