# adding redirection to your shell

### coding requirements

Extend your `rshell` program so that it properly handles input redirection `<`, output redirection `>` and `>>`, and piping `|`.  This will require using the Unix functions `dup2` and `pipe`.

For example, after this assignment, your program should be able to successfully handle the following command:

```
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2 &
```

**IMPORTANT:** This is a necessary but not sufficient test case.  You must come up with others on your own.

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

You SHOULD talk to other students about test cases.  You are allowed to freely share ideas in this regard.

### grading

25 points for input redirection `<`

25 points for output redirection `>` and `>>`

50 points for piping `|`

#### extra credit

The bash shell has an additional form of input redirection that let's you redirect from a string instead of a file.  For example, these two commands will give us the same output:

```
$ echo extra credit rocks | cat
$ cat <<< "extra credit rocks"
```

You can receive up to 25 points extra credit for implementing this functionality.

Bash has an extensive syntax for redirection that let's you specify which file descriptors to redirect from and to.  You can receive up 50 points extra credit (in addition to the 25 points above) for fully implementing this syntax.  See the linux documentation project's bash io-redirection tutorial for details on the syntax: http://www.tldp.org/LDP/abs/html/io-redirection.html
