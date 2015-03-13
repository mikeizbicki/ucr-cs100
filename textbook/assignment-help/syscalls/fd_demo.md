#Demonstration: Manipulating File Descriptors

This file contains a block of code that demonstrates how to use file descriptors to take the contents of a 27-byte sized file `fileold` and place them in a new file `filenew` of the same byte size. The code utilizes the system calls `open`, `read`, `write`, and `close`, as well as file descriptors and buffers that the above system calls manipulate. The source code without any comments is shown below. Explanations paired with code snippets will follow below to piece the process all together.

##Source Code

Assume we have `fileold`, which holds the contents:
```
this file is 27-bytes long.
```

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
char c[27];
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

If we wish to place the message within `fileold` into a new file, we must first allocate memory for a file descriptor. File descriptors are data structures similar to buffers represented by an integer value. To store a file descriptor, we must set an integer variable for it, and call the `open` system call to generate the file descriptor to the variable. By default, the `open` system call will set the file descriptor value to the lowest possible descriptor value available. We must also create a file descriptor for the old file to mesh with the system calls throughout the process.

```
int fdnew; //Stores the file descriptor, an integer-based reference to a file
if(-1 == (fdnew = open("filenew", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR))) //Parameters and flags dictate what open will set how the file descriptor will react
{
	perror("There was an error with open(). ");
	exit(1); //Not enough shared memory to allocate file descriptor
}

int fdold;
if(-1 == (fdold = open("fileold", O_RDONLY))) //Sets file descriptor to old file
{
	perror("There was an error with open(). ");
	exit(1);
}
```

`open` can take in 3 arguments; the file-name of the file descriptor is referencing to, the flags, and the modes that will determine the end-behavior of the file descriptor. The name passed in can be one that exists or not, depending on the flags and modes. The flags and modes are all octal values that have been conveniently defined into macros from the associated `open` libraries. These octal values are able to be appended together with the `|` bitwise operator.

The flags `O_WRONLY | O_CREAT` tells `open` to ask the system for write permissions to create a file called `filenew`. The flag `ORDONLY` tells `open` to ask the system only for read permissions to the existing file `fileold`.

The modes `S_IRUSR | S_IWUSR` define the permissions to the created file as read-able and write-able by the user.

Once we have created the file descriptors, we can place the contents of `oldfile` into a buffer using `read`. From there, we take the contents of the buffer and `write` it in to the file descriptor referencing the new file. We will use a separate buffer and an integer to keep track of the transferred content across both files.

```
int size;
char c[27]; //Sets the buffer equal to the size of `fileold`.
if(-1 == (size = read(fdold, c, sizeof(c)))) //This function will set size to the value 27 for the number of bytes read was equal to the array c, which was 27
{
	perror("There was an error with read(). ");
	exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value
}
while(size > 0) //Loop to run read for situations where read does not read the entirety of a file
{
	if(-1 == write(fdnew, c, size)) //Writes to the new file the contents of the old file
	{
		perror("There was an error with write(). ");
		exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte size
	}
	if(-1 == (size = read(fdold, c, sizeof(c)))) //Calls read again to update size and continue passing in the amount of bytes equal to the array's size from the old file if any
	{
		perror("There was an error with read(). ");
		exit(1); //Invalid file descriptor or permissions, invalid buffer, or invalid byte value
	}
}
```

The `read` system call takes 3 arguments: the file descriptor to obtain data from, the buffer to send that data to, and how many bytes of data should be sent to the buffer. The amount of bytes that can be read range from just 1 byte to a recommend value given through the system, defined by the macro `BUFSIZ`.

The `write` system call also takes 3 arguments: the file descriptor to write data to, the buffer to parse the data from, and the amount of content through bytes to be passed onto the file descriptor. The amount of bytes written range from just 1 byte to a recommended value given through the system, defined by the macro `BUFSIZ`.

The usage of `read` and `write` exist in a loop due to how the `read` system call works. If `read` is called again with the same file descriptor and buffer to read to, the system call will simply pick up where it left off and read up to the amount of bytes given plus the amount of bytes previously given into the buffer. The loop acts as a way to continuously read through a file, as `read` will only return `0` or a negative value upon reaching the end of a file or an error. `write` also behaves in a similar way, with subsequent calls of `write` appending and not overwriting what was already written to the file descriptor from `read`.

Once the loop ends, it is good practice to close the related file descriptors to `fileold` and `filenew`: `fdold`, and `fdnew`. Closing file descriptors frees up memory and also prevents unexpected behavior occurring to any files associated with file descriptors. Closing file descriptors also finalize any changes made to file descriptors before being made into a new file by the aftereffects of the `open` system call.

```
if(-1 == close(fdnew)) //Close file descriptor to create the file
{
	perror("There was an error with close(). ");
	exit(1);
}

if(-1 == close(fdold)) //close file descriptor to conserve memory
{
	perror("There was an error with close(). ");
	exit(1);
}
```

If we were to check the same directory of this code, we would find a new file `filenew` with the message "`this file is 27-bytes long.`" contained within. This is the same message that was in `fileold`.

##Follow-Up

This demonstration only covers the use of `open`, `read`, `write`, and `close` system calls to create file descriptors that will result in a new file. Further documentation can be found here:
* [System calls related to changing file descriptors](./fd.md)
