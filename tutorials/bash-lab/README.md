# Intro to the Bash Command Line and Vim

Purpose of this lab
------------------------------------
This lab will familiarize CS 100 students with the command line as they transition from using visual displays on Windows and OS X to the Linux Bash shell. Students will also learn how to use a new text editor: Vim.

Introduction
------------------------------------
Only 1.41% of all desktop and laptop computers run Linux as the primary operating system. That means you probably don't have too much experience with Linux either. 

Linux programmers primarily use the command line to interact with the computer and this may seem foreign to Windows and Mac users. 

By the end of this lab, you will be able to execute basic commands in the Bash terminal to create, move, and delete files and directories, as well as a few other useful functions.

Terms and Definitions
-----------------------------------
`<your username>`: In this lab, whenever you see `<your username>`, simply replace it with your UCR username. An example username is `kwest001`.

**Shell:** An interface for the terminal that allows for interaction between the computer and the user. In this class, we will be using the Bash shell. 

**Terminal:** For the sake of this lab, the "terminal" is the program that the user will run to type in commands. Used interchangably with "shell" and "command line".

**Command Line:** The command line is a way for the user to interact with the computer through various text commands. Used interchangably with "shell" and "terminal".

**Directory:** A directory is like a folder. It holds files and other directories.

**Unix:** This lab refers to Unix as the "Unix Philosophy". It emphasizes proper programming etiquette. 



Let's get started!
-----------------------------------
First of all, you must open the terminal. You can find the terminal by clicking Applications -> System -> Terminal. 

From this point on, you will be using the mouse as little as possible! Efficient programming is one of the main virtues of Unix culture. That means limiting your mouse usage in favor of keyboard usage.

**IMPORTANT:** Before you run any commands, type the following into the terminal:
```
$ ssh <your username>@hammer.cs.ucr.edu
```
You may be promted to log in after you ssh into hammer. Hammer is a server provided by UCR specifically for CS100 to break stuff! You will be doing all of your work in hammer so remember to always ssh into hammer when you go to lab!

Once you are in hammer, you must set the settings to CS100, simply type:
```
$ cs100
```
A pretty window will pop up confirming that you have enabled CS100 settings. Don't forget this step! It's crucial and will save you plenty of headache throughout this quarter.

Every time you open a new terminal, you must ssh into hammer and enable CS100 settings.

Throughout this lab, there will be 10 exercises. Get out a pen and paper and be prepared to write down the answers to those exercises in order to show the TA.

pwd (Print Working Directory)
------------------------------------
The first command you will learn is `pwd`. `pwd` stands for "Print Working Directory" and will output the current directory you are in to the screen. Since you just typed in the ssh command, you should be in the HOME directory. Try it out!
```
$ pwd
```
The output should look something like this:
```
home/csmajs/<your username>
```
What does this mean? You have probably seen something similar to this before (perhaps in the url to this website). This is a path! Paths are chains of directories in directories. Each directory is separated by a `/`. In this case, your current directory, `<your username>`, is in `csmajs` which is in `home`. Later on, you will be using paths to access files in directories far away from your current directory.

You may have noticed the `$` that gets outputted after a command is run. This simply means that the terminal is expecting an input from the user.

`pwd` is a useful command that helps you navigate through different directories quickly. If you're lost and you don't know which directory you are in, call `pwd`! 


ls (list files)
------------------------------------
Now that you know what directory you're in, don't you want to know what files are inside this directory? `ls` does the job!
Try typing the following:
```
$ ls
$ ls -a
$ ls -l
$ ls Desktop
```
The `-a` and `-l` are flags. Most commands come with optional parameters that change how they function. `ls` by itself with simply output the files and directories in the current directory. 

`ls Desktop` will output the files and directories in the `Desktop` directory.

Here are some useful flags. Feel free to try them if you haven't already!
`ls -a`: prints all the files and directories, even if they are hidden files which begin with a `.`.

`ls -l`: prints all the files and directories and gives detailed information including permissions, date last modified, and many more!

`ls -R`: prints all the files and directories, and those in each directory in it. Think of it as a binary search tree! This command will output every node in the tree.

`ls -t`: prints all the files and directories and sorts them in order of the date last modified. The most recent will appear first.

Notice that when you used the flag `-a`, you may have noticed some files called `.` and `..`. These are both hidden directories found in every directory. 

`.` refers to your current directory.

`..` refers to the parent directory.

These flags can be combined such as `ls -tla` or `ls -aR` and multiple files/directories can also be passed in as parameters.

You will be using `ls` and `pwd` a lot in this lab and throughout the quarter so get used to them! 

**Exercises:**

1) Write a command that prints all files and folders in the existing folders `Pictures` and `Music`.

2) Write a command that prints all files and folders in your parent directory.

3) Write a command that prints all files and folders, including hidden ones, with detailed information, sorted in chronological order. You may only pass in one parameter.

touch (create a file)
--------------------------------------
In order to create new files, the `touch` command must be used.
Note that the `touch` command simply creates an empty file. You will go further indepth into file editing at the end of this lab.

We will now be creating a new file. In order to do this, enter:
```
$ touch main.cpp
```
Lets check out the file you just created using the command:
```
$ ls
```
Notice how the file now appears in the directory. congratulations, you've just created your first file on linux!

**Tip:** If you `touch` a file that already exists, it will simply update the date last modified. Try running these commands and compare the main.cpp file with `ls -l`
```
$ ls -l
$ touch main.cpp
$ ls -l
```

**Exercise:**

4) Write a command that creates a file name `touched.txt` in an existing directory called `Desktop`.

mkdir (create a directory)
--------------------------------------------
Moving on to the big boys.

We will now create a new directory within our current path.
The command we will use is `mkdir`. Like the `touch` command, this command also has a path parameter that will determine the location of the new directory.

  Example: commands `mkdir ./newDir` and `mkdir newDir` will both create the directory `newDir` within your current directory.
  
Using `mkdir`, lets create a directory name `temp` in our current directory:
```
$ mkdir temp
```

Opps!
We've just recieved a message from the higher ups saying that our new directory has an incorrect name. Lets delete this and make a new one! Wait a minute... 

rmdir (remove a directory)
---------------------------------------------
The command `rmdir` will delete a directory as long as it is empty. Type the following to delete your `temp` directory...
```
$ rmdir temp
```
Now that you deleted your directory, make a new directory called `CS`.
```
$ mkdir CS
```

Let's move on to a new comman- What's that? `CS` is still the wrong directory name? Ok, the next command we'll go over is a more efficient method than deleting and creating a new directory. Besides, Unix is all about efficiency right?



mv (move)
-------------------------------------------
The command `mv` moves files/directories from one place to another. The syntax for this command is:
```
$ mv [sourcefile1] [sourcefile2] ... [destinationfolder]
```
`mv` can be used in another clever way. If you type mv with two parameters as so...
```
$ mv [sourcefile1] [newname]
```
This command will rename a file/directory to a new name! Now lets try to rename our `CS` directory. Rename it to `CS100`. 
```
$ mv CS CS100
```
Great job! now you have a directory called `CS100`! Type `ls` to see it. Here are some exercises to keep you busy...

**Exercises:**

5) Write a command that moves two files called `cs100.rules` and `no.mouse` to a folder called `folder` in your parent's parent directory.

Now that you made a new directory, don't you want to see what's inside?

cd (cooldown... just kidding: change directory)
-----------------------------------------------------
So currently, you should still be in your home directory. If you are unsure, type 
```
$ pwd
```
Let's go deeper into your new `CS100` directory. In order to do this, type the following:
```
$ cd CS100
```

*Note that for the sake of this lab, `CS100` is the name of a directory. `cs100` is a command that enables cs100 settings.

`cd` is a command that allows you to change directories into the directory specified by the parameter. In this case, you will be changing directories to CS100.

Now type `pwd` again! You should now be in the directory you just created. Is there anything inside? What command would you type to find the contents of your current directory?

It's quite empty in here right? Let's furnish it with some files. Create a new file called `main.cpp`. You remember how to do that right?

**Hint!** If you type `cd` with no parameters, it will always take you back to your HOME directory. In this case, it is the directory you were in when you first ssh'd into hammer.

Now lets go back to the directory you were just in previously! How do you go back one directory? That's your exercise!

**Exercise:**

6) Write a command that changes directories to your parent directory.

If you haven't run that command yet, **do not move on until you do so.** 

You are now in the parent directory for `CS100`. Type `pwd` and you will see something along the lines of...
```
home/csmajs/<your username>
```
If you type `ls`, you will see your `CS100` directory. If you type `ls CS100`, you will see the file `main.cpp` and nothing else.

cp (copy)
------------------------------
The `cp` command will copy files and directories to your desired destination.

The syntax of this command is as follows:
```
$ cp [SOURCE] [DESTINATION]
```
**Note:** if the destination path does not exist, cp will create a copy of the file or directory with the name of the destination path given.
  
Remember that `main.cpp` we left behind in the HOME directory? Lets make a copy of it named `mainbro.cpp` and move it to our CS100 directory with the command:
```
$ cp main.cpp CS100/mainbro.cpp
```
Lets check our progress in the `CS100` directory with:
```
$ ls CS100
```
Your `CS100` directory should currently contain the files `main.cpp` and `mainbro.cpp`

BUT WAIT!

We no longer need the `main.cpp` file in our HOME directory, lets remove it!

rm (remove)
------------------------------
**BE VERY CAREFUL WITH THIS COMMAND!!!!!!!!**

The `rm` command removes a file. The syntax is 
```
$ rm [file1] [file2] ... [-flags] 
```

Enter the following command to remove the unnecessary `main.cpp` in the current directory.
```
$ rm main.cpp
```
**Try this!** On the terminal, run these commands:
```
$ mkdir california
$ touch california/riverside
$ touch california/sandiego
$ rmdir california
```

HA!
Your command resulted in an error
* if your command did not result in an error, the command you have entered must be incorrect.

This error is due to the conflict from attempting to remove a non-empty directory.

By including the `-r` (recursive) flag, we can sucessfully remove all files and directories within the desired path.

Empty this repository with the `-r` flag! Afterwards, check its contents.
```
$ rm -r california
$ ls california
```
As you can see, this directory is now empty and can be deleted with `rmdir`.

With great power comes great responsibilities!

You can use this power for evil and make a command that deletes all of the files in your computer. In fact, that's your next exercise! This one might need a bit of research...

**DO NOT RUN THIS COMMAND**

**DO NOT RUN THIS COMMAND**

**DO NOT RUN THIS COMMAND**

**Exercise:**

7) Write a command that removes all files in your computer. 

cat (concatenate)
-----------------------------
Next, we introduce the `cat` command, but we've forgotten what it exactly does.

No worries.

There is a command that serves as a manual page for bash commands.

man (manual)
----------------------------------
`man` command can be used with bash commands with the syntax
```
man [commandname]
```
Lets use the `man` command to find out the purpose of `cat`:
```
$ man cat
```
After some extensive reading, we can see that the main purpose of `cat` is to display the content of a file into stdout.

connectors
------------------------------------
Finally, a more efficient way to quickly run all the commands you've learned is the use of connectors `;`, `&&`, `||`
The `;` connector will execute every command separated by `;`. 

The `&&` connector functions similarly to the && comparison operator in C++, it will execute the next command as long as the previous command suceeded.

The `||` connector functions similarly to the || comparison operator in C++, it will execute commands as long as the previous command failed.

Commands can fail in many different ways. An example of a command failing is running `rmdir` on a directory that does not exist.

When using multiple connectors, using paretheses is extremely important because it tells the computer which order to execute multiple commands.

Using these connectors, we can greatly increase the efficency of our experience with the bash terminal. Here's an example!

```
$ mkdir sanfran && touch sanfran/goldengate.txt
```
Can you figure out what that does? What if there's already a directory called `sanfran`?

Let's Recap!
---------------------------------------
- `pwd` outputs the current directory.
- `ls` outputs all of the files/directories in the current directory.
- `touch` creates a file
- `mkdir` creates a repository
- `rmdir` removes a repository
- `mv` moves files
- `cd` changes directories
- `cp` copies files
- `rm` removes files
- `cat` outputs contents of a file into stdout
- `man` gives detailed descriptions of commands
- `.` is the current directory
- `..` is the parent directory

Final Exercises!
-------------------------------------------
By now, you should have finished 7 exercises! In order to show your proficiency with bash commands, we will test you with several more advanced exercises.

8) Write a command that removes a file called `gumwrapper`. If it does not exist, create a file called `gumwrapper` and move it to an existing directory called `trash`. Connectors are allowed.

9) Write a command that creates a directory called `sports`. If sports already existed, do nothing. Otherwise, move the existing file `baseball.txt` from your parent directory into `sports`. The parent directory should not have `baseball.txt` after running this command. There are two ways to do this. Connectors are allowed.

10) Assuming you are not in your HOME directory, write a command that prints out all of the files and directories in your HOME directory. You are not allowed to use connectors or the `cd` command.

Once you are done with all 10 exercises, you will learn how to use the text editor: `vim`.


vim (text editor)
------------------------------------------------
You will now familiarize yourself with the `vim` text editor.  In this class, you must use `vim` for all homework and lab assignments.  At first, you will find that `vim` is very weird.  But with practice, you will find `vim` much more powerful than either the `geany` or `Cloud9` editors you are already familiar with.  

The key to mastering `vim` is practice.  Therefore, you are required to use `vim` for all lab and homeworks assignments in this course.  **Using any editor other than `vim` will result in a 0 on the assignment.**

Open up a terminal and type the command `vimtutor` to get started.  This command walks you through the basics of using the `vim` editor.  Don't just read the file!!!  Make sure to actually do the exercises!!!

```
$ vimtutor
```

Once you have finished that, start playing the game: http://vim-adventures.com.
The first three levels are free (and that's all you're required to do).
You're welcome to pay for the full game if you want, but I'm not requiring you to do so.
And you won't get any extra credit for it.

## vim links

Here's some extra (optional but recommended) reading:

[stackoverflow: what is your most productive shortcut with vim?](http://stackoverflow.com/questions/1218390/what-is-your-most-productive-shortcut-with-vim)

[stackoverflow: simple vim commands you wish you'd known earlier](http://stackoverflow.com/questions/1276403/simple-vim-commands-you-wish-youd-known-earlier)

[vim for people who think things like vim are weird and hard](http://csswizardry.com/2014/06/vim-for-people-who-think-things-like-vim-are-weird-and-hard/)

## deliverables

Show the following to your TA:

Exercises 1-10
