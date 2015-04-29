# two more command line utilities

In this lab, you will add two additional command line utilities to your rshell project: rm and mv.
You will have to use the `link`, `unlink`, and `rmdir` syscalls.
We haven't discussed them in class, but you should be able to figure out how they work based on the man pages.

**IMPORTANT:**
You must use pair programming on this assignment.
That means both partners should be working together on the same terminal.
You are specifically NOT allowed to have one partner work on `rm` and the other partner work on `mv`.
Pair programming is a widely used technique in industry to boost programmer performance.
With practice, two programmers working together can be more than twice as fast as a single programmer.

#### details for `rm`

Implement your own version of the `rm` command.
You must be able to support an unlimited number of files passed in as command line parameters.
If any of those files are directories, you must not delete them unless the optional `-r` flag is also present.
Instead, print a warning message.

#### details for `mv`

Implement your own version of the `mv` command.
Given the command:

```
mv file1 file2
```

If `file2` does not exist, then you should rename `file1` to `file2`.
Otherwise, if `file2` is a directory, you should move `file1` into `file2`.
If `file2` is not a directory, you should print an error message.

### deliverables

You should submit pull requests to your partner's repo adding the rm and mv command.
As in the previous lab, you are not allowed to add the code to your own repo.
