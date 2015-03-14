#System Calls related to Manipulating File Descriptors

This file contains information on the system calls needed to manipulate file descriptors in general. In combination, these system calls will ultimately allow the writer to create or add on to files with code. The system calls that follow are `open`, `read`, `write`, and `close`.

##open

**includes:** `#include <sys/types.h>, `#include <sys/stat.h>`, `#include <fcntl.h>`

**declaration:** `int open(const char *pathname, int flags);`
			`int open(const char *pathname, int flags, mode_t mode);`
			`int creat(const char *pathname, mode_t mode);`

**returns:** Returns the value of the new file descriptor, or -1 if an error occurred.

[man page](http://linux.die.net/man/2/open)

The `open` system call takes in a name for an existing or non-existent file and returns an associated file descriptor to that file. The file descriptor can then be used with other system calls to change its contents and reflect those changes to the file it originated from. It can be seen as an editable form of the file identified by an integer value. Note that `open` will assign the file descriptor the next available file descriptor value in the kernel.

`open` cannot be used without also passing in flags that determine the end-goals of the file descriptor it returns. Looking to simply open a file to use its contents? The flag macro `O_RDONLY` returns a file descriptor that does that. Looking to create a new file from nothing? The flag macros `O_CREAT` coupled with `O_WRONLY` returns a file descriptor that does that. Looking to add on to an existing file? The flag macros `O_APPEND` and `O_WRONLY` returns a file descriptor that does that. 

As `open` only takes in three arguments, how would we fit multiple flags into just one argument? Simply line them up in one argument, and separate each flag with bitwise operator `|`.

There are 2 types of flags to consider: the access mode, and the creation/status flag. Both of these are essential to open functioning as intended and determining what open will do. The access mode asks for access to a file, requesting permissions that are defined by the macros `O_RDONLY`(read), `O_WRONLY`(write), and `O_RDWR`(read/write). The creation/status flag tells open what the file descriptor should do after it is closed. There are many flags to cover, but this file will only cover the two used in the scope of this class. The creation flag `O_CREAT` tells the file descriptor to create a file on end, regardless if the file exists or not. If the file exists, then all content in the file would be overwritten for the new created content. The status flag `O_APPEND` opens the file descriptor to add on to the root file, attaching all content in the file descriptor to the very end of the root file. The status flag `O_TRUNC` takes an existing file(if any), and overwrites all data within that file with the contents of the file descriptor upon closing.

An example of using `open` to create a new file descriptor to a new file is shown below:
```
int fd; //We need an integer to place the file descriptor somewhere for future use
if(-1 == (fd = open("testfile", OWRONLY | O_CREAT)))
{
	perror("There was an error with open(). ");
	exit(1); //The file already exists
}
```
Just because we created a new file does not mean it has any permissions attached to it! As is, this code will create a file with no actual permissions, meaning nobody will be able to access the file generated! With the `O_APPEND` flag it is possible to get by without including a third argument as those entail the permissions of the file as they already exist. For creation(`O_CREAT`) flags however, it is mandatory that they are included or else the file created will be inaccessible to anyone.

These permissions exist as octal values conveniently assigned to macros for use. This tutorial will only cover the ones used in the scope of this file, and the rest may be looked up in the man page. These mode flags can be linked together with bitwise operator `|` like the mode access and creation/status flags.
```
S_IRUSR 00400	user has read permission
S_IWUSR 00200	user has write permission
```

With our newfound knowledge, we can now properly open a file descriptor to a file:
```
int fd; //We need an integer to place the file descriptor somewhere for future use
if(-1 == (fd = open("testfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
{
	perror("There was an error with open(). ");
	exit(1); //The file already exists
}
```
This code will create a file called "testfile" with user-read and user-write permissions granted to it, so that the user of the computer will be able to edit the file later on in future use.

The system call `creat` is a variation of `open`, and is equivalent to the code below with the only two argument types:
```
open(//file descriptor, O_CREAT | O_WRONLY | O_TRUNC, //modes)
```

##read

**includes:** `#include <unistd.h>`

**declaration:** `ssize_t read(int fd, void *buf, size_t count);`

**returns:** Returns a -1 if no bytes are read, and returns the number of bytes read on success. Will also return a 0 if no bytes are read, indicating the end of a file.

[man page](http://linux.die.net/man/2/read)

The `read` system call will take in a file descriptor, and pass its contents into the buffer assigned. The amount of bytes passed into the buffer from the file descriptor is dependent on the numerical value passed into the third argument.

The `read` system call is special in that it can pick up and resume from where its previous stopping point ended if `read` is called again with the same buffer and file descriptor. It is possible to then transport an entire file descriptor into a buffer with subsequent calls of `read` with varying `count` values. In turn, it is also possible to transport an entire file descriptor into a buffer with just one call of `read`, if the amount of bytes to be read covered the entire scope of the file descriptor.

An example of using `read` to place the contents of a file descriptor into a buffer:
```
int fd;
if(-1 == (fd = open("examplefile", O_RDONLY)))
{
	perror("There was an error with open(). ");
	exit(1); //Invalid permissions to create a file descriptor, file does not exist
}

int size;
char c[BUFSIZ]; //The buffer of size BUFSIZ, which will be the size of the resulting file descriptor
if(-1 == (size = read(fd, c, sizeof(c))))
{
	perror("There was an error with read(). ");
	exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value
}
while(size > 0)
{
	if(-1 == (size = read(fd, c, sizeof(c))))
	{
		perror("There was an error with read(). ");
		exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value
	}
}
```

##write

**includes:** `#include <unistd.h>`

**declaration:** `ssize_t write(int fd, const void *buf, size_t count);`

**returns:** Returns a -1 if an error occured. Otherwise, returns the number of bytes successfully written or a 0 if nothing was written.

[man page](http://linux.die.net/man/2/write)

The `write` system call will take in a buffer, and send its contents into a file referred to by its file descriptor. The amount of bytes written to the file from the buffer is dependent on the numerical value passed into the third argument.

The `write` system call is also special in that it can also pick up and resume from where its previous stopping point ended if `write` is called again with the same buffer and file descriptor much like `read`. It is possible to then transport the contents of the entire buffer into a file with subsequent calls of `write` with varying `count` values. In turn, it is also possible to transport the entirety of a buffer into a file with just one call of `write`, if the amount of bytes to be written equaled the entire buffer in question.

An example of using `write` to read from an available buffer to a file descriptor:
```
int fd; //We need an integer to place the file descriptor somewhere for future use
if(-1 == (fd = open("testfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
{
	perror("There was an error with open(). ");
	exit(1);
}

 //Assume we already have a filled buffer c,
if(-1 == write(fd, c, sizeof(c)))
{
	perror("There was an error with write(). ");
	exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte size
}
```

##close

**includes:** `#include <unistd.h>`

**declaration:** `int close(int fd);`

**returns:** Returns a -1 if an error occured, or a 0 if the file descriptor was successfully closed.

[man page](http://linux.die.net/man/2/close)

The system call `close` closes the file descriptor passed in, so that it may not be available for editing in code beyond the `close` system call. Closing file descriptors is important as it not only frees up the value of the file descriptor for resource allocation, it also prevents any additional changes to be made to the descriptor from future code. At this point, the file descriptor acts based on what flags were assigned to it, such as creating/overwriting a file or appending to an existing one.

An example of using the `close` system call:
```
if(-1 == close(fd))
{
	perror("There was an error with close(). ");
	exit(1); //Invalid file descriptor
}
```
In this code the file descriptor attached to the variable `fd` is closed. The value pertaining to the file descriptor is now freed, and can be used again for subsequent system calls.

##Additional Resources

* [Demonstration: Manipulating File Descriptors](./fd_demo.md)
* [Bitwise Operators](../bitwise-ops/README.md)
