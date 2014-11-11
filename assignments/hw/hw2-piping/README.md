# adding redirection to your shell

### coding requirements

Extend your `rshell` program so that it properly handles input redirection `<`, output redirection `>` and `>>`, and piping `|`.  
This will require using the Unix functions `dup` and `pipe`.  
The [syscalls tutorial from hw0](https://github.com/mikeizbicki/ucr-cs100/blob/cs100-2014fall/tutorials/syscalls/README.md) also covers these functions.
Of course, you should also be consulting the man pages.

As an example, after this assignment, your program should be able to successfully handle the following command:

```
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2 &
```

**IMPORTANT:** This is a necessary but not sufficient test case.  You must come up with others on your own.

Bash has an extensive syntax for redirection, and you are not required to implement all of it.
But if you're curious, see the [linux documentation project's bash io-redirection tutorial](http://www.tldp.org/LDP/abs/html/io-redirection.html) for details.

### submission instructions

You will add this code to your `rshell` project on github.  Create a branch called `redirect` and do all of your work under this branch.  When finished, merge with the `master` branch and create a tag called `hw2`.

To download and grade your homework, the TA will run the following commands:

```
$ git clone  http://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```

You should run them as well to verify that you've submitted your code successfully.

### project structure

There are no changes to your project structure.

### testing

Again, the tests you choose will be the most important part of your grade.  

You should carefully consider: which redirections can be legally combined together, and which cannot? does order matter?  Also make sure to test that you are parsing the command correctly.

**IMPORTANT:** If you are unsure if your test cases are sufficient, ask one of the instructors to review them *before the deadline*.

### collaboration policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You are ENCOURAGED to talk with other students about test cases.
You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at [bash's source code](https://www.gnu.org/software/bash/) for inspiration.

### grading

25 points for input redirection `<`

25 points for output redirection `>` and `>>`

50 points for piping `|`

#### extra credit 1

The bash shell has an additional form of input redirection that let's you redirect from a string instead of a file.  For example, these two commands will give us the same output:

```
$ echo extra credit rocks | cat
$ cat <<< "extra credit rocks"
```

You can receive up to 20 points extra credit for implementing this functionality.

#### extra credit 2

The bash shell let's you perform output redirection on whatever file descriptors you want by placing a number before the `>` command.
For example,
```
$ g++ main.cpp 2> errors
```
will direct stderr (which is where g++ prints error messages) to the file errors.
If you implement this syntax for any file descriptor and both `>` and `>>`, you will get up to 20 points extra credit.
