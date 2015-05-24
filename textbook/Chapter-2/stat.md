#System calls to get the status of a file

This document contains information on how to get the status of a file. The system calls described here are `stat`, `fstat`, and `lstat`.

## What does stat, fstat, and lstat do?
`stat`, `fstat`, and `lstat` obtain information of a file. All three return a `stat` structure when successful.

The `stat` structure is as follows:
```
struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* inode number */
               mode_t    st_mode;        /* protection */
               nlink_t   st_nlink;       /* number of hard links */
               uid_t     st_uid;         /* user ID of owner */
               gid_t     st_gid;         /* group ID of owner */
               dev_t     st_rdev;        /* device ID (if special file) */
               off_t     st_size;        /* total size, in bytes */
               blksize_t st_blksize;     /* blocksize for filesystem I/O */
               blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
               time_t    st_atime;       /* time of last access */
               time_t    st_mtime;       /* time of last modification */
               time_t    st_ctime;       /* time of last status change */
};
```
####Returns:
As mentioned above, a `stat` structure is returned upon sucess. If an error occurs, -1 is returned.

####Headers:
`#include <sys/types.h>` `#include <sys/stat.h>`  `#include <unistd.h>`

####Declaration:
- stat: `int stat(const char*pathname, struct stat *buf);`
- fstat: `int stat(int fd, struct stat *buf);`
- lstat: `int stat(const char*pathname, struct stat *buf);`

####[Man Page](http://linux.die.net/man/2/stat)

##Example
####Calling stat
**stat**
```
struct stat buf; 	// create a stat struct to store file status
const char* path; 	// name of the path where the file is located
stat (path, &buf); 	// call stat (no error check)
```

**fstat**
Instead of a pathname, `fstat` uses a file descriptor to stat. You can obtain a file descriptor by using the `open` syscall. (See the [file descriptors section](./fd.md))  on how to use it.)
```
struct stat buf;  	 // create a stat struct
int fd; 			// file descriptor (obtained from open syscall)
fstat (fd, &buf); 	// call fstat (no error check)
```

**lstat**
In this case, the pathname used in `lstat` is a symbolic link. Because of this, `lstat` returns information about that link and not the file itself.
```
struct stat buf;		// create a stat struct
const char* symLink;	// name of symbolic link
lstat (symLink, &buf);	// call lstat (no error check)
```
####Obtaining information from stat
After successfully calling `stat`, you can now obtain information about it. Remember the `stat` structure mentioned earlier? We will be using parts of that structure to get the info we need.

Let's say that you want to know about the file's permissions. We can use the `st_mode` field and [Bitwise Operators](../bitwise-ops/README.md) to do so.

For example, we can determine if the owner has read permissions on a file stat `fStat`:
```
struct stat fStat; // assume stat was successful (no error)

if (fStat.st_mode & S_IRUSR) // bitwise ops is used here
  cout << "The owner has read permissions";
else
  cout << "Owner does NOT have read permissions"
```
Similarily, you can do bitwise ops with the `st_mode` field to obtain info about the other permissions. Below is a list of some of them.

Flag    | Permission
------- | ------------------------------
S_IRUSR | Owner has read permission
S_IWUSR | Owner has write permission
S_IXUSR | Owner has execute permission
S_IRGRP | Group has read permission
S_IWGRP | Group has write permission
S_IXGRP | Group has execute permission
S_IROTH | Others have read permission
S_IWOTH | Others have write permission
S_IXOTH | Others have execute permission

Besides the `st_mode` field, you can access the other fields to obtain information about the file.

## Summary
In conclusion, here's how the `stat` syscall works:

1. Create an empty `stat` structure to store the stat.
2. Get stat by calling it:
  - If you have a path name:
    - Path name is NOT a symbolic link:
      - use `stat()`
    - Path name is a symbolic link:
      - use `lstat()`
  - If you have a file descriptor (obtained from using `open`):
    - use `fstat()`
3. Obtain information from the stat (i.e. `fStat.st_mode`) and use bitwise ops if necessary.
