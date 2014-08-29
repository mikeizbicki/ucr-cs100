# adding the `ls` command to your shell

### coding requirements

Write a C++ program that implements a subset of the GNU `ls` command.  In particular, you must support: the `-a`, `-l` and `-R` optional flags; and the ability to pass in zero, one, or many files.  Notice that the GNU `ls` command handles files and folders differently, and you must reproduce this functionality exactly.  You will use the functions `readdir` and `stat`, which are provided by Unix operating systems.  For details on the use of these functions, visit their man pages.

To get you started, the file `ls.cpp` contains code that reads the files in the current working directory.  

### submission instructions

You will add this code to your `rshell` project on github.  Create a branch called `ls` and do all of your work under this branch.  When finished, merge with the `master` branch and create a tag called `hw2`.

To download and grade your homework, the TA will run the following commands:

```
$ git clone  http://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/ls
```

You should run them as well to verify that you've submitted your code successfully.

### project structure

All source files created for this program should be in your project's `src` folder.  

You will have to modify the `Makefile` to include a target called `ls` which builds your `ls` program.  The `all` target should build *both* `rshell` and `ls`.  Both binaries should be placed in the `bin` folder.  Remember that binaries should not get added to your git repo, and you will be penalized if they are.

### testing

Again, the tests you choose will be the most important part of your grade.  

Remember that the commands `ls -l -R`, `ls -R -l`, `ls -lR` and `ls -Rl` should all do the same thing.  You must consider how these flags interact with the `-a` flag and the optional file parameters.

**IMPORTANT:** If you are unsure if your test cases are sufficient, ask one of the instructors to review them *before the deadline*.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You SHOULD talk to other students about test cases.  You are allowed to freely share ideas in this regard.

### grading

25 points for the optional file parameters

25 points for the `-a` flag

25 points for the `-l` flag

25 points for the `-R` flag

#### extra credit

The GNU `ls` utility displays different types of files in different colors/fonts using [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code).  You will receive up to 25 points extra credit if your `ls` command has this ability.  In particular, you should print directories in blue; executables in green; and hidden files (with the `-a` flag only) with a gray background.  These effects should be combinable.  So if you have a hidden directory, it should be displayed as blue text on top of a gray background.
