

#Using getpwuid, getgrgid, and getcwd
In this write-up, we will learn how use three system calls: `getpwuid`, `getgrgid`, and `getcwd`.
We will look at each of their function calls, parameters, and return values.
Let's dive in!

##getpwuid
This system call retrieves information on a user.

Here is an example of calling `getpwuid` in order to print the username of a file's owner:
```
struct stat s1;

const char* path1 = "./file1"

if(-1 == (stat(path1, s1))){
	perror("stat failed");
}

struct passwd* p1;

p1 = getpwuid(s1.st_uid);
if(p1 == NULL){
	perror("getpwuid failed");
}

std::cout << p1->pw_name << std::endl;
```
Because the `getpwuid` function requires a `uid_t uid` parameter (A user's ID), we use the `stat` system call to load `s1` of type `struct stat` with the information regarding the file specified by `path1`.
Among this information is the `uid` of the user who owns the file, which we can use as the parameter for `getpwuid`.

After error checking `stat`, we initialize `p1` of type `struct passwd*`, the same type as the return value of `getpwuid`.

We then call `getpwuid`, passing in the `uid` value in `s1` as the parameter by writing `getpwuid(s1.st_uid)`.

We then set `p1` to catch the function's return value and perform an error check.
Upon success, `p1` will be loaded with the user's information.
On failure, `p1` will have the value `NULL`.

Lastly, we print out the user's username using the variable `pw_name`,  which is one of the contents of the returned `struct passwd*` type.

To use the `getpwuid` system call, include the following headers in a program:
```
#include <sys/types.h>
#include <pwd.h>
```

###struct passwd
Being the return value type of the `getpwuid` function call, we can look at its content to see what information is given about the user:

```
struct passwd {
	char   *pw_name;       /* username */
	char   *pw_passwd;     /* user password */
	uid_t   pw_uid;        /* user ID */
	gid_t   pw_gid;        /* group ID */
	char   *pw_gecos;      /* user information */
	char   *pw_dir;        /* home directory */
	char   *pw_shell;      /* shell program */
};
```
For more information on `getpwuid`, visit the following man page:

####[man page](http://linux.die.net/man/3/getpwuid)

or enter the following command into your linux terminal to access the man page locally:
```
$ man getpwuid
```

##getgrgid
This system call is used to retrieve information about a group.
Much like the user, someone who is a part of a group can be granted certain access and permissions to files and directories that others outside the group cannot access.

Here is an example of using `getgrgid` to print out the group-name by using a file owned by that group:
```
struct stat s2;

const char* path2 = "./file2";

if(-1 == (stat(path2, s2))){
	perror("stat failed");
}

struct group* g1;

g1 = getgrgid(s2.st_gid);

if(g1 == NULL){
	perror("getgrgid failed");
}

std::cout << g1->gr_name << std::endl;
```
First we call `stat` on our chosen file, giving us a `struct stat` type that contains the `gid_t` variable (the group ID) we need to call `getgrgid`.

After error checking `stat`, we initialize `g1` of type `struct group*`, which will receive the group's information after `getgrgid` executes.

We then call `getgrgid` with the parameter `s2.st_gid`, which is the `gid_t` variable contained in `s2` that we needed.

Next, `g1` is loaded with the function's return value of type `struct group*`, which we then error check.
Upon the function's success, `g1` will be loaded with the group's information.
On failure, `g1` will have the value `NULL`.

Finally, we print out the group's name by using the `gr_name` variable found in the `struct group*` type.

To use `getgrgid`, include the following headers in a program:
```
#include <sys/types.h>
#include <grp.h>
```

###struct group
The contents of this structure show what kind of information we can retrieve on a group:
```
struct group {
	char   *gr_name;       /* group name */
	char   *gr_passwd;     /* group password */
	gid_t   gr_gid;        /* group ID */
	char  **gr_mem;        /* group members */
};
```
For more information on getgrgid, visit the following man page:

####[man page](http://linux.die.net/man/3/getgrgid)

or enter the following command into your linux terminal to access the man page locally:
```
$ man getpwuid
```
##getcwd

This system call returns the current working directory. (The pathname between the home directory and the directory containing the program)
If your program depends on moving between several directories, this system call is great for telling the user which directory they are in.

Here is an example of calling `getcwd` and printing the CWD:
```
char c[1024];
if(getcwd(c, sizeof(c)) == NULL){
	perror("getcwd failed");
}

std::cout << c << std::endl;		//print current working directory
```
First we initialize a cstring large enough to contain a pathname.
Initializing it with a size of 1024 is more than enough space.

Next we call the function for `getcwd`.
The first parameter takes in our cstring, whether or not it be empty.
The second parameter is of type 'size_t', and its value should always be that of the first parameter's size.
Using the function `sizeof()` makes this easier than inputting a number, should that number ever change.

After `getcwd` executes, our cstring used as the first parameter will contain the null-terminated pathname of the CWD.

Next we catch the function's return value of type `char*`, and perform an error check.
Upon success, the function returns the same `char*` value that is loaded into the first parameter.
On failure, the function returns the `NULL` value.

Finally, we can print the CWD by simply calling `std::cout`.

For more information on the getcwd command, consider reviewing its man page linked below:

###[man page](http://linux.die.net/man/3/getcwd)

or enter the following command into your linux terminal to access the man page locally:

```
$ man getcwd
```
