#System calls towards gathering information on files and directories

This file contains information on the system calls needed to gather information from files and directories. In combination, these system calls will allow the user to open/close directories and search through the properties of each file within said directory. The system calls that follow are `opendir`, `closedir`, `readdir`, `stat`, `fstat`, and `lstat`.

**IMPORTANT:**
These system calls return information in data types and binary values that are ideal for computers, but not for humans, To get the information from the `stat` system call to become readable for human eyes, refer to the system calls tutorial made by past cs100 students below.
* [Obtaining info from processes](/getinfo.md)

##opendir

**includes:** `#include <sys/types.h>`, `#include <dirent,h>`

**declaration:** `DIR *opendir(const char *name);`
			`DIR *fdopendir(int fd);`

**returns:** Returns a pointer to a stream of the directory passed in. Returns a NULL if an error occurred.

[man page](http://linux.die.net/man/3/opendir)

The system call `opendir` grants access to a stream of data type DIR related to the directory that was passed in the arguments. From there, system calls like `readdir` can be used to access the contents of the directory within the stream.

An example of using the `opendir` system call:
```
DIR *dirp; //Allocate data for the stream
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, or invalid direcotry
}
```

##readdir

**includes:** `#include <dirent,h>`

**declaration:** `struct dirent *readdir(DIR *dirp); *`
			`int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);`

**returns:** Returns a pointer to the next directory entry within the DIR stream that was passed in. Returns a NULL if the function has reached the end of a directory stream or if an error occurred.

[man page](http://linux.die.net/man/3/readdir)

The system call `readdir` reads into the `DIR` stream created from `opendir` to produce a `dirent` struct containing specific info about the files or directories within the stream. The attributes of the `dirent` struct include:
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
`readdir` can be called again on the same `DIR` stream to overwrite its previous contents with the next directory entry in the stream.

An example of using the `readdir` system call to parse through an entire directory:
```
DIR *dirp; //Allocate data for the stream
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, or invalid direcotry
}
struct dirent *direntstream; //Allocate data for the dirent struct
int errcheck; //Error value for error checking
while(direntp = readdir(dirp))
{
	errcheck = errno;
	if(errcheck == -1)
	{
		perror("There was an error with readir(). ");
		break; //Reached end of directory or invalid directory stream
	}
	//Access dirent struct attributes here, such as gathering a file name
}
```

##closedir

**includes:** `#include <sys/types.h>`, `#include <dirent.h>`

**declaration:** `int closedir(DIR *dirp);`

**returns:** Returns a 0 on success. Otherwise, returns -1 if an error occurred.

[man page](http://linux.die.net/man/3/closedir)

The system call `closedir` closes the associated `DIR` stream passed in to the system call. Closing `DIR` streams can be useful to save resources and prevent unexpected behavior by using data from a previous `DIR` stream.

An example of using the `closedir` system call after using `opendir` and `readdir`:
```
DIR *dirp; //Allocate data for the stream
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, or invalid direcotry
}
struct dirent *direntstream; //Allocate data for the dirent struct
int errcheck; //Error value for error checking
while(direntp = readdir(dirp))
{
	errcheck = errno;
	if(errcheck == -1)
	{
		perror("There was an error with readir(). ");
		break; //Reached end of directory or invalid directory stream
	}
	//Access dirent struct attributes here, such as gathering a file name
}

if(-1 == closedir(dirp))
{
	perror("There was an error with closedir(). ");
	exit(1); //Invalid DIR stream
}
```

##stat:

**includes:** `#include <sys/types.h>` `#include <sys/stat.h>` `#include <unistd.h>`

**declaration:** `int stat(const char*pathname, struct stat *buf);`

**returns:** Error occurs if `-1` is returned; otherwise, a `stat` structure is returned.

[man page](http://linux.die.net/man/2/stat)

##fstat:
**includes:** `#include <sys/types.h>` `#include <sys/stat.h>` `#include <unistd.h>`

**declaration:** `int stat(int fd, struct stat *buf);`

**returns:** Error occurs if `-1` is returned; otherwise, a `stat` structure is returned.

[man page](http://linux.die.net/man/2/stat) 

##lstat:
**includes:** `#include <sys/types.h>` `#include <sys/stat.h>` `#include <unistd.h>`

**declaration:** `int stat(const char*pathname, struct stat *buf);`

**returns:** Error occurs if `-1` is returned; otherwise, a `stat` structure is returned.

[man page](http://linux.die.net/man/2/stat) 

##The stat structure:

The `stat` system call takes in a file name and returns information about that file into a `stat` struct which is passed in as the second argument. From there, it is possible to access information about the file by accessing the struct's attributes. Those attributes are shown below:
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

};

```




