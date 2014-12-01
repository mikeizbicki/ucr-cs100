# adding the `ls` command to your shell

### coding requirements

Write a C++ program that implements a subset of the GNU `ls` command.  In particular, you must support: the `-a`, `-l` and `-R` optional flags; and the ability to pass in zero, one, or many files.  Notice that the GNU `ls` command handles files and folders differently, and you must reproduce this functionality exactly.  For a refresher on how to use the `ls` command effectively, you can watch [this video tutorial](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#ls).

To implement `ls`, you must use the `readdir` and `stat` syscalls.  For details on the use of these functions, visit their man pages.

To get you started, the file `ls.cpp` contains code that reads the files in the current working directory.  

### submission instructions

You will add this code to your `rshell` project on github.  Create a branch called `ls` and do all of your work under this branch.  When finished, merge with the `master` branch and create a tag called `hw1`.

To download and grade your homework, the TA will run the following commands:

```
$ git clone  http://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw1
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

As with your previous assignments: Your `tests` directory will contain a file called `ls.script` that contains all of the test cases you tried. You will generate the file using the script command, and it must be succinct (i.e. it cannot have unnecessary commands in it). You should use comments in your script to document what you are testing with each test case.

**IMPORTANT:** If you are unsure if your test cases are sufficient, ask one of the instructors to review them *before the deadline*.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You are ENCOURAGED to talk with other students about test cases.
You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at [GNU ls's source code](https://www.gnu.org/software/coreutils/) for inspiration.

### grading

25 points for the optional file parameters

25 points for the `-a` flag

25 points for the `-l` flag

25 points for the `-R` flag

#### extra credit

The GNU `ls` utility displays different types of files in different colors/fonts using [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code).
You will receive up to 15 points extra credit if your `ls` command has this ability.
In particular, you should print directories in blue; executables in green; and hidden files (with the `-a` flag only) with a gray background.
These effects should be combinable.
So if you have a hidden directory, it should be displayed as blue text on top of a gray background.

#### lab 5 integration

Everyone who showed up for lab 5 got full credit on the lab.
But your grade on this assignment will depend on your lab 5.
In particular:

0. You should include all of lab 5 in your submission (`hw1` tag) for this assignment.

1. Your `Makefile` must have an additional target called `cp`.
This target should build the `cp` program you developed in lab and place it in the `bin` folder.
The `all` target should depend on the `cp` target.

2. The resulting `cp` executable should behave as specified in the lab.
In particular: (a) I do not care what the optional parameter is, but I must be able to place the parameter anywhere in the argument list; (b) there should be an error message if the location you are copying to already exists or is a directory.

3. Your account must not make any commits to the source code for `cp`.
Only your partner's account should be making these commits.
We will verify this by running `git blame` on your source code.
It should show only your partner's name, and not yours.

If you do not meet these requirements, you will lose up to 20 points of credit on this assignment.
