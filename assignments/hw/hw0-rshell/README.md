# writing a basic command shell

### coding requirements

Write a command shell called `rshell`.
Your shell will perform the following steps:

1. Print a command prompt (e.g. `$`)

2. Read in a command on one line.
Commands will have the form:
```
cmd         = executable [ argumentList ] [ connector cmd ]
connector   = || or && or ;
```
where `executable` is an executable program in the `PATH` and `argumentList` is a list of zero or more arguments separated by spaces.
The connector is an optional way you can run multiple commands at once.
If a command is followed by `;`, then the next command is always executed;
if a command is followed by `&&`, then the next command is executed only if the first one succeeds;
if a command is followed by `||`, then the next command is executed only if the first one fails.
For example:
```
$ ls -a
$ echo hello
$ mkdir test
```
is equivalent to:
```
$ ls -a; echo hello; mkdir test
```
There should be no limit to the number of commands that can be chained together using these operators,
and your program must be able to handle any combination of operators.
For example, you should be able to handle the command:
```
$ ls -a; echo hello && mkdir test || echo world; cd test
```

3. Execute the command.
This will require using the syscalls `fork`, `execvp`, and `waitpid`.
Previous cs100 students created a [written tutorial](../../../textbook/assignment-help/syscalls)
and two video tutorials
( [a fun cartoon tutorial](http://youtu.be/2c4ow5RoKA8)
; [more serious explanation](https://www.youtube.com/watch?v=xVSPv-9x3gk)).
You should also refer to the man pages for detailed instructions.

4. You must have a special built-in command of `exit` which exits your shell.

5. Anything that appears after a `#` character should be considered a comment.
For example, in the command `ls -lR /`, you would execute the program `/bin/ls` passing into it the parameters `-lR` and `/`.
But in the command `ls # -lR /`, you would execute `/bin/ls`, but you would not pass any parameters because they appear in the comment section.

**IMPORTANT:**
Most bash commands are actually executables located in `/bin`, `/usr/bin/` (e.g. `ls`).
But some commands are built-in to bash (e.g. `cd`).
So while the `ls` command should "just work" in your shell, the `cd` command won't.
You'll be adding this feature in a later homework.

**HINT:**
Pay careful attention to how you parse the command string the user enters.
There are many ways to mess this up and introduce bugs into your program.
You will be adding more parsing features in future assignments, so it will make your life much easier if you do it right the first time!
I recommend using either the `strtok` function from the C standard libraries (see [this tutorial](../../../textbook/assignment-help/strtok/README.md) by former cs100 student Dave MacPherson) or the `Tokenizer` class provided in the boost library (see [this tutorial](../../../textbook/assignment-help/BoostTokenizer/README.md) by former cs100 students Chelsey Calingo and Virgilio Garcia).
Students often don't do this section of the assignment well and end up having to redo all of assignment one in order to complete the future assignments.

### submission instructions

Create a new project on github called `rshell`.
Create a branch called `exec`.
Do all of your work under this branch.
When finished, merge the `exec` branch into the `master` branch, and create a tag called `hw0`.
Remember that tags and branches in git are case sensitive!

To download and grade your homework, the TA will run the following commands from the `hammer` server:

```
$ git clone  https://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```

You should ssh into `hammer.cs.ucr.edu` and run the above commands to verify that you've submitted your code successfully.
If you forget how to use git, two students from previous cs100 courses (Rashid Goshtasbi and Kyler Rynear) made [video tutorials on the git commands needed to submit your assignments](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#tags) via github.

**Do not wait to upload your assignment to github until the project due date.**
You should be committing and uploading your assignment continuously.
If you wait until the last day and can't figure out how to use git properly, then you will get a zero on the assignment.
NO EXCEPTIONS.

### project structure

You must have a directory called `src` which contains all the source code files for the project.

You must have a `Makefile` in the root directory.
In the `Makefile` you will have two targets.
The first target is called `all` and the second target is called `rshell`.
Both of these targets will compile your program using `g++` with the flags: `-Wall -Werror -ansi -pedantic`.

You must NOT have a directory called `bin` in the project;
however, when the project is built, this directory must be created and all executable files placed here.

You must have a `LICENSE` file in your project.
You may select any open source license.
I recommend either GPL or BSD3.

You must have a `README.md` file.
This file should briefly summarize your project.
In particular, it must include a list of known bugs.
If you do not have any known bugs, then you probably have not sufficiently tested your code!
For more details on how to write a good README file, see [this tutorial](../../../textbook/bestpractices/WritingREADMEs/README.md) by former cs100 student Alexander Ortiz.
You must use [the Markdown formatting language](../../../textbook/bestpractices/WritingREADMEs/Markdown.md) when writing your README.

You must have a directory called `tests`.
The directory will contain a file called `exec.script` that contains all of the test cases you tried.
You will generate the file using the `script` command, and it must be succinct (i.e. it cannot have unnecessary commands in it).
You should use comments in your script to document what you are testing with each test case.
[This video tutorial](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#script) explains how to use the `script` command.

**IMPORTANT:**
The file/directory names above are a standard convention.
You must use the exact same names in your project, including capitalization.

### coding conventions

Your code must not generate any warnings on compilation.

Your final executable must have no memory leaks.

Your code must be properly indented.
I don't care if you indent with tabs or with spaces, but you must be consistent.
Any submission that uses both spaces and tabs for indentation will receive an automatic -20 points.

Every time you run a syscall, you must check for an error condition.
If an error occurs, then call `perror`.
For every syscall you use that is not error checked, you will receive an automatic -5 points.
For examples on when, how, and why to use `perror`, see [this video tutorial](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#perror).

### testing

Proper testing is the most important part of developing software.
It therefore will have a very large impact on your grade.

It is not enough to simply show that your program works in some cases.
You must show that it works in every possible edge case.
**That means you must try to write test cases that will break your program!**

**IMPORTANT:**
If you do not include a particular test case that we think is important, then we will assume your program fails that test.
It doesn't matter if your program actually passes the test or not.
If you didn't test that case and document it, then your program fails!

If you are unsure if your test cases are sufficient, ask one of the instructors to review them *before the deadline*.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You are ENCOURAGED to talk with other students about test cases.
You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at [bash's source code](https://www.gnu.org/software/bash/) for inspiration.

### grading

30 points for executing commands

30 points for executing multiple commands on a single line with `;`, `&&`, and `||`

20 points for the `exit` command

20 points for comments

<!--

test cases for part 1 (each worth 5 pts):

* run any command with no params

* run any command with a small number of params

* run any command with a large (>10) number of params

* run both a command in `/bin` and a command in the current directory; for example, run rshell from within rshell

* if command doesn't exist, must print appropriate error message

* verify their parsing works by trying to add lots of spaces between parameters, e.g. `     ls      -a -l        -R`

test cases for part 2: (total 35 points, so possibility of extra credit)

* simple example showing two commands connected with each operator; they must show both the case where the first command succeeds and the case where the first command fails. (15 pts)

* an example showing lots of commands chained together (5 pts)

* two examples mixing and matching different operators in one command (10pts)

* parsing example showing that the operators can be right next to each command or they can have spaces separating them; e.g. `ls -l||cat        ; rm -rf *` (5pts)

test cases for part 3: (5 pts each)

* exit all by itself

* exit with parameters passed to it (I don't care if it exits or prints an error)

* exit as a parameter to something else shouldn't exit, e.g. `ls -l exit`

* exit in a chain of commands should exit, e.g. `ls -l; exit`

test cases for part 4:

* comment within a command: `ls -l # this is a comment` (10 pts)

* comment on a line by itself (5 pts)

* comment where `#` touches something else: `ls -l# this is a comment here` (5 pts)

other deductions:

* if they have any binary files in their project, they get -20 points

* if the LICENSE file is missing -5 pts

* if the README is not relatively nice, they get -10 points

* for every syscall that is not error checked they get -5 pts (grading script checks this automatically)

* for every warning during compilation they get -5 pts

* for every memory leak reported by `valgrind` -5 pts up to -20 points; if `valgrind` wasn't run then -20 points

* for every error reported by cppchecker, -5 points

extra credit:

* if all of their prompts have the information, then +10pts

* if they provide extra test cases that are particularly nice, they can get up to +10 points

-->

**IMPORTANT:**
Your project structure is not explicitly listed in the grading schedule above.
But for each part of the project structure you don't follow, you will receive an automatic -20 points.

**IMPORTANT:**
Your test cases are also not explicitly listed above, but they are included implicitly in each category.
For example, if you get comments working correctly, but do not test and document that feature, then you will get zero credit for comments.

#### extra credit

Many shells display extra information in the prompt besides just a simple `$`.
For example, it is common to display the currently logged in user, and the hostname of the machine the user is logged into.
My username is `mizbi001`, and if I'm logged into the machine `alpha023`, then my prompt would look like:
```
mizbi001@alpha023$
```
You can get up to 10 points of extra credit if your prompt prints this extra information.
You will need to lookup the man pages for the functions `getlogin` and `gethostname`.
You must not hard code the username or hostname!

**REMINDER:**
If anything is unclear about this assignment, remember that you can get extra credit by submitting pull requests and asking good questions in the issue tracker.

## additional resources

Here is a complete list of resources created by previous cs100 students that might help with this assignment:

* [written tutorial on syscalls](../../../textbook/assignment-help/syscalls/exec.md)

* video: [a fun cartoon tutorial](http://youtu.be/2c4ow5RoKA8)

* video: [explanation of `fork` and `exec`](https://www.youtube.com/watch?v=xVSPv-9x3gk)

* video: [using bash, github, vim, and syscalls](https://izbicki.me/blog/videoguide-for-github-vim-bash.html)

* [writing README files](../../../textbook/bestpractices/WritingREADMEs/README.md)

* [the Markdown formatting language](../../../textbook/bestpractices/WritingREADMEs/Markdown.md)

* [writing Makefiles](../../../textbook/tools/Makefiles/README.md)
