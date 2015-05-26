# Links
###What is This?
This is a page all about links for people who dont want to read the man pages or want examples.
###What are Links and Why Should I Care?
Without links Inode are associated with one directory entry at a time.
With links, you can access the same inode with more than one entry.
Why whould someone want to do this?
Lets say your root partition is running out of space and you really want to instsall Libre office.
You link a root folder to your home folder in another partition and install Libre Office in your home folder. 

###Whats the Difference Between Hard and Soft Links?
The main difference is soft links makes a new inode while hard links share the same inode.
Click [Here](www.youtube.com/watch?v=j_BgOf2Ti-s) to watch a video about inodes.
#Code 
Dont want to read pages of test?
Click [Here](https://www.youtube.com/watch?v=LPIMLR4simU) to watch a simplified video about the basics of links.
###Creating Links
So how whould I go about making these wonderful links?
You can make hard links simply with the ln command.
The format is 

> ln file1 link1

or

> ln /path/to/file1 /path/to/link1

Just make sure the file exists and the link does not exits.
The command creates a hard link to file1.

Soft links are exactly the same except with a '-s' flag.

> ln -s file link

or

> ln -s /path/to/file1 /path/to/link1

Soft links can link across file systems and to directories.
###Removing Links
Say you typed 'ln file1 lnik' instead of 'ln file1 link1'.
To delete links, you can use

> rm lnik

or 

> unlink lnik 

Because files are directory entries associated with a Inode, you can use unlink to delete files.
So whats the difference between the two?

```
$ touch $(seq 1 100) #makes file form 1 to 100
$ time for i in $(seq 1 100); do rm $i; done
real	0m0.151s
user	0m0.000s
sys	0m0.032s
$ touch $(seq 1 100)
$ time for i in $(seq 1 100); do unlink $i; done
real	0m0.147s
user	0m0.004s
sys	0m0.032s
```

Notice how unlink is slightly faster than rm.
That is because unlink has less fetures than rm.
unlink:
* is not recursive
* cannt remove directories
* cannt handle less than one element ie 'unlink file1 file2' will not work
* has less sanity checking

The measurements are done with a loop unlinking or removing one file at a time.
Because rm can accept more than one argument at a time it is actully faster to use rm if you know all the arguments beforehand.

```
$ touch $(seq 1 100)
$ time rm $(seq 1 100)
real	0m0.008s
user	0m0.000s
sys	0m0.004s
```

You should almost always use the `rm` command because it is better in close to everyway. 
#Flags
###--backup -b
Want to make a link but the file already exists?
Dont want to type mv?
Cant think of a name?
use `--backup` or `-b` to create a backup of a file and make a link at the same time.

>ln --backup file1 file2

If file2 exists, running the command you get `file1` `file2` and `file2~`
Dont like the naming system? 
You can use number too!

>ln --backup=numbered file1 file2

Now instead of making a backup called `file2~` its now called `file2.~1~`
Possable arguments for `--backup` is:
* none
* off
* sumple
* never
* existing
* nil
* numbered 
* t

In summary  
If file 2 exists the flag will 
* create a backup of file 2
* create a link for file1 called file2

### -d -F --directory
What if hardlinks could link to directories as well?
Well it can! (not really)
`-d` `-F` or `--directory`
lets super user create a hard link to a dir 

> ln -d dir link

It almost never works just use soft links instead

### -f
Say you want to make a link of file called file2 and oh no!
`ln: failed to create hard link ‘file2’: File exists`
Instead of typing `rm file2` an entire 8 characters type `-f` instead.
`-f` is the force flag.

> ln -f file file2

*Makes a link to file2
*If file2 exists removes file2.

### -n --no-dereference
In `ln -sfn file link`, the n flag treats link as a regular file if it is a soft link to a directory. 
Now why whould anyone want to do that?
If `link` is a soft link to `dir`, `ln` will dereference `link` to `dir` go to `dir` and use the original name as the target name.
Understand? Not really? Heres an example.

```
$ mkdir dir1 dir2
$ ln -s dir1 link
$ ls -l link
lrwxrwxrwx 1 lolipopping lolipopping 4 May 24 15:41 link -> dir1
$ln -sf dir2 link
$ ls -l link
lrwxrwxrwx 1 lolipopping lolipopping 4 May 24 15:41 link -> dir1
$ ls -l dir1
total 0
lrwxrwxrwx 1 lolipopping lolipopping 4 May 24 15:42 dir2 -> dir2
$ ln -snf dir2 link
$ ls -l link
lrwxrwxrwx 1 lolipopping lolipopping 4 May 24 15:45 link -> dir2
```

In this example, I first linked `link` to `dir1`.
When I tried to link to `dir2`, ln dereferenced link went to the original target `dir1` and used it as the link name which is why you get `dir2` inside `dir1`
Understand? Not really?
Thats fine just remember to always use `-nsf` instead of `-sf` 

### -i
`i` stands for `interactive`.
It does exactly what the `-f` flag does but it asks first.

```
$ touch f1 f2
$ ln -i f1 f2
ln: replace ‘f2’?
```

Side note if you add the `-f` flag with the `-i` flag it does not ask and just deletes. 

### -S --suffix=SUFFIX
Wow `-b` sounds really useful but I dont like how its named. 
What if I want to add .backup or .csgod to my backups instead?

> ln -S.backup f1 f2

or 

> ln --suffix=.backup f1 f2

The command makes a backup of `f2` if `f2` exists and adds whatever suffix you want.
If the file with the suffix already exists, it is over written. 

### -t --target-directory=DIRECTORY
What if I want a link in another directory?
Say I want to make a soft link of a folder form root to my home folder with the same name.

> ln -tdir1 f1

or

> ln --target-directory=dir1 f1

The command creats a link called `f1` in directory `dir1` to file `f1`

### -T --no-target-directory
Lets say you're now working at google and you want to link some filesystems togther.
You want to link to `file` called `link` but you notice theres a directory also called `link`.
Instead of creating a link called `link`, it creates a link called `file` inside the `link` directory!
To prevent this and instead print an error, you need to use the -T flag. 

> ln -T file link

or

> ln --no-target-directory

Thay way, instead of creating a link instide the directory, it prints out an error so you know to change the name of the link.

### -v --verbose
Are you making hundreds of links across your system and want to make a text file to keep track of it?
The `-v` flag has `ln` print out what its doing.

> ln -vs f1 f2

or 

> ln -s --verbose f1 f2

Not only does this create a link called f2 linking to f1, it prints out what its doing.
The output would be `'f2' -> 'f1'`.
The format is name of link created -> target of link.

