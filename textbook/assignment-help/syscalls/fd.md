#Manipulating File Descriptors

This markdown file explains the usage of `fd_demo`, which takes the existing file `fileold`'s contents and places them in a new file `filenew` in the current directory.
The content copied into `filenew` will have the same formatting and byte size as `fileold`.
The code utilizes the system calls `open`, `read`, `write`, and `close`, as well as file descriptors and buffers that the above system calls manipulate to create and copy to the new file.
The source code is available in `fd_code.cpp`.

##Code

`fileold`'s contents:
```
this file is 27-bytes long.
```

`fd_code.cpp`:
```
int fdnew;
if(-1 == (fdnew = open("filenew", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
{
    perror("There was an error with open(). ");
    exit(1);
}	
int fdold;
if(-1 == (fdold = open("fileold", O_RDONLY))) 
{
    perror("There was an error with open(). ");
    exit(1);
}
int size;
char c[BUFSIZ];
if(-1 == (size = read(fdold, c, sizeof(c)))) 
{
    perror("There was an error with read(). ");
    exit(1);
}
while(size > 0)
{
    if(-1 == write(fdnew, c, size))
    {
        perror("There was an error with write(). ");
        exit(1);
    }
    if(-1 == (size = read(fdold, c, sizeof(c))))
    {
        perror("There was an error with read(). ");
        exit(1);
    }
}	
if(-1 == close(fdnew))
{
    perror("There was an error with close(). ");
    exit(1);
}
if(-1 == close(fdold))
{
    perror("There was an error with close(). ");
    exit(1);
}
```

##Explanation

**open**

**Headers:**
`#include <sys/types.h>` `#include <sys/stat.h>` `#include <fcntl.h>`

**Declaration:**
`int open(const char *pathname, int flags);` `int open(const char *pathname, int flags, mode_t mode);` `int creat(const char *pathname, mode_t mode);`

**Returns:**
Returns the value of the new file descriptor, or -1 if an error occurred.

If we wish to place the message within `fileold` into a new file, we must first allocate memory for a file descriptor.
File descriptors are abstract data structures similar to buffers accessible through an integer value.
We must set an integer variable to store the file descriptor, and call the `open` system call to allocate the file descriptor to the `int`.
By default, the `open` system call will allocate the file descriptor to the lowest possible descriptor value available.
We must also `open` a file descriptor to the old file in order to access its contents for future copying.

```
int fdnew; //stores the file descriptor value
//flags and modes dictate the behavior of the file descriptor
//try to open the file with write permissions; if it doesn't exist create it with permissions S_IRUSR | S_IWUSR
if(-1 == (fdnew = open("filenew", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR))) 
{
    perror("There was an error with open(). ");
    exit(1); //Not enough shared memory to allocate file descriptor
}	
int fdold;
if(-1 == (fdold = open("fileold", O_RDONLY))) 
{
    perror("There was an error with open(). ");
    exit(1); //Not enough shared memory to allocate file descriptor
}
```

`open` can take in 3 arguments; the file name of the file descriptor is referencing to, a flag, and any additional flags represented as a mode.
The file name passed can be one that does not exist, depending on the flags and modes.
The flag and mode are defined values that determine file descriptor creation and permission behavior.
These values are represented through macros from the associated `open` libraries for convenience.
Such values are able to be appended together with the "`|`" [bitwise operator](../bitwise-ops/README.md) to form a singular value that represents multiple behaviors.

The flag argument encompasses what the file descriptor will try to enact once it is freed from memory. This also involves getting permission from the system to complete its task. <br />
The flag `O_WRONLY | O_CREAT` tells `open` to ask the system for write permissions to create a file called `filenew`.  <br />
The flag `O_RDONLY` tells `open` to ask the system only for read permissions to the existing file `fileold`.

The mode argument encompasses any additional flags that accompany the flag in argument two. <br />
The mode `S_IRUSR | S_IWUSR` define the permissions to `filenew` as read-able and write-able by the user. <br />
There are no modes set when opening `fileold` as it does not use the flag `O_CREAT`.

Once we have created the file descriptors, we can place the contents of `oldfile` into a buffer using `read`.
From there, we take the contents of the buffer and `write` it in to the file descriptor referencing the new file.
We will use a separate buffer and an `int` to keep track of the transferred content across both files.

```
int size;
//allocates buffer of size BUFSIZ, an efficient memory size dependent on the system for I/O streaming
char c[BUFSIZ];
//read will read up to the buffer size of fdold into buffer c
if(-1 == (size = read(fdold, c, sizeof(c)))) 
{
    perror("There was an error with read(). ");
    exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value
}
//Loop to ensure read transfers all bytes of fileold into c
while(size > 0)
{
	//writes to filenew the contents of fileold from c
    if(-1 == write(fdnew, c, size)) 
    {
        perror("There was an error with write(). ");
        exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte size

    }
    //read called to update size
    if(-1 == (size = read(fdold, c, sizeof(c))))
    {
        perror("There was an error with read(). ");
        exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value

    }
}
```

**read and write**

**Headers:**
`#include <unistd.h>`

**Declaration:**
`ssize_t read(int fd, void *buf, size_t count);`

`ssize_t write(int fd, void *buf, size_t count);`

**Returns:** <br />
`read`:
Returns the number of bytes read on success.
Returns a 0 if no bytes are read, indicating the end of a file.
Returns a -1 if an error occurred.
<br />
`write`:
Returns the number of bytes written on success.
Returns a 0 if no bytes are written.
Returns a -1 if an error occurred.

The `read` system call takes 3 arguments: the file descriptor to obtain data from, the buffer to send that data to, and how many bytes of data should be sent to the buffer.
The amount of bytes that can be read range from just 1 byte to a suggested maximum value given by the system for streaming, defined by the macro `BUFSIZ`.

The `write` system call also takes 3 arguments: the file descriptor to write data to, the buffer to parse the data from, and how many bytes of data that should be written to the file descriptor.
The amount of bytes written range from just 1 byte to a suggested maximum value given by the system for streaming, defined by the macro `BUFSIZ`.

The usage of `read` and `write` may exist in a loop based on the behaviors of both system calls.
If `read` is called again using the same arguments, the system call will continue from the last byte read until it reaches the end of the file, returning 0.
`write` also behaves in a similar way, with subsequent calls of `write` continuing from the last byte read until it reaches the end of a buffer, returning 0.
The size variable will keep track of when `read` has read to the end of a file, ending the loop.

**close**

**Headers:**
`#include <unistd.h>`

**Declaration:**
`int close(int fd);`

**Returns:**
Returns a 0 if the file descriptor closed successfully.
Returns a -1 if an error occurred.


Now that the content transfer is complete, it is good practice to close the related file descriptors to `fileold` and `filenew`.
Closing file descriptors frees up memory and also prevents unexpected behavior occurring to any files associated with file descriptors.
Closing file descriptors initializes their respective behaviors defined from `open`, if any.

```
if(-1 == close(fdnew))
{
    perror("There was an error with close(). ");
    exit(1);
}
if(-1 == close(fdold))
{
    perror("There was an error with close(). ");
    exit(1);
}
```

We would find the file `filenew` in the same directory after `fd_demo` finishes running, containing the same contents as `fileold`: "`this file is 27-bytes long.`".

##Man Pages
[open](http://linux.die.net/man/2/open) <br />
[read](http://linux.die.net/man/2/read) <br />
[write](http://linux.die.net/man/2/write) <br />
[close](http://linux.die.net/man/2/close) <br />
