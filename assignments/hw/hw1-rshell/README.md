# writing a basic command shell

### coding requirements

Write a command shell called `rshell`.  Your shell will perform the following steps:

1. Print a command prompt (e.g. `$`)

2. Read in a command on one line.  Commands will have the form: `commandName [ argumentList ] [ & ]`, where `commandName` is an executable program in the `PATH` and `argumentList` is a list of zero or more words.

3. Execute the command.  This will require using the system functions `fork`, `execvp`, and `wait`.

4. If the command was followed by the `&` character, do not wait for the command to finish; immediately return to step 1.  Otherwise, wait until the command finishes before returning to step 1.

5. You must have a special built in command of `exit` which exits your shell.

6. Anything that appears after a `#` character should be considered a comment.

For example, in the command `ls -lR /`, you would execute the program `/usr/bin/ls` passing into it the parameters `-lR` and `/`.  But in the command `ls # -lR /`, you would execute `/usr/bin/ls`, but you would not pass any parameters because they appear in the comment section.

**IMPORTANT:** Most bash commands are actually executables located in `/usr/bin`.  But some commands are special and are built in to bash.  The `cd` command is the most common example.  So while the `ls` command should "just work" for you, the `cd` command won't.  You'll be adding this feature in a later homework.

**HINT:** Pay careful attention to how you parse the command string the user enters.  There are many ways to mess this up and introduce bugs into your program.  You will be adding more parsing features in future assignments, so it will make your life much easier if you do it right the first time!

### submission instructions

Create a new project on github called `rshell`.  Create a branch called `exec`.  Do all of your work under this branch.  When finished, merge the `exec` branch into the `master` branch, and create a tag called `hw1`.

To download and grade your homework, the TA will run the following commands:

```
$ git clone  http://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw1
$ make
$ bin/rshell
```

You should ssh into `well.cs.ucr.edu` and run the above commands to verify that you've submitted your code successfully.  To ensure that your `hw1` tag is getting pushed to github correctly, you may have to run the command: `git push origin hw1` instead of just `git push`.  

### project structure

**IMPORTANT:** The file/directory names below are a standard convention.  You must use the exact same names in your project, including capitalization.

You must have a directory called `src` which contains all the source code files for the project.

You must have a `Makefile` in the root directory.  In the `Makefile` you will have two targets.  The first target is called `all` and the second target is called `rshell`.  Both of these targets will compile compile your program using `g++` with the flags: `-Wall -Werror -ansi -pedantic`.

You must NOT have a directory called `bin` in the project; however, when the project is built, this directory must be created and all executable files placed here.

You must have a `LICENSE` file in your project.  You may select any open source license.  I recommend either GPL or BSD3.

You must have a `README` file.  Calling the file `README.md` is also acceptable if you want to use markdown syntax.  This file should briefly summarize your project.  In particular, it must include a list of known bugs.  If you do not have any known bugs, then you probably have not sufficiently tested your code.  See the testing section below for more details.

You must have a directory called `tests`.  The directory will contain a file called `exec.script` that contains all of the test cases you tried.  You will generate the file using the `script` command, and it must be succinct (i.e. it cannot have unnecessary commands in it).  You should use comments in your script to document what you are testing.

### testing

Proper testing is the most important part of developing software.  It therefore will have a very large impact on your grade. 

It is not enough to simply show that your program works in some cases.  You must show that it works in every possible edge case.  **That means you must try to write test cases that will break your program!**  

The code you are writing is complex, and complex programs always have bugs.  That's okay!  You can still get a 100% on this assignment if your program doesn't work for all edge cases.  But you must explicitly document the cases where it does and does not work. 

**IMPORTANT:** If you do not include a particular test case that we think is important, then we will assume your program fails that test.  It doesn't matter if your program actually passes the test or not.  If you didn't test that case and document it, then your program fails!

If you are unsure if your test cases are sufficient, ask one of the instructors to review them *before the deadline*.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You SHOULD talk to other students about test cases.  You are allowed to freely share ideas in this regard.

### grading

20 points for setting up the project correctly

20 points for executing commands

20 points for properly handling commands with and without `&`

20 points for the exit command

20 points for comments

**IMPORTANT:** Your test cases are not explicitly listed in the grading schedule above, but they are included implicitly in each category.  For example, if you get the background processes working correctly (`&`), but do not test and document that feature, then you will get zero credit in that category.

#### extra credit

Many shells display extra information in the prompt besides just a simple `$`.  For example, it is common to display the currently logged in user, and the hostname of the machine the user is logged into.  My username is `mizbi001`, and if I'm logged into the machine `alpha023`, then my prompt would look like:

```
mizbi001@alpha023$
```

You can get up to 20 points of extra credit if your prompt prints this extra information.  You will need to lookup the functions `getlogin_r` and `gethostname`.  You must not hard code the username/hostname!
