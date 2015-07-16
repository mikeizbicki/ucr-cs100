#Retrieving file information via the Stat system call
In this write-up, we will be going over how to use the system call `stat`.
We will go over the general purpose of `stat`, followed by its function call, parameters, and return value.

##stat
`stat` is a system call that can retrieve information from a single file.


Let's say that we are working in the following set of directories `head` and `tail`,
```
head:
	main.cpp
	tail

tail:
	file1
```
writing in `main.cpp`, and want to retrieve information on `file1` with `stat`.
To do so, we can write this inside `main.cpp`:
```
struct stat s1;

const char* pathname1 = "./tail/file1";

int return = stat(pathname1, s1);
if(return == -1){
	perror("stat failed");
}
```
We initialize `struct stat s1` before calling `stat` because it will be used as a buffer to receive the file's information after `stat` executes.

Then we initialize a `const char*` with the proper pathname from the directory the program is in, to the directory `file1` is in.

We then call `stat`.
The first parameter of the function call is of type `const char*` and will lead the function to the file specified by the pathname in `pathname1`.
Next, we pass in our already initialized `s1` of type `struct stat` as the second parameter, which will receive the information on the file specified by `pathname1`.

We then catch the function's return value which is of type `int`, and perform an error check.
If the return value is 0, the function succeeded.
if it is -1, it failed.

After we have called `stat`, we can look at the contents of our `struct stat` buffer `s1` to see what information its contents provide us with:

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

####st_mode
One of the contents of the `struct stat` type and a variable of type `mode_t`, the value of `st_mode` is an octal number whose value is determined by several different permissions and properties of the file.
What we can do with this octal number is perform a bitwise AND operation with one or more available flags to determine whether that flag is true or false for our file.

Here is an example of using such an operation with two different `struct stat` types:
```
struct stat s1;
struct stat s2;

const char* path1 = "./tail";
const char* path2 = "./tail/file1";

int return1 = stat(path1, s1);
if(return1 == -1){
	perror("stat failed");
}

int return2 = stat(path2, s2);
if(return2 == -1){
	perror("stat failed");
}

int isdir1 = (s1.st_mode & S_IFDIR);
int isreg1 = (s1.st_mode & S_IFREG);

int isdir2 = (s2.st_mode & S_IFDIR);
int isreg2 = (s2.st_mode & S_IFREG);
```
First we call two instances of `stat`, one for `tail` and the other for `file1`, giving us two `struct stat` types loaded with the information on each.
Then after error checking, we grab the `st_mode` value from both `struct stat` types using `s1.st_mode` and `s2.st_mode`, and use the bitwise AND operation with the flags `S_IFDIR` and `S_IFREG`.

ANDing an `st_mode` value with the `S_IFDIR` flag will return 0 if the concerning file is not a directory.
Otherwise it will return non-zero, letting us know that the file is actually a directory.

ANDing the same value with the `S_IFREG` flag will return 0 if the concerning file is not a regular file.
Otherwise it will return non-zero, letting us know that the file is indeed a regular file.

In the case of our example, we would get the following values for our variables:
```
isdir1 != 0
isreg1 = 0

isdir2 = 0
isreg2 != 0
```
So we know from this that `file1` is indeed a regular file, and `tail` is a directory.

Below is a list of flags that are also useful, and the information they provide when ANDed with `st_mode`:

Flag	  | Information
----------|--------------------------------
`S_IFREG` | Is it a regular file?
`S_IFDIR` | Is it a directory?
`S_IRUSR` | Does the owner have read permission?
`S_IWUSR` | Does the owner have write permission?
`S_IXUSR` | Does the owner have execute permission?
`S_IRGRP` | Does the group have read permission?
`S_IWGRP` | Does the group have write permission?
`S_IXGRP` | Does the group have execute permission?
`S_IROTH` | Do others have read permission?
`S_IWOTH` | Do others have write permission?
`S_IXOTH` | Do others have execute permission?

For the best details on the remaining elements of `struct stat`, the remaining flags used with `st_mode`, as well as the entirety of using the Stat system call, consider reviewing the stat man page linked here:

#####[man page](http://linux.die.net/man/2/stat)

Or you can enter the following command from inside your linux terminal to access the page locally:
```
$ man 2 stat
```
