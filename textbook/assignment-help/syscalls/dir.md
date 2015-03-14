#System Calls related to Obtaining Information on Directories

This file contains information on the system calls needed to gather information from directories and its contents. In combination, these system calls will allow the user to open/close directories as streams and search through the properties of each file within said directory. The system calls that follow are `opendir`, `readdir`, and `closedir`.

##opendir

**includes:** `#include <sys/types.h>`, `#include <dirent,h>`

**declaration:** `DIR *opendir(const char *name);`
			`DIR *fdopendir(int fd);`

**returns:** Returns a pointer to a stream of the directory passed in. Returns a `NULL` if an error occurred.

[man page](http://linux.die.net/man/3/opendir)

The system call `opendir` grants access to a stream of data type DIR related to the directory that was passed in the arguments. From there, system calls like `readdir` can be used to access the contents of the directory within the stream.

An example of using the `opendir` system call:
```
DIR *dirp; //Allocate data for the stream
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, or invalid directory
}
```

##readdir

**includes:** `#include <dirent,h>`

**declaration:** `struct dirent *readdir(DIR *dirp);`
			`int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);`

**returns:** Returns a pointer to the next directory entry within the `DIR` stream that was passed in. Returns a `NULL` if the function has reached the end of a directory stream or if an error occurred.

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

An example of using the `readdir` system call to parse through an entire directory, given `DIR` stream `dirp`:
```
struct dirent *filespecs; //Allocate data for the dirent struct
int errcheck; //Error value for error checking
while(filespecs = readdir(dirp))
{
	errcheck = errno;
	if(errcheck == -1)
	{
		perror("There was an error with readdir(). ");
		break; //Reached end of directory or invalid directory stream
	}
	//Access dirent struct attributes here, such as gathering a file name
}
```
##closedir

includes:** `#include <sys/types.h>`, `#include <dirent.h>`

**declaration:** `int closedir(DIR *dirp);`

**returns:** Returns a 0 on success. Otherwise, returns -1 if an error occurred.

[man page](http://linux.die.net/man/3/closedir)

The system call `closedir` closes the associated `DIR` stream passed in to the system call. Closing `DIR` streams save memory-related resources and prevent unexpected behavior by using data from a previous `DIR` stream.

An example of using the `closedir` system call after using `opendir` and `readdir`:
```
DIR *dirp; //Allocate data for the stream
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, or invalid directory
}
struct dirent *filespecs; //Allocate data for the dirent struct
int errcheck; //Error value for error checking
+while(filespecs = readdir(dirp))
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

##Additional Resources

* [Demonstration: Obtaining Information on Directories](./dir_demo.md)
