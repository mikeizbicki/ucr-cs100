#chown system call

Documentation on the `chown()` system call which is used to change the ownership and group of a file.

##Inclusion
 
`#include <unistd.h>`

##Declaration

`int chown(const char *path, uid_t owner, gid_t group);`

##Return Value

`chown()` will return 0 if successfully changed owner and group of a file, and will return -1 if an error has occurred, which will set errno.

[man page](http://man7.org/linux/man-pages/man2/chown.2.html)

##Example

```
$ cat mychown.c
int main()
{
	int flag;
	flag = chown("test.txt", -1, 62);
	if (flag == -1)
		perror("mychown.c");
}
$ ls -l test.txt		
-rw-r--r-- 1 glass	music		8 June 11:42 test.txt
$./mychown
$ ls -l test.txt
-rw-r--r-- 1 glass   cs			8 June 11:43 test.txt

```

A very brief example of how chown works within actual code, but as you can see, chown runs passing in `test.txt` as its path, -1 and 62 are the owner and group respectively. Numerical IDs can be used, but in other examples  (as shown above): command line arguments, or usernames can also be used. As you can somewhat see, if the program was to be run in a terminal, you can clearly see that `music` changed to `cs` indicating that the group has changed after the command was run. So with numerical values in coding, or just simply calling chown in the terminal, ownership and group can be changed easily.

`chown` can also be used on a command line to change the owner and group.

When `ls -l` runs the first name that comes up after  `-rw-r--r-- _` is the owner and the second name is the group. The information after just relates to time and filename. If we would like to change the owner of the file from root to siddu, refer to the example below.

```
$ ls -l tmpfile
-rw-r--r-- 1 root family 0 2015-06-04 22:20 tmpfile

$ chown siddu tmpfile

$ ls -l tmpfile
-rw-r--r-- 1 siddu family  0 2015-06-04 22:21 tmpfile 
```

The ownership has changed! The ownership has changed from root to siddu after calling chown and what file it should be completed with. 

To change the group, instead of calling `chown siddu tmpfile`  we would call `chown :siddu tmpfile` and we would expect this to be the output. 

```
$ls -l tmpfile
-rw-r--r--1 root siddu 0 2015-06-04 22:21 tmpfile
```

The terminal reads whatever after the colon to be the group, and whatever is before the colon to be the owner.

If we would like to change both the owner and the group simultaneously from `root family` to `siddu friends` respectively, then observe the code below.

```
$ ls -l tmpfile
-rw-r--r-- 1 root family 0 2015-06-04 22:20 tmpfile

$ chown siddu:friends tmpfile

$ ls -l tmpfile
-rw-r--r-- 1 siddu friends 0 2015-06-04 22:21 tmpfile
```

So as you can see with the usage of the colon, you're able to change both the owner and the group as you see fit. And also numerical IDs did not need to be used in this example, showing that you can work with multiple ways to 
change the ownership of the group. 


Below is another example of `chown()` being used in the terminal to change the group of a file. Before the group of the files was named as `music` and the object is to be able to change ownership to `cs` as the group. These are preset to numerical IDs that can be set as seen fit. 
