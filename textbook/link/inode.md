#Inodes
###What are Inodes?
Files are not directly linked to data blocks.
Instead they link to inodes.
Inodes or index nodes are a file structure of a file system. 
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
add explnation here~!!

#Data Blocks
Data blocks in unix are 1024 bytes.
As you can see, data blocks stores data.
If you want to store data less than or equal to 1024 bytes, it takes up one block.
The amount of blocks it takes up is the amount of data you want to store divided by 1024 bytes rounded to the nearest block.
If you want to store 1025 bytes, you want to use 2 blocks.
###Fragmentation
Storing data in block can cause fragmenttation. 
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
So now that you have this knowlage how can you use it?
###Restoring Deleted Files on ext2 ext3
Because the `rm` command does not overwrite any data and just deletes the node, 
we can restore data deleted.
=======
###Restoring deleted files
Since the `rm` command does not overwrite any data and just deletes the node, 
we have the ability to restore the data deleted.

```
$ echo 'hiii' > file.txt
$ ls -i file.txt
4590386 file.txt
$ rm file.txt
```

First we create a test file called file and use the `-i` flag to get the inode number.
Now we use the `debugfs` to get the information we need to restore the file. 

If your system is on `/dev/sda2` use

```
sudo debugfs -w /dev/sda2
```

If your system is on `/dev/mapper/SysVolGroup-LogVolRoot` use

```
sudo debugfs -w /dev/mapper/SysVolGroup-LogVolRoot
```

If you didn't get a chance to run `ls -i` you can find the inode number with `lsdel`.
The command displays:

* the deleted inode number
* its owner 
* size
* deletion date

Now run

```
logdump -i <4590386>
```

A lot of output will appear but we are only intrested on the line 

```
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
