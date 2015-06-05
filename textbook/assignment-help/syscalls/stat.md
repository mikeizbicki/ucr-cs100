#Retrieving file information via the Stat system call
In this write-up, we will be going over how to utilize the system call Stat.
We will go over the general purpose of Stat, followed by its function calls, their parameters, and return values.
There will also be a number of example code snippets demonstrating how to use them.
##What is stat?

Let us start by understanding the general purpose of the Stat system call.
As we know, one of the many wonderful "doo-dads" of the Linux Terminal is that it allows us to operate within a directory.
Inside of such a directory there can exist all sorts of different files; and sometimes we will want to access certain specific information about one (or more) of those files from inside a program of ours.
With the Stat system call, we can perform exactly that kind of information retrieval and harness it for use inside of our program!

To utilize the Stat syscall, include these headers in your program:
```
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
```

##The stat and fstat functions

There are two useful ways to perform the Stat system call:
```
	int stat(const char* path, struct stat *buf);
```
and
```
	int fstat(int fd, struct stat *buf);
```
The difference between the two lies in the first parameter of their respective function calls.
Now let's take a look at these function calls, and the role each parameter plays in them.

####const char* path
This parameter is a constant char array that tells the function which file to retrieve information from.
It is important however to recognize how this parameter is handled.
In an effort to ease the explanation, let's look at an example of two directories `head` and `tail` whose contents are as such:
```
head:
	main.cpp
	file1
	tail

tail:
	file2
```
Let's imagine that `main.cpp` is utilizing the `stat` syscall and we want to retrieve information on `file1` and `file2`.
To access information on `file1`, our function call inside main.cpp  might look something like this:
```
int return = stat("file1", s); //ignore the "s" for now
```
And this would work!
It would effectively retrieve the information on `file1`.

Now let's imagine that we tried something similar when trying to access the information in `file2`, and wrote this:
```
int return = stat("file2", s);
```
It doesn't work however!!!
Why?
Well, if we look back at the two directories, we can see that `main.cpp` is contained in `head`, while `file2` is contained in `tail`.
Our pathname was incorrect!
Our call worked for `file1` because the parameter `"file1"` is an acceptable pathname for a file that exists in the same directory as the program.
But because `file2` exists in a different directory, we need to modify our pathname accordingly to lead the function to our file.
Changing our call to this should do fine:
```
int return = stat("./tail/file2", s)
```
AND VOILA!!
Our program that exists inside the directory `head` has successfully retrieved information from a file that exists in another directory! 
Always remember that it is imperative that you take into account the pathname you are passing into the function call.

####int fd
This parameter is much more simple.
It is a file descriptor, or more specifically, a non-negative integer used to access a file.
But of course our program doesn't automatically have a file descriptor for every file on our computer.
No.
But we can create a new file descriptor using another syscall such as Open, whose function call looks like this:
```
int fd = open("file1", flags);
```
We won't be going into any details about the Open system call here.
All we need to know is that we can pass in a pathname just like our previous example, and Open will return a file descriptor specific to that file linked by the pathname.
From there it is only a matter of calling the fstat function properly:
```
int return = fstat(fd, s);
```
####struct stat *buf
Now that we've gone over how to tell the function which file's information we want to access, you may be wondering where we then go to access its info.
Well that role is played by this parameter.
By initializing our own empty stat structure, we can pass it as the function's second parameter, where it will then contain all of the information regarding our chosen file after the function executes!
Here is an example of what that code might look like:
```
struct stat s;

int return = stat("file1",s);
```
With this, after stat executes, s will contain all the information of `file1`.
It is as simple as that!!!

##The Return Value
With the parameters out of the way, we turn to the return value.
Looking at the `stat` and `fstat` function calls, we see that both return an integer value.
Like most system calls that return an integer, the return value will be -1 upon error, and 0 upon success.


##The Stat structure

So exactly what kind of file information does Stat give us?
To find out, we can take a look at the stat structure and its elements:

```
struct stat{
	t_dev;    			  /* ID of device containing file */
	no_t	  st_ino;     /* inode number */
	mode_t    st_mode;    /* protection 
	nlink_t   st_nlink;   /* number of hard links */
	uid_t     st_uid;     /* user ID of owner */
	gid_t     st_gid;     /* group ID of owner */
	dev_t     st_rdev;    /* device ID (if special file) */
	off_t     st_size;    /* total size, in bytes */
	blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	time_t    st_atime;   /* time of last access */
	time_t    st_mtime;   /* time of last modification */
	time_t    st_ctime;   /* time of last status change */
};
```
`st_mode` is probably the most complex stat element, at least in terms of understanding how to utilize it.
For that reason, this will be the only element of the stat structure we will go over.
####st_mode
An element of type `mode_t`, the value of `st_mode` is an octal number whose value is determined by several different permissions and properties of the file.
What we can do with this octal number is perform a bitwise AND operation with one or more flags to determine whether that flag is true or false for our file.
Because we are dealing with octal numbers, if the value 0 is returned after performing the bitwise AND operation, it means that the result is false.
Otherwise, the result is true.
Let's take a look at an example.
Going back to our previous example directory, `head`, let's imagine that `main.cpp` now contains something like this:
```
struct stat s1;
struct stat s2;

int return1 = stat("file1", s1);     //retrieve information from file: file1
int return2 = stat("tail", s2);	  	 //retrieve information from directory: tail

int isdir1 = (s1.st_mode & S_IFDIR); //S_IFDIR checks if "file1" is a directory
int isreg1 = (s1.st_mode & S_IFREG); //S_IFREG checks if "file1" is a file

int isdir2 = (s2.st_mode & S_IFDIR); //S_IFDIR checks if "tail" is a directory
int isreg2 = (s2.st_mode & S_IFREG); //S_IFREG checks if "tail" is a file
```
As you can probably tell, we are trying to determine whether `file1` and `tail` are directories or regular files.
After execution, we would discover the following values for our variables:
```
isdir1 = 0
isreg1 != 0

isdir2 != 0
isreg2 = 0
```
So we know from this that `file1` is indeed a regular file, and `tail` is a directory.
This is just one of the many convenient flags available to use with `st_mode`!

Below is a list of flags that are also useful, and the information they provide when ANDed with `st_mode`:

Flag	  | Information
----------|--------------------------------
`S_IFREG` | Is it a regular file
`S_IFDIR` | Is it a directory
`S_IRUSR` | Does the owner have read permission
`S_IWUSR` | Does the owner have write permission
`S_IXUSR` | Does the owner have execute permission
`S_IRGRP` | Does the group have read permission
`S_IWGRP` | Does the group have write permission
`S_IXGRP` | Does the group have execute permission
`S_IROTH` | Do others have read permission
`S_IWOTH` | Do others have write permission
`S_IXOTH` | Do others have execute permission

####Other elements of stat

Besides `st_mode`, the purpose of each element will not be touched upon here as they are more straightforward with their use.
For the best details on the remaining elements, as well as the entirety of using the Stat system call, consider reviewing the stat man page linked here:

#####[man page](http://linux.die.net/man/2/stat)

Or you can enter the following command from inside your linux terminal to access the page locally:
```
$ man 2 stat
```
