#Obtaining Information on Directories

This markdown file explains the usage of `dir_demo`, which accepts a single argument.
If the argument is a path to a directory name, then `dir_demo` will print out the contents of the directory on a single line.
For example, if we passed in `../syscalls` or `.` to dir_demo, it would print out all the markdown and source code files within this directory.
`dir_demo` utilizes the system calls `opendir`, `readdir`, and `closedir`, as well as several streams and structs unique to these system calls, directories, and their contents. 
The source code is available in `dir_code.cpp`.

##Code

```
if(argc <= 1)
{
	cout << "Nothing passed in to argv." << endl;
    exit(1);
}
else
{
    DIR *dirp;
    if(NULL == (dirp = opendir(argv[1])))
    {
        perror("There was an error with opendir(). ");
        exit(1);
    }
    struct dirent *filespecs;
    int errcheck;
    while(NULL != (filespecs = readdir(dirp)))
    {
         errcheck = errno;
        if(errcheck == -1)
        {
            perror("There was an error with readir(). ");
            break;
        }
        cout << filespecs->d_name << " ";
    }
    cout << endl;
    if(-1 == closedir(dirp))
    {
        perror("There was an error with closedir(). ");
        exit(1);
    }
}

```

##Explanation

**opendir**

**Headers:**
`#include <sys/types.h>`, `#include <dirent.h>`

**Declaration:**
`DIR *opendir(const char *name);` `DIR *fdopendir(int fd);`

**Returns:** 
Returns a pointer to a stream of the directory passed in. 
Returns a `NULL` if an error occurred.

We begin by first allocating some memory that will be utilized with all three system calls used in this demo: the s/DIR/`DIR` data type.
It acts as a stream to the contents of any directory passed into `opendir`, which we call next.
Note that the call to `opendir` will only succeed and fill the `DIR` stream if a valid directory is passed in as its sole argument, otherwise it will return the `NULL` value to the stream.
The "failed" state of the `DIR` stream is a factor we can use for error checking.

```
DIR *dirp;
//opendir returns a pointer or NULL to dirp
if(NULL == (dirp = opendir(argv[1])))
{
    perror("There was an error with opendir(). ");
    exit(1); //permission to directory denied, wrong directory name, not a directory
} 
```

**readdir**

**Headers:**
`#include <dirent.h>`

**Declaration:**
`struct dirent *readdir(DIR *dirp);` `int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);`

**Returns:** 
Returns a pointer to the next directory entry within the `DIR` stream that was passed in. 
Returns a `NULL` upon error or the end of `DIR` stream.

Now that we have the `DIR` stream `dirp` filled, we can use the system call `readdir` on it to extract individual file information from it. 
`readdir` uses the stream as an argument to return a pointer to the `dirent` struct that holds individual file specifics from the files in the directory.
We must allocate memory of the `struct dirent` to access the info that `readdir` will return.

```
struct dirent *filespecs;
int errcheck; //error value for error checking
//readdir will overwrite filespecs using a different file from the directory
while(NULL != (filespecs = readdir(dirp)))
{
    errcheck = errno;
    if(errcheck == -1)
    {
        perror("There was an error with readir(). ");
        break; //reached end of directory or invalid directory stream
    }
    //access file specifics here, such as printing out a file name
    cout << filespecs->d_name << " ";
}
cout << endl;
```

We use a loop to repeatedly call `readdir` due to the way `readdir` is implemented. 
If called again with the same arguments, `read` will read the next file in the directory stream until it reaches the end of the directory, where `readdir` will return a `NULL`.
We use the `errno` value to track when `readdir` ends.

As `filespecs` is a struct, it contains its own values that `readdir` will overwrite based on the file that is currently passed into `readdir` from the `DIR` stream.
The attributes of the struct include:

```
struct dirent
{
	ino_t			d_ino;		 /* inode number*/
	off_t			d_off;		 /* not an offset; see NOTES */
	unsigned short	d_reclen;	 /* length of this record */
	unsigned char	d_type;		 /* type of file; not supported
								    by all filesystem types */
	char			d_name[256]; /* filename */

}
```

It is possible to do far more with the file-specific values than just printing their names out.
You can save wanted attributes to other data structures like vectors, and use them in conjunction with other system calls like `stat` to access even more specifics about said files.

**closedir**

**Headers:**
`#include <sys/types.h>` `#include <dirent.h>`

**Declaration:**
`int closedir(DIR *dirp);`

**returns:** 
Returns a 0 on success. 
Otherwise, returns -1 if an error occurred.

It is always good practice to close a directory stream to conserve memory when we no longer need it.
Closing a directory uses `closedir`, and is simple to call; it takes in the `DIR` stream, and returns a value to indicate whether it succeeded or not.

```
if(-1 == closedir(dirp))
{
    perror("There was an error with closedir(). ");
    exit(1); //invalid DIR stream
}
```

##Man Pages
[opendir](http://linux.die.net/man/3/opendir) <br />
[readdir](http://linux.die.net/man/3/readdir) <br />
[closedir](http://linux.die.net/man/3/closedir) <br />
