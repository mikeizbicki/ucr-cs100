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

###Description
The call creates a link, known as a hard link, to an existing file.

This system call is useful for transferring data from one file to next such as in the case of `mv`. 

If the command is called by `mv file1 file2` and file2 does not exist, then file1 is simply renamed file2.

This is achieved through the link call. The pointer newpath is equated to oldpath signifying that they both point to the same file. Oldpath is then deallocated to free space, and thus the file1 name, resulting in renaming of file1 without altering its contents at all.

Unlink is used as the opposite operation of link. 

The path passed to unlink will be broken from the file, similar to deallocating a standard pointer (paths are essentially pointers). 

In the case of mv, unlink is used last to sever the link between olpath and the file, which completes the renaming or physical move of the file.

####Example
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

After this, link is called on the variables storing the paths. This links the new name to the original file1, essentially renaming it. Last, unlink is called to remove the original name and finish the operation.

##SymLink
Symbolic link creates a soft link between paths. The operation is similar tolink but has inverse behavior. 

If the file is moved, the link does not follow, rather it remains pointing at the path it was declared to point at. 

If the a new file is created with the same name, the link will change to point to the new file.

###Inclusion and Return Values
Identical to link

###Declaration
`int symlink(const char* oldpath, const char* newpath);`

The operation and handling of symlink are all identical to link but the function after varies as stated above
