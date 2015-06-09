# Links
###What are Links and Why Should I Care?
Links are a simple way to map two or more filenames to the same inode.
Without links Inode are associated with one directory entry at a time.
With links, you can access the same inode with more than one entry.
Why would someone want to do this?
It allows organization of the filesystem in amazing ways.
#Inodes
###What are Inodes?
Inodes or index nodes are a file structure of a file system. 
Inodes represent a file system object - either a file or directory.
Files are not directly linked to data blocks.
Instead they link to inodes.
Every unix system uses inodes except Solaris.
These inodes contain information about the corresponding file such as:

* mode/permissions
* owner id/group id 
* size of file
* number of hard links to the file
* time last accessed and modified
* the time the inode was last modified
* the data block number
* the inode number

Inodes are around 128 bytes of data.
###Example
![Alt text](pictures/inode_ex.jpg?raw=true)
In this picture, you can see `foo.txt` is a file with the inode number 1234 linking to the datablock containing hello world.
There is also a directory cs100 with the inode number 2345 linking to a datablock contaning `bar.txt`
#Data Blocks
Data blocks in unix are usually 1024, 2048, or 4096 bytes.
As you can see, data blocks stores data.
If you want to store data less than or equal to 1024 bytes, it takes up one block.
The amount of blocks it takes up is the amount of data you want to store divided by 1024 bytes rounded to the nearest block.
If you want to store 1025 bytes, you want to use 2 blocks.
###Fragmentation
Storing data in block can cause fragmentation. 
![Alt test](pictures/frag_1.jpg?raw=true)
As you can see there is a green file, a blue file and a red file. Now the user wants to delete the blue file and store a pink file

![Alt test](pictures/frag_2.jpg?raw=true)
The pink file takes up more than one block so it stores the data 
in the space of the deleted blue block. A pink block is stored but there is not enough room so the system appends the rest of the blocks at the end,
This process is known as fragmentation.
With a revolving platter hard drive, the magnetic needle needs to move to the place where the block is stored. In return, this causes slow data transfer eventually leading to fragmentation.

![Alt test](pictures/frag_3.jpg?raw=true)
To fix this problem, the system regularly defragments the grouping of data blocks of the same files together in order to speed up the reading.
Since Solid State Drives don't have moving parts, you do not need to defrag them.

#Practical Uses
So now that you have this knowledge how can you use it?
###Restoring Deleted Files on ext2 ext3
Because the `rm` command does not overwrite any data and just deletes the node, 
we can restore data deleted.
=======
###Restoring deleted files
Since the `rm` command does not overwrite any data and just deletes the node, 
we have the ability to restore the data deleted.

First we create a test file called `file.txt` by using the command echo and output redirection.
Then we use the `-i` flag with ls to get the inode number.

```
$ echo 'hiii' > file.txt
$ ls -i file.txt
4590386 file.txt
$ rm file.txt
```

Now we use the `debugfs` to get the information we need to restore the file. 

If your file is located on `/dev/sda2` use

```
sudo debugfs -w /dev/sda2
```
`/dev/sda2` is the unix way of naming filesystems much like the `C:` on Windows.
`/dev/` contains the device files and `sda2` is the second partition on the first drive.

If your file is located in the file system `/home`, use `/dev/mapper/SysVolGroup-LogVolRoot`

```
sudo debugfs -w /dev/mapper/SysVolGroup-LogVolRoot
```
If you didn't get a chance to run `ls -i` you can find the inode number with `lsdel`.

Now run

```
logdump -i <4590386>
```

A lot of output will appear but we are only interested on the line 
`Blocks: (0+1): 7559168`

```
inode is at 4590386 group 230, block 7536642, offset 896
Journal starts at block 10875, transaction 38398034
  FS block 7536642 logged at sequence 38398245, journal block 12418
 ...
 ...
 ...
  Blocks: (0+1): 7559168
```

It tells us where the data block is 
Enter `q` to quite and finally run: 

```
dd if=/dev/mapper/name of=file.txt bs=4096 count=1 skip=7559168
```

or if you are on a ext2 system run:

```
dump <4590386> data.txt
```

Finally we can check with

```
cat file.txt
```

#Examples
###Syncing Entire Folders to Dropbox
Dropbox and other cloud storage are great at keeping backups of our important files.
The problem is that these forms of storage can only sync what is in their folders.
This is where symbolic links are useful.

```
ln -s ~/Documents/essays ~/Dropbox
```

Here we are creating a soft link of the folder called essays into the dropbox folder. 
If the cloud provider you are using does not support symbolic links, simply type the following:

```
cd ~
mv Documents/essays Dropbox
ln -s Dropbox/essays Documents
```

Instead of syncing the symbolic link to the file, we can sync the actual file and we have a symbolic link to our documents folder.

Using this method has numerous advantages over just copying the files you want to sync over.
First off, it allows us to keep the changes we make in that folder up to date so we wouldn't have to keep recopying the contents. 
It will keep our folder structure. 
In our essays folder, we can separate the essays by class and dropbox will copy the structure for us.
We can backup important files without changing where our files are on our computer.

###Accessing files in a different partition
When starting out with linux it is easy to break your installation.
Assuming you have a separate partition with all of your important data and you named the partition Data, 
all you have to do is run the following commands:

```
ln -fsn /media/Data/Documents ~/
ln -fsn /media/Data/Pictures ~/
ln -fsn /media/Data/Videos ~/
```

As long as you have your partition called data mounted in /media, you can created a link to the folder in your home directory.
This command replaces your Documents, Pictures and Videos folder in your directory with a soft link. 
You can access and change the files in the folders as long as the partition is mounted. 

Why do all the extra work to access some files on another partition?
This allows you to keep all of your previous data from before you moved to linux so you wouldn't have to download all this data again. 
If you duo boot, you can access the same files from both OS's saving a large amount of space. 
If you break your linux install, you can simply reinstall linux without deleting all of your files. 

###Fixing Compatibility issues
Not only can you link to files and folders but you can also link to executables and execute the executable with a link.

```
ln -s /opt/program-1.2.3.4 program
```
This creates a soft link to the latest version of program 
Some features are not backwards compatible so multiple versions are kept.
Everything the program updates all you have to update is the link.
Running the program multiple times a day will save lots of typing!
###Organization with Links
Being able to access the same file in multiple files makes organization far easier. 

We will now be creating a hardlink of a picture for another directory

```
ln ../Family/12352162.png .
```

You can edit one picture and it will change all the other pictures.
It works just like a tagging system but with folders.
Why not soft links?
We use hard links in this case so moving files will not break the soft links.
Deleting a folder guarantees nothing will break.
Hard links use slightly less space.


#Interesting Facts
###Why are Hard Links not allowed for Directories and What Happens When We Try?
First lets make a empty directory and use `ls` to see some details about it.
```
$ mkdir test
$ ls -la test
total 8
drwxr-xr-x 2 lolipopping lolipopping 4096 Jun  8 20:32 .
drwxr-xr-x 3 lolipopping lolipopping 4096 Jun  8 20:32 ..
```
As you can see from the 2 and 3 the `.` and `..` folders are hardlinks.
So there can be hardlinks to directories but we just can't make it.
That is because of performance overhead and an extra complication for the file system.
One of the complications is when you delete a directory which has hardlinks, what should `..` point to?
If the directory is deleted from its parent but its link count is still greater than 0 then there must still be something pointing to it.
To find out way you would have to traverse the entire file system.

###How the mv and rm command works
`rm` just unlinks the file but does not overwrite the data. 
As long as you are in the same filesystem, `mv` just creates a hard link and removes the previous directory entry. 
This allows for faster reorganization without actually changing the data at all. 


