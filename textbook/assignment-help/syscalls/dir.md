#Obtaining Information on Directories

This markdown file demonstrates how to use the system calls `opendir`, `readdir`, and `closedir` through the example program `dir_demo`. 
`dir_demo` is a program that accepts a single argument; if the argument is a path to a directory name, then `dir_demo` will print out the contents of the directory on a single line.
For example, if we passed in `../syscalls` or `.` to dir_demo, it would print out all the markdown and source code files within this directory.
`dir_demo` uses the system calls `opendir`, `readdir`, and `closedir`, as well as several streams and structs unique to these system calls and directories to achieve the intended result.
The source code is available in [`dir_code.cpp`](./dir_code.cpp).

----

We begin by opening the directory with `opendir` to give us a `DIR*`.
We use the first parameter of the program (`argv[1]`) as the directory we want to open:

```
DIR *dirp;
if(NULL == (dirp = opendir(argv[1])))
{
    perror("There was an error with opendir(). ");
    exit(1);
} 
```
Notice if `opendir` fails it returns `NULL`, and we're performing proper error checking.

Next, we use `readdir` to read through the directory's contents. We pass in the `DIR*` to `readdir` and it returns a `struct dirent`, which holds the data of our directory names that we print out:

```
struct dirent *filespecs;
int result;
while(result == (filespecs = readdir(dirp)))
{
    cout << filespecs->d_name << " ";
}
```

We use a loop to call `readdir` on the entire directory.
Multiple calls of `readdir` with the same argument will read the next file in the directory automatically and overwrite the current data in the struct.

`readdir` returns a `NULL` upon reaching the end of a directory, so we use that to end our loop.
Note that we do use error-checking by checking if `errno` has changed since running `readdir`:

```
errno = 0;
//loop running readdir
if(errno != 0)
{
        perror("There was an error with readdir(). ");
        exit(1);
}
```

We've finished printing the contents of the directory, so let's close the stream to conserve memory with `closedir`.
Pass in the `DIR*` as the argument:

```
if(-1 == closedir(dirp))
{
    perror("There was an error with closedir(). ");
    exit(1);
}
```

`closedir` returns a -1 if there is an error, so we perform error-checking in the event that it happens. 

##Man Pages
[opendir](http://linux.die.net/man/3/opendir) <br />
[readdir](http://linux.die.net/man/3/readdir) <br />
[closedir](http://linux.die.net/man/3/closedir) <br />
