#System calls pertaining to getting information about a process

This document is for system calls that are used to get information about a process, or an environment variable. The system calls described here will be `getcwd`, `getpwuid`, and `getgrgid`.

##getcwd:

**includes:** `#include <unistd.h>`

**declaration:** `char *getcwd(char *buf, size_t size);`

**returns:** When successful, the function returns a pointer to a `string` containing the pathname of the current working directory. On error, it returns `NULL`.

[man page](http://linux.die.net/man/3/getcwd)

As stated above, getcwd gets the c-string containing the current working directory. It inserts the c-string into `buf` to be used later. The parameter size is the length of the `char*` you pass in as the first parameters. For example, if you created `char directory[250]`, you’d pass in `directory, 250`.

Notes: This function is useful when implementing bash commands such as `cd`, and you need to display the current working directory the user is in.

Here is a quick example of `getcwd` in action:
```
char buf[1024];
if(!getcwd(buf,1024))
   perror(“problem with getcwd.”);
```

`buf` now contains the path to the current directory you're in, you can output it before your command line prompt to simulate the real bash shell. When you create your own bash shell you will have to implement `cd` with `getcwd` instead of using `exec`.

##getpwuid:
**includes:** `#include <pwd.h>`
          `#include <sys/types.h>`

**declaraton:** `struct passwd *getpwuid(uid_t uid);`

**returns:** If an error occurs `NULL` is returned, otherwise it returns a pointer to a `passwd struct` (seen below)

[man page](http://linux.die.net/man/3/getpwuid)

Notes: As you can probably see, `getpwuid` is a bit different from the other syscalls previously mentioned. It takes in the user’s ID, which is in a numerical form. After that, it will return a pointer to a structure, which contains these fields:
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

The main purpose of this function is to assist in finding info about the user, and their info. This is particularly useful when implementing things such as `ls` (an assignment in cs-100), and is necessary to implement the `-l` flag for `ls`.

Here’s a quick implementation of `getpwuid`, where `s` is a `stat struct`:
```
struct passwd *pw;
if(!(pw = getpwuid(s.st_uid)))
   perror("there was an error in getpwuid. ");
```

##getgrgid:

**includes:** `#include <sys/types.h>`
          `#include <grp.h>`

**declaraton:** `struct group *getgrgid(gid_t gid);`

**returns:** If an error occurs `NULL` is returned, otherwise it returns a pointer to a `group struct`

[man page](http://linux.die.net/man/3/getgrgid)

Much like `getpwuid`, `getgrgid` also returns a pointer to a structure, which contains these fields:
```
struct group {
    char   *gr_name;       /* group name */
    char   *gr_passwd;     /* group password */
    gid_t   gr_gid;        /* group ID */
    char  **gr_mem;        /* group members */
};
```

The main purpose of this function is to assist in finding info about the group and its info, and much like `getpwuid`, is particularly useful  when implementing things such as `ls` (an assignment in cs-100), and is necessary to implement the `-l` flag for `ls`.

Here’s a quick implementation of `getgrgid`, where s is a `stat struct`:
```
struct group *gp;
if(!(gp = getgrgid(s.st_gid)))
   perror("there was an error in getgrgid. ");
```

