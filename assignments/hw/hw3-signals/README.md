# extending rshell again

### coding requirements

You will make three modifications to your `rshell` project.

1. Implement the `cd` command.
Every time this command is run, you must update the `PWD` and `OLDPWD` environment variables appropriately.
This will require using the `chdir`,`getenv`, and `setenv` functions.
Your implementation must support the following forms:

    a. `cd <PATH>` will change the current working directory to `<PATH>`

    b. `cd` will change the current working directory to the user's home directory

    c. `cd -` will change the current working directory to the previous working directory

1. Change your prompt so that it displays the current working directory.

1. The shell should not exit when the user types `^C`.
Instead, the current foreground job should receive the `SIGINT` signal.
If `SIGINT` kills the job, then control should return to your shell.

<!--
1. Your shell must be able to find commands (e.g. `ls` and `tee`) by searching for them using the user's current `PATH` environment variable.  Previously, you were required to only look in the directory `/usr/bin` for these commands, but now you must search many directories.  There are versions of the `exec` function that will perform this search for you automatically (e.g. `execvp`), but you are not allowed to use them.  You must use the `getenv` function to get the current `PATH`, then manually search these directories for the command.

2. The shell should not exit when the user types `^C`.  Instead, the current foreground job should interrupt.

3. Implement the `cd` command, and change your prompt so that it displays the current working directory.  This will require using the `chdir` function.
In bash, the `cd` command without an argument will change the current working directory to the home directory.
You do not have to implement this feature.
-->

### submission instructions

You will add this code to your `rshell` project on github.  You may use any number of branches/commits you find convenient.  When finished, merge with the `master` branch and create a tag called `hw3`.

To download and grade your homework, the TA will run the following commands:

```
$ git clone  http://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw3
$ make
$ bin/rshell
```

You should run them as well to verify that you've submitted your code successfully.

### project structure

There are no changes to your project structure.

### testing

Again, the tests you choose will be the most important part of your grade.

As with your previous assignments: Your `tests` directory will contain a file called `signals.script` that contains all of the test cases you tried. You will generate the file using the script command, and it must be succinct (i.e. it cannot have unnecessary commands in it). You should use comments in your script to document what you are testing with each test case.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You are ENCOURAGED to talk with other students about test cases.
You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at [bash's source code](https://www.gnu.org/software/bash/) for inspiration.

### grading

20 points for implementing `cd PATH`

20 points for implementing `cd`

20 points for implementing `cd -`

40 points for handling the `^C` signal

#### extra credit 1

Catch the `^Z` signal, and implement the `fg` and `bg` commands.
You can earn up to 30 points of extra credit for this.

#### extra credit 2

If the current working directory contains the user's homefolder, replace the home folder with a `~`.
For example, my home folder is `/home/user`.
So if I'm in the directory `/home/user/proj/ucr-cs100`, then my prompt would display `~/proj/ucr-cs100`.
If the current working directory does not contain the user's homefolder, then display the directory normally.

You can earn 5 points of extra credit for this.
It should be a very simple task.
