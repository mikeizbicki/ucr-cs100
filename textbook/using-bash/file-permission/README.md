Permission
===
This tutorial will introduce the basic permission in the file system. 

The big advantage that Linux has is its multi-user concept- the idea will allow one or more users use or log into same computer to do a specific or different jobs. Although there are already a lot of good security features built into Linux-based systems, one very important potential vulnerability can exist when local access is granted - - that is file permission based on issues resulting from a user not assigning the correct permissions to files and directories. So I will go over some simple concepts about the permission and how to manage the file-permission.

This tutorial will use two commands **chmod** and **umask**.

##File permission

To see the permission settings for a file, we can use the `ls -l` command as follows
![screenshot-sjin010 tango-18 -hw4](https://cloud.githubusercontent.com/assets/9039778/5391455/dda0fee2-80cf-11e4-849c-f3b88ca4da09.png)

We can decide the file permission type by this information:

* The file `test` is owned by user `jinsongwei` which is my username.

* User `jinsongwei` has the right to read and write this file

* The file is owned by the group `csgrads`

* Members of the group `csgrads` can only read this file

* Anyone else can read this file

In the diagram below, we see how the first portion of the listing is interpreted. It consists of a character indicating the file type, followed by three sets of three characters that convey the reading, writing and execution permission for the owner, group, and everybody else.

![permissions_diagram](https://cloud.githubusercontent.com/assets/9039778/5336536/b9d34ed4-7e72-11e4-8576-b93584d756fc.gif)

picture provided by [© 2000-2014, William E. Shotts, Jr](http://linuxcommand.org/lts0070.php)


follow by `-rw-r--r--` the first `jinsongwei` is the username who own this file, and the second `csgrads` is group name, usually user and group name are same in the personal computer.

It is easy to think of permission setting as a series of bits:

`rwx rwx rwx = 111 111 111`

`r-- r-- r-- = 100 100 100`

`rwx = 111 in binary = 7`

`rw- = 110 in binary = 6`

`r-w = 101 in binary = 5`

`r-- = 100 in binary = 4`

`--- = 000 in binary = 0`

` and so on`

Therefore, there is a table about permission setting in binary:

![permssion binary](https://cloud.githubusercontent.com/assets/9039778/5337629/93c29134-7e7f-11e4-98d7-8e5979a68a66.png)

[© 2000-2014, William E. Shotts, Jr](http://linuxcommand.org/lts0070.php)

## simple file system

Let's talk about a little file system briefly. This is what file system looks like below. This picture may be in your computer, or a server (just like you login into the computer in the lab).

![fs-layout](https://cloud.githubusercontent.com/assets/9039778/5335933/7a337768-7e68-11e4-9288-d82c3f90ba52.png)

[Copyright (c) 2002-2007, Machtelt Garrels](http://tldp.org/LDP/intro-linux/html/intro_07.html)

On the left "/" means root directory, which is the top level directory on a system. That is, it is the directory in which all other directories, including their subdirectories, and files reside. The root directory is designated by a forward slash ( / ). Usually, the permission of root directory's files is owned by **root** which is superuser.
![screenshot-sjin010 tango-18 -](https://cloud.githubusercontent.com/assets/9039778/5391515/cf552a56-80d0-11e4-9bae-eeaf495f3cce.png)


You are a member of root group, so you have right to access and execute the file, but do not have right to change the file. 

In the diagram of filesystem, you will see `home` directory which is a group directory. In this directory in the picture, there is four usernames: rick, anna, emmy and bob -- in the lab, you will see `csgrads csmajs grads` in the `home` directory. In this group of members, you don't have right access those directories, only I have right access to the /home/csgrads/sjin010, which is my account.
![screenshot-sjin010 tango-18](https://cloud.githubusercontent.com/assets/9039778/5337107/992c241a-7e79-11e4-9ed3-2019375cd4fb.png)

So this is how users protect themselves from each other in a server. In a personal computer, there is usually only one group and one user in the `home` directory.

##Changing permission

###umask

When a user creates a file or directory, there are a set of default permissions. For example, if a text file has `666` (which is the same as the `rw-rw-rw` permission), it grants read and write permission to everyone. Similarly a directory with `777` permissions, it gives the user read, write, and execute permission to everyone. The user file-creation mask(umask) is used to determine the file permission for newly created files. It can control the default file permission for new files. It is a four-digit octal number. A umask can be set or expressed using **Symbolic values** and **Octal values**.

Here is table of Octal values:

![1502-octal-format-clarified](https://cloud.githubusercontent.com/assets/9039778/5392076/5c90ee5e-80d7-11e4-9921-f08759560a94.png)


####Setup Default umask
By default most Linux distro set it to 0022(022) or 0002(002). 

![screenshot-sjin010 tango-18 -hw4-2](https://cloud.githubusercontent.com/assets/9039778/5391953/e612dcf2-80d5-11e4-9578-bb213d1ee468.png)

Now, let's change the default permission setting for new file to `027`, which is related `rw-r-----`

![screenshot-sjin010 tango-18 -hw4](https://cloud.githubusercontent.com/assets/9039778/5392126/ebe71682-80d7-11e4-90f0-39dabe72c83b.png)

The new file's permissions changed. 




###chmod - modify file access rights
Use this command to change file's permission which is created by owner. Just simply type `chmod 600 file`

The 600 is the file's permission setting. As mentioned before, the machine thinks the permission settings as a series of bits.

![screenshot-sjin010 tango-18 -hw4-1](https://cloud.githubusercontent.com/assets/9039778/5392292/580b3f04-80d9-11e4-85ea-723411b89cc6.png)

Or you can type the permission changes by characters that you want to change. `chmod u=r,g=rx,o=rwx file2`

![screenshot-sjin010 tango-18 -hw4](https://cloud.githubusercontent.com/assets/9039778/5392365/1037afb8-80da-11e4-98c6-0944cd6ea2f2.png)

If you are willing to set your files as private in the lab, you can change all the directories setting in your account as `700` that only you can read, write and execute the files.

####Sticky bit
In the directory `/tmp`, any user can store files in `/tmp` but only the owner of the file has the rights to modify or delete the file from `/tmp`.

![screenshot-sjin010 tango-18 -](https://cloud.githubusercontent.com/assets/9039778/5392828/95942aba-80df-11e4-9af4-1c65a4d05b7a.png)

At end of the permission expression, there is a `t`, which is the sticky bit that says that you can create any file in this directory, but cannot delete any other files that you do not own.

Let's bring an example. 

If you run a command `su - guest1 - c "touch guest1.txt"`, which creates `guest1.txt` owned by `guest1` and

run another command `su - guest2 - c "touch guest2.txt"` that creates `guest2.txt` owned by `guest2`.

And if `guest2` wants delete `guest1.txt` which owned by `guest1`

`su - guest2 - c "rm guest1.txt"`.

There will be an error.

`rm: remove write-protected regular empty file 'guest1.txt'? y`

`rm: cannot remove 'guest1.txt': Operation not permitted`

So, how do we set the sticky bit to a file or directory? There is several ways to do that; the easy, understandable way is to just simply use the `chmod` command, `chmod +t <filename>`

![screenshot-sjin010 tango-18 -hw4](https://cloud.githubusercontent.com/assets/9039778/5393035/d0480f9e-80e1-11e4-82da-a69243008fd6.png)

 

##Security

When you write into a read-only file in vim, you will be given a warning - "this file is read-only". However, it also has a tip on the next "using `!` can override this file. " This is because, you are actually writing a temp file into the system, then the system will delete the original file and create a new one. So you have permission to make the file read-only, but you don't have actual permission to change the permission settings under the system level. Many applications delete and create new files when edits are made, if your directory permissions are not secure. This can be a security concern. Therefore, the permission settings will be very important on the security system.





