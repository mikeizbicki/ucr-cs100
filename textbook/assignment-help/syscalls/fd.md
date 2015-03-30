#Manipulating File Descriptors

This markdown file demonstrates how to use the system calls `open`, `read`, `write`, and `close` through the program `fd_demo`. 
`fd_demo` takes the existing file `fileold`'s contents and places them in a new file `filenew` in the current directory.
The content copied into `filenew` will have the same formatting and byte size as `fileold`.
`fd_demo` uses the system calls `open`, `read`, `write`, and `close`, as well as file descriptors and buffers that the above system calls manipulate to create and copy to the new file.
The source code is available in [`fd_code.cpp`](./fd_code.cpp).

----

To begin, we'll use `open` to create file descriptors to `fileold` and non-existent `filenew`.
The file descriptors can be referenced through their integer values, which we store in `int`s.
We'll call `open` twice for both files, but we'll pass in a different flag and mode to each syscall, determining the file descriptor behavior:

```
int fdnew;
int fdold;
if(-1 == (fdnew = open("filenew", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR))) 
{
    perror("There was an error with open(). ");
    exit(1);
}	
if(-1 == (fdold = open("fileold", O_RDONLY))) 
{
    perror("There was an error with open(). ");
    exit(1); 
}
```

`open` takes in 3 arguments; a possible file name, a flag, and additional flags known collectively as a mode.
The flag and mode are values able to be appended together with the "`|`" [bitwise operator](../bitwise-ops/README.md) to form a singular value that represents multiple behaviors.

The flag argument encompasses what the file descriptor will try to enact once it is freed from memory.  <br />
The flag `O_WRONLY | O_CREAT` tells `open` to ask the system for write permissions to create a file called `filenew`.  <br />
The flag `O_RDONLY` tells `open` to ask the system only for read permissions to the existing file `fileold`.

The mode argument encompasses any additional flags that accompany the flag in `open`'s second argument. <br />
The mode `S_IRUSR | S_IWUSR` define the permissions to `filenew` as read-able and write-able by the user. <br />
There are no modes set when opening `fileold` as it does not use the flag `O_CREAT`.

If `open` fails, it will return -1 to the `int`s which we use to perform error checking with.

We have created the file descriptors; now we place the contents of `oldfile` into a buffer using `read`.
Pass in the file descriptor to `read` from(`fdold`), the buffer to read to(`c`), and the amount of bytes to read(`BUFSIZ`):

```
int size;
char c[BUFSIZ];
if(-1 == (size = read(fdold, c, sizeof(c)))) 
{
    perror("There was an error with read(). ");
    exit(1); }
}
```

We allocate the buffer to be of size `BUFSIZ`, an efficient value set by the system used for I/O streaming.
Error checking is in place if `read` fails.

From there, we take the contents of the buffer and `write` it in to the new file.
Pass in the file descriptor referencing the new file(`fdnew`), the buffer to write from(`c`), and the amount to be written in(`size`).

```
while(size > 0)
{
    if(-1 == write(fdnew, c, size))
    {
        perror("There was an error with write(). ");
        exit(1);
    }
    //read called again
}
```

We use `read` and `write` in a loop based on the behaviors of both system calls.
If `read` or `write` is called again using the same arguments, the system calls will continue from the last byte read or written until it reaches the end of the file or buffer, returning 0.

The amount of bytes read or written by `read` or `write` range from just 1 byte to a suggested maximum value given by the system for streaming, defined by the macro `BUFSIZ`.

The `int` is used to keep track of how much is transferred between the file descriptors and buffer, and to end the loop.

Now that the content transfer is complete, we close the related file descriptors to `fileold` and `filenew` to free up operating system resources and prevent additional changes made to these file descriptors, if any:

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
Closing file descriptors initializes their respective behaviors defined from `open`, if any.

We would find the same contents as `fileold` stored in the newly created file `filenew` within the same directory.

##Man Pages
[open](http://linux.die.net/man/2/open) <br />
[read](http://linux.die.net/man/2/read) <br />
[write](http://linux.die.net/man/2/write) <br />
[close](http://linux.die.net/man/2/close) <br />
