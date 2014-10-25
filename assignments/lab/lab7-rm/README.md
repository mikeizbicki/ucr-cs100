# more command line utilities

The commands will require you to use the `link`, `unlink`, and `rmdir` system commands.

### `rm`

Implement your own version of the `rm` command.  You must be able to support an unlimited number of files passed in as command line parameters.  If any of those files are directories, you must not delete them unless the optional `-r` flag is also present.  Instead, print a warning message.

### `mv`

Implement your own version of the `mv` command.  Given the command:

```
mv file1 file2
```

If `file2` does not exist, then you should rename `file1` to `file2`.  Otherwise, if `file2` is a directory, you should move `file1` into `file2`.  If `file2` is not a directory, you should print an error message.

