#Chown system call

Documentation on the 'chown()' system call which is used to change ownership and group of a file.

##Inclusion
 
`#include <unistd.h>`

##Declaration

`int chown(const char *path, uid_t owner, gid_t group);`

##Return Value

chown() will return 0 if successfully changed owner and group of a file, and will return -1 if an error has occurred, which will set errno.

##Description

`chmod()` is used to change the user and group ownership of a file. In the function declaration, the `path` argument specifies the file, and the `owner` and `group` parameters contain numerical values that will symbolize the IDs of the two. The path will be changed to owner and group respectively.

##Example

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

'

The code above shows a very brief example of how chown works. As you can see, chown runs passing in 'test.txt' as its path, -1 and 62 are the owner and group respectively. Numerical IDs can be used, but in other examples command line arguments, usernames, or other identification tactics. As you can somewhat see, if the program was to be run in a terminal, you can clearly see that 'music' changed to 'cs' indicating that the ownership has changed after the command was run.
