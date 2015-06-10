#Chown system call

Documentation on the `chown()` system call which is used to change ownership and group of a file.

##Inclusion
 
`#include <unistd.h>`

##Declaration

`int chown(const char *path, uid_t owner, gid_t group);`

##Return Value

`chown()` will return 0 if successfully changed owner and group of a file, and will return -1 if an error has occurred, which
will set errno.

##Description

`chown()` is used to change the user and group ownership of a file. In the function declaration, the `path` argument 
specifies the file, and the `owner` and `group` parameters contain numerical values that will symbolize the IDs of the two. 
The path will be changed to owner and group respectively.

##Example

So if you would like to change the owner of a file, know a few things. When `ls -l` runs the first name that comes up after 
`-rw-r--r-- _` is the owner and the second is the group. The information after just relates to time and filename. So say I 
would like to change the owner of the file from root to siddu. How would I go about that? Observe the code below.
```
$ ls -l tmpfile
-rw-r--r-- 1 root family 0 2015-06-04 22:20 tmpfile

$ chown siddu tmpfile

$ ls -l tmpfile
-rw-r--r-- 1 siddu family  0 2015-06-04 22:21 tmpfile 
```

The ownership has changed! Simple, right? Well the ownership has changed from root to sidd after calling chown and calling 
what file it should be completed with. So how would you change the group? Well if instead of calling `chown siddu tmpfile` I 
called `chown :siddu tmpfile` the output would be as follows.

```
$ls -l tmpfile
-rw-r--r--1 root siddu 0 2015-06-04 22:21 tmpfile
```

Notice the difference? If you want to change the group, you simply need to add a colon before hand in order to change the 
group. 

What about changing the owner and group at the same time? If in the terminal and you have the idea to change both the owner 
and the group from `root family` to `siddu:friends` then observe the code below.

```
$ ls -l tmpfile
-rw-r--r-- 1 root family 0 2015-06-04 22:20 tmpfile

$ chown siddu:friends tmpfile

$ ls -l tmpfile
-rw-r--r-- 1 siddu friends 0 2015-06-04 22:21 tmpfile
```

So as you can see with the usage of the colon, you're able to change both the owner and the group as you see fit. And also 
you can observe, numerical IDs did not need to be used in this example, showing that you can work with multiple ways to 
change the ownership of the group. 


Below is another example of `chown()` being used in the terminal to change the group of a file. Before the group of the files
was named as `music` and the object is to be able to change ownership to `cs` as the group. These are preset to numerical IDs
that can be set as you see fit. 

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

A very brief example of how chown works, but as you can see, chown runs passing in 'test.txt' as its path, -1 and 62 are the 
owner and group respectively. Numerical IDs can be used, but in other examples command line arguments, or usernames can also 
be used. As you can somewhat see, if the program was to be run in a terminal, you can clearly see that `music` changed to 
`cs` indicating that the group has changed after the command was run. So with numerical values in coding, or just simply 
calling chown in the terminal, you're allowed to change ownership as you see fit.


