

#Using getpwuid, getgrgid, and getcwd
In this write-up, we will learn how use three system calls: `getpwuid`, `getgrgid`, and `getcwd`.
We will look at each of their function calls, parameters, and return values.
Let's dive in!

##getpwuid
This system call retrieves information on a user.

Say we want to use `getpwuid` in order to retrieve the username of a file's owner.
Here is the beginning code segment to an example of that:
```
struct stat s1;

const char* path1 = "./file1"

if(-1 == (stat(path1, s1))){
	perror("stat failed");
}
```
Because the `getpwuid` function requires a `uid_t uid` parameter (A user's ID), we use the `stat` system call to load `s1` of type `struct stat` with the information regarding the file specified by `path1`.
Among this information is the `uid` of the user who owns the file, which we can use as the parameter for `getpwuid` in the next code segment:
```
struct passwd* p1;

p1 = getpwuid(s1.st_uid);
if(p1 == NULL){
	perror("getpwuid failed");
}
```
First we initialize `struct passwd* p1`, which will receive the return value of 'getpwuid'.
We then call the `getpwuid` function, passing in the `uid` value in `s1` as the parameter by writing `getpwuid(s1.st_uid)`.

We then set `p1` to catch the function's return value and perform an error check.
Upon success, `p1` will be loaded with the user's information.
On failure, `p1` will have the value `NULL`.

We can now look at the contents of the `struct passwd` type to see what information `p1` contains on the user:

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

To print the user's username, we can simply write the following code into our program:
```
std::cout << p1->pw_name << std::endl;
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
```
Because the `getgrgid` function requires a `gid_t gid` parameter (A group ID), we use the `stat` system call to load `s2` of type `struct stat` with the information regarding the file specified by `path2`.
Among this information is the `gid` of the group who owns the file, which we can use as the parameter for `getgrgid` like so:

```
struct group* g1;

g1 = getgrgid(s2.st_gid);

if(g1 == NULL){
	perror("getgrgid failed");
}

std::cout << g1->gr_name << std::endl;
```
First, we initialize `struct group* g1`, which will receive the return value of the `getgrgid` function.
We then call `getgrgid` with the parameter `s2.st_gid`, which is the `gid_t` variable contained in `s2` that we needed.

After the function executes, `g1` is loaded with the function's return value, which we error check.
Upon the function's success, `g1` will be loaded with the group's information.
On failure, `g1` will have the value `NULL`.

We can now look at the contents of the `struct group` type to see what information `g1` has on the group:
```
struct group {
	char   *gr_name;       /* group name */
	char   *gr_passwd;     /* group password */
	gid_t   gr_gid;        /* group ID */
	char  **gr_mem;        /* group members */
};
```
We can now use any one of these variables in our program.
For example, to print the group's name we can write the following code:
```
std::cout << g1->gr_name << std::endl;
```
Or we can even print out the list of users who are a part of that group:
```
for(unsigned i = 0; g1->gr_mem[i] != NULL ; ++i){
	std::cout << g1->gr_mem[i] << std::endl;
}
```
For more information on getgrgid, visit the following man page:

####[man page](http://linux.die.net/man/3/getgrgid)

or enter the following command into your linux terminal to access the man page locally:
```
$ man getpwuid
```
##getcwd

This system call returns a string pointer containing the pathname of the current working directory (CWD).
If your program depends on moving between several directories, this system call is great for telling the user which directory they are in.

Here is an example of calling `getcwd` and printing the CWD:
```
char c[BUFSIZ];
if(getcwd(c, sizeof(c)) == NULL){
	perror("getcwd failed");
}
```
First we initialize a cstring large enough to contain a pathname.
Initializing one with the constant `BUFSIZE` is good, as it represents the maximum number of characters that can be taken into stdin at once (a large number).

Next we call the function for `getcwd`.
The first parameter takes in our cstring, whether or not it be empty.
The second parameter is of type 'size_t', and its value should always be that of the first parameter's size.
Using the function `sizeof()` with our cstring as its parameter makes this easier than inputting a number or constant, should we ever need to change the size.

After `getcwd` executes, our cstring used as the first parameter will contain the null-terminated pathname of the CWD.

Next we catch the function's return value of type `char*`, and perform an error check.
Upon success, the function returns the same `char*` value that is loaded into the first parameter.
On failure, the function returns the `NULL` value.

Finally, we can print the CWD by writing:
```
std::cout << c << std::endl;
```

For more information on the getcwd command, consider reviewing its man page linked below:

###[man page](http://linux.die.net/man/3/getcwd)

or enter the following command into your linux terminal to access the man page locally:

```
$ man getcwd
```
