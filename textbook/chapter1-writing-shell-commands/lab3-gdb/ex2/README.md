###Exercise 2: a simplified ls program

[`ex2.cpp`](ex2.cpp) is a program that outputs specific information of specified files.
The program uses the `stat` system call to create a struct for each filename passed in.
The struct has the following members:

```
    struct stat {
        dev_t     st_dev;     /* ID of device containing file */
        ino_t     st_ino;     /* inode number */
        mode_t    st_mode;    /* protection */
        nlink_t   st_nlink;   /* number of hard links */
        uid_t     st_uid;     /* user ID of owner */
        gid_t     st_gid;     /* group ID of owner */
        dev_t     st_rdev;    /* device ID (if special file) */
        off_t     st_size;    /* total size, in bytes */
        blksize_t st_blksize; /* blocksize for file system I/O */
        blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
        time_t    st_atime;   /* time of last access */
        time_t    st_mtime;   /* time of last modification */
        time_t    st_ctime;   /* time of last status change */
    };
```
_Taken from the stat(2) manpage_

Compile and run the program with:
```
$ g++ -g ex2.cpp -o ex2
$ ./ex2 README.md ex2.cpp
```
(The arguments to `ex2` specify which files to output information for.)

You should get the following output:
```
$ a.out ex2.cpp README.md
|??|-------README.md
|??|---------ex2.cpp
```

The output is similar to the output of `ls -l`.
But this program is missing the user permissions that each file has.
You will use `gdb` to explore the `stat` version of each file.

Run GDB on the binary executable you compiled. You can run the program by
typing `r` of `run` followed by the filenames you wish to pass in.

GDB allows you to visualize structs that `cout` or `printf()` cannot output.
* Make a breakpoint at line 35. Print the struct sb. What do you see?

GDB is especially useful when using binary flags. It allows you to print
bitwise operations while stepping through a program. The flags `S_IRUSR`,
`S_IWUSR`, and `S_IXUSR` each represent a different permission.
* Use the `stat` manpage to look up the values of each of these flags.
* When paused at a breakpoint, run `print sb.st_mode & <flag value>`.
  * What are the values of the three flags for the README.md file?

[ex2.cpp](ex2.cpp) has three `if` statements in the `info` function.
Each one checks for a certain permission, then outputs a single character
corresponding to that permission. GDB allows you to check if your
programs are hitting certain `if` statements.
* Place a breakpoint at the lines with comments indicating where to place breaks.
* Run the program on different filenames. Which `if` statments are hit?
* Which characters are supposed to be printed in these statements?

_Check your work by running `ls -l` on the files you worked with._
