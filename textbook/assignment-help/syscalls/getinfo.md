

#Using getpwuid, getgrgid, and getcwd
In this write-up, we will learn how to properly utilize three rather important system calls: getpwuid, getgrgid, and getcwd.
We will look carefully at each of their function calls, parameters, return values, as well as example code snippets regarding them.
Let's dive in!

##getpwuid
This system call allows us to retrieve several important pieces of information regarding the user.
In order to use this system call, include the following headers in your program:
```
#include <sys/types.h>
#include <pwd.h>
```

###The getpwuid function calls
There are two simple ways to call the getpwuid function:
```
	struct passwd *getpwnam(const char *name);
```
and
```
	struct passwd *getpwuid(uid_t uid);
```
####getpwnam:
This variation of the system call takes in a `const char*` containing the name of the user we wish to gather information on, and returns a `struct passwd*` where that information can be located.
For example, if our username was something like `user001`, then we could write something like this to call getpwnam:
```
const char* name = "user001";
struct passwd *p = getpwnam(name);
```
Upon execution of this code, `struct passwd *p` would then contain the information on user001;

####getpwuid:
Probably the more useful call, this variation takes in an octal value of type `uid_t` (which can be obtained with the help of the Stat syscall) associated with a user, and then also returns a `struct passwd*` where the information on that user can be found.
Let's look at another example code, supposing we have found a way to assign our `uid_t uid` value to the variable `myUserID`:
```
struct passwd *p = getpwuid(myUserID);
```
Upon execution, `struct passwd *p` would again contain the information regarding our user ID number found in `myUserID`.

###Return Values
Both functions will return a pointer to a `struct passwd*` containing the user's information.
On failure, both functions will return a NULL value.

###The Passwd structure
As we have already gone over, after calling either getpwnam or getpwuid, the information about the user is retrieved and put into a `passwd*` structure.
Let's take a look at its contents to see what we can learn about the user:
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
Now, let's take a look at a complete example code.
First, we'll assume that we have utilized the Stat system call, and have established a stat structure named `s`.
Here's what our code might look like when we attempt to use our user ID found in `s` to print our username:
```
struct passwd *p = getpwuid(s.st_uid);	//call getpwuid
if(p == NULL){							//p = NULL if getpwuid failed
	perror("getpwuid failed");			//perform error checking
}

std::cout << p->pw_name << std::endl;	//print username
```
And with this, we have successfully printed out our username.
This method is especially helpful for printing the username's of anyone else who might use your program on their own computer!

For more information on getpwuid and getpwnam, visit the following man page:

####[man page](http://linux.die.net/man/3/getpwuid)

or enter the following command into your linux terminal to access the man page locally:
```
$ man getpwuid
```

##getgrgid
This function call is useful when we want to retrieve information regarding a group.
Much like the user, someone who is a part of a group can be granted certain access and permissions to files and directories that others outside the group cannot access.
In order to use this system call, include the following headers in your program:
```
#include <sys/types.h>
#include <grp.h>
```

###the getgrgid function call
Though there are a few ways to use this system call, here we will focus on only the one that is the most simple in its execution.
Here is the synopsis of the call:
```
struct group *getgrgid(gid_t gid);
```
The only parameter, `gid_t gid`, is an octal variable whose value is a group ID number.

###Return Value
Upon success, getgrgid returns a pointer to a `struct group`.
Other wise, the function returns the NULL value.

###the Group structure
So what kind of information does the returned `struct group*` contain?
Let's take a look at the structure's contents below.
The purpose of each element should be self explanatory:
```
struct group {
	char   *gr_name;       /* group name */
	char   *gr_passwd;     /* group password */
	gid_t   gr_gid;        /* group ID */
	char  **gr_mem;        /* group members */
};
```
Now that we have gone over how to call the getgrgid function and have learned about what it returns, let's look at an example of using it to print our group's name.
Using the stat syscall, we can harness a file's associated group ID, and use that value in our call to getgrgid.
Below is an example of such a program, where our stat call has helped us establish a stat structure named `s`:
```
struct group *g = getgrgid(s.st_gid);	//call getgrgid
if(g == NULL){							//g = NULL if getgrgid failed
	perror("getgrgid failed");			//perform error checking
}

std::cout << g->gr_name;				//print group name
```
This code will effectively print out the name of the group associated with the `st_gid` value taken from `s`.

For more information on getgrgid, visit the following man page:

####[man page](http://linux.die.net/man/3/getgrgid)

or enter the following command into your linux terminal to access the man page locally:
```
$ man getpwuid
```
##getcwd

The system call getcwd allows us to retrieve the current working directory (CWD).
You may recall that the CWD can vary depending on what directory you are currently working in.
The same rule applies to the getcwd system call.
When its function is called, the CWD is the path between the home directory and the directory where the program was executed.
This can be a useful piece of information when your program depends on moving between different directories.

In order to utilize this system call, include the following header in your program:

```
#include <unistd.h>
```

###The getcwd function call
There are a few ways to use this sytem call, but for now we will only be going over the one that is the most simple in its execution.
Here is a synopsis of that call:
```
char *getcwd(char *buf, size_t size);
```
The parameter `char *buf` is a char array that should already have an established size.
Because this char array will contain the CWD as a cstring after the function executes, its size should be one that is large enough to contain the entire CWD.
A size of 1024 is more than enough.

The parameter `size_t size` is a variable with a numerical value that should always be that of the size of the `char *buf` parameter.
So if our char array was indeed one of size 1024, then we should also pass in the `size` parameter as the value 1024.

###Return Value
Upon success, getcwd will return a null terminated char array containing the CWD.
Also take care to remember that the `char *` returned has the same value as that of the `char *buf` parameter after execution.
Upon failure, the function will return NULL.

Let's look at a simple example where we want to print out our current working directory:
```
char c[1024];						//create char*
if(getcwd(c, sizeof(c)) == NULL){	//execute getcwd
	perror("getcwd failed");		//perform error check
}

std::cout << c << std::endl;		//print current working directory
```

For more information on the getcwd command, consider reviewing its man page linked below:

###[man page](http://linux.die.net/man/3/getcwd)

or enter the following command into your linux terminal to access the man page locally:

```
$ man getcwd
```







