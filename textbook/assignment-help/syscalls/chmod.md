#Chmod System Call

Documentation on the 'chmod()' system call which is used to change the mode and/or permissions of a file.

##Chmod

[man page - chmod] (http://man7.org/linux/man-pages/man2/chmod.2.html)

##Inclusion

`#include <sys/types.h>`
`#include <sys/stat.h>`

##Declaration

`int chmod(const char *path, mode_t mode);`

##Return Value

Upon successful completion that the file has been changed, then a 0 is returned. Other wise -1 is returned and 'errno' is set to find the specific erro and no change to the file mode has occured.

##Description

###Parameters
chmod() is used to change S_ISUID, S_ISGID, S_ISVTX, and other file permission bits that have been named by a pathname, `path`, to the corresponding bits in the `mode` parameter. 

###Permissions
The file permission bits that are changed are defined in `sys/stat.h`

1. S_ISUID - A set-user ID on an execute bit, on 04000 usually.
2. S_ISGID - Similar to S_ISUID but on 02000 usually. Takes a new file group from parent directory.
3. S_ISVTX - A sticky bit, usually 01000 that gives permission to delete a file in that directory only if the file is one that you own. If this is set to a non-directory file, the behavior will be unspecified. 
 
Many other permission bits can be used with this function, but it all varies on what specifically needs to be done. For example, setting read, write, exexecute permissions all have different permissions to be passed in. (S_IRUSR, S_IWUSR, S_IXUSR)

##Examples

In the example below, we will see how chmod() can be used to change permissions for the user, group, and others.

```
#include <sys/stat.h>

int main()
{
	const char *path;`
	*/Insert code here/*`

	chmod(path, S_IRUSR | S_IRGRP | S_IROTH);`
}
```

As you can see, 3 different permissions are passed in. `S_IRUSR` is the read permission for the owner. `S_IRGRP` is the read permission for the group, and `S_IROTH` is the read permission for others. The permissions are split up by the `|` command, so thus any one of these permissions can be passed through giving permissions to the owner, group, and others.
If say for example, the `S_IRGRP` permission was removed, the above code would only give read permissions to the user and the others. Starting to get how this works? 


Different permissions can be given for different purposes. A list of permissions can be give multiple types of permissions. In the example below, we can see an instance of how multiple permissions can be given with only one parameter passed through.
```
#include <sys/stat.h> 

int main()
{
	const char *path;
	*/insert code here*/

	chmod(path, S_IRWXU);
}
```

If read, write, and execute permissions for the owner only is what you would like to do, then it would be the same code listed above but with S_IRWXU passed in. As you can see, the above code essentially gives all these permissions to the user only.  

Within the same example, if instead of `S_IRWXU` being passed in, if `S_IXUSR` gives execute and search permissions to the owner. 

So as you can see, `chmod()` provides to be very beneficial if permissions ever need to be given or taken away for any reason. 

You can find a list of permissions here depending on what you would need to change. Take the time to look through and see what specifically needs to be done!


[List of permissions](www.delorie.com/gnu/docs/glibc/libc_288.html)
