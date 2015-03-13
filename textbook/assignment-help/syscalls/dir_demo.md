#Demonstration: Obtaining Information on Directories

This file contains a piece of code that demonstrates how to open a directory, print the name of each file in the directory, and then close said directory upon reaching its end. The code utilizes the system calls `opendir`, `readdir`, and `closedir`, as well as several streams and structs unique to these system calls, directories, and their contents. The code without any commentary is shown below, with follow-up snippets of code to explain the process and system calls used in relation with the code.

##Code

```
DIR *dirp;
if(NULL == (dirp = opendir(dirName)))
{
	perror("There was an error with opendir(). ");
	exit(1);
}
struct dirent *filespecs;
int errcheck;
while(filespecs = readdir(dirp))
{
	errcheck = errno;
	if(errcheck == -1)
	{
		perror("There was an error with readir(). ");
		break;
	}
	cout << filespecs->d_name << " ";
}
cout << endl;

if(-1 == closedir(dirp))
{
	perror("There was an error with closedir(). ");
	exit(1);
}
```

##Explanation

We begin by first allocating some memory that will be utilized with all three system calls used in this demo: the `DIR` data type. It acts as a stream to the contents of any directory passed into `opendir`, which we call next. Note that the call to `opendir` will only succeed and fill the `DIR` stream if a valid directory is passed in as its sole argument, otherwise it will return the `NULL` value to the stream. The "failed" state of the `DIR` stream is a factor we can use for error checking.

```
DIR *dirp; //Allocate data for the directory stream
if(NULL == (dirp = opendir(dirName))) //Opendir will place the contents of dirName into the dirp stream or NULL if dirName is invalid
{
	perror("There was an error with opendir(). ");
	exit(1); //Permission to directory denied, wrong directory name, not a directory
}
```

Now that we have the `DIR` stream `dirp` filled, we can use the system call `readdir` on it to extract individual file information from it. While `readdir` uses the stream as an argument, it returns a pointer to another data structure that holds the information of a specific file within the directory. We must allocate memory of the `struct dirent` to access the info that `readdir` will return.

```
struct dirent *filespecs; //Allocate data for the dirent struct for readdir
int errcheck; //Error value for error checking
while(filespecs = readdir(dirp)) //readdir will overwrite the previous directory entry with the next entry until the end of the directory
{
	errcheck = errno; 
	if(errcheck == -1)
	{
		perror("There was an error with readdir(). ");
		break; //Reached end of directory or invalid directory stream
	}
	cout << filespecs->d_name << " "; //Access file specifics here, such as printing out the file-name
}
cout << endl;
```

In this moment of the code, we use a loop to repeatedly call `readdir` due to the way `readdir` is built. If called onto the same structure and with the same directory, `readdir` will overwrite what would be in `filespecs` with the next file in the directory until it exhausts the stream, returning a `NULL` to indicate the end of a directory. We use the `errno` value to track when `readdir` ends, but there are certainly other ways to cover a stream with `readdir`.

As `filespecs` is a struct, it contains its own values that `readdir` will update according to the file that is currently passed into `readdir` on the `DIR` stream The attributes of the struct include:

```
struct dirent
{
	ino_t			d_ino;		 /* inode number*/
	off_t			d_off;		 /* not an offset; see NOTES */
	unsigned short	d_reclen;	 /* length of this record */
	unsigned char	d_type;		 /* type of file; not supported
								    by all filesystem types */
	char			d_name[256]; /* filename */

}
```

When within the `readdir` loop, it is possible to do far more with the struct values than just printing the file-name out. You can save wanted attributes to other data structures like vectors, and use them in conjunction with other system calls like `stat` to access even more specifics about the file itself.

When we are done looking through a directory, it is always good practice to close the directory to return and conserve precious memory. Closing a directory uses `closedir`, and is relatively simple as it takes in the `DIR` stream, and returns a value to indicate whether it succeeded or not.

```
if(-1 == closedir(dirp)) //Close the DIR stream when we're finished
{
	perror("There was an error with closedir(). ");
	exit(1);
}
```

##Follow-Up

This demonstration only covers the use of the `opendir`, `readdir`, and `closedir` system calls to access and search through a directory. Further documentation can be found here:
* [System Calls related to Obtaining Information on Directories](./dir.md)

