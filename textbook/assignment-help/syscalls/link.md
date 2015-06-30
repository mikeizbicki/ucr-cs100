#Links
Documentation on linking. These are two calls, link and unlink that are very useful in moving and connecting files. 

##Link and Unlink
###Inclusion
`#include <unistd.h>`

###Declaration
`int link(const char* oldpath, const char* newpath);`

`int unlink(const char* path);`

###Return
Zero is returned upon success. -1 is returned in the occurence of an error and errno is set properly

###Example
This system call is useful for linking data from one file to another such as in the case of `mv`. 

If the command is called by `mv file1 file2` and file2 does not exist, then file1 is simply renamed file2.

Link connects to the paths by a hard link, essentially having two pointers point to the same data.

In the case of mv, unlink is used to remove the link between olpath and the file, which completes the renaming and/or physical move of the file.

```
if(argc != 3)
{
	cout << "Invalid argument count\n";
	exit(1);
}

int sz = sizeof(argv[1]);
char here[] = "./";								// Current directory string
char* path;
path = argv[1];
char* curr = here;
for(unsigned int i = 0; i < sizeof(path); ++i)	// Creates path
	curr[i+2] = path[i];
curr[i+2] = '\0';

int sz = sizeof(argv[2]);
path = argv[2];
char* fresh = here;
for(unsigned int i = 0; i < sizeof(path): ++i)
	fresh[i+2] = path[i];
fresh[i+2] = '\0';
```
The example here takes three command line arguments, outputting an error if more or less are given, and stores the second and third as the paths. The arguments are the executable, as always, file1, which is being moved, and file2 name.

This version only handles the case when file2 does not exist, meaning file1 will be renamed.

First, the arguments must form file paths. To accomplish this you can prepend `./` to both arguments. The paths are either in the current directory or a parent/child directory of the current directory so placing the `./` is valid and does not adversely alter the created paths. 

`./file1` file is in current directory

`./tests/file1` file is in child directory from current directory

`./../examples/file1` file is in parent directory of current directory which is accessed by `../` so `./` has no effect

```
if(link(curr, fresh) == -1)		// Calls and error checking
{
	perror("link");
	exit(1);
}
if(unlink(curr) == -1)
{
	perror("unlink");
	exit(1);
}
```

Once `./` is added before the arguments, the paths are obtained.

Link is called on the paths to form the link between them, linking the original file to the new path (name).

```
if(unlink(curr) == -1)
{
	perror("unlink");
	exit(1);
}
```

Last, unlink is called to remove the connection of the old path and the file, finishing the operation.
