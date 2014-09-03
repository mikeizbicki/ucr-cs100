#The Wonderful World of GitHub!

This tutorial will teach you to master GitHub. Let's jump into it!

Now what's this GitHub thing you ask? Well its a wonderful tool for programmers. It allows you to back up your code,
data and files onto the internet and does so through the use of various `git` commands. You can keep track of changes that are made to files and work, and its something that you'll definitely be using in the future for work involving code, programs, and team contribution.

##Useful Commands
Now before we dive into using GitHub, there are a few commands that will prove useful throughout the learning proccess:

`ls` - a quick command that allows you to see the files and directories that are in your current working directory. Inputting it will yield something similar to this:
```
derp@well $ ls
Avngrs/    CS14/       Downloads/        Music/     selfies/
CS_GO/    cs61/       Firefox.png*      Nyan_Cat/   untitled.cpp
CS1000/   Desktop/    Izbicki_is_cool   Public/     Videos/
CS12/     DBRainbow/  lols/             rawr/
```
  * `-a` - appending this flag after the `ls` command will show the hidden files that start with a `.` such as `.gitconfig`
  *  `-l` - will allow you to see additonal information about each file.

`cd` - your go to command to navigate through directories. Inputting only `cd` will take you to your default home directory.
  * `cd x` will take you into a directory named x, but only if directory x is in your current directory.
  * `cd ..` - appending two periods after the cd command will exit a directory by one level.

  A cool thing you can do with the `cd` command is append directory names with the `/` character to cd through multiple levels! In your terminal if you were to run the command
```
$ cd a/b/c
```
You would be able to directly `cd` into directory c without having to go into a, then into b, then into c. It's magical!

`touch` - this command will create simply create a file.
```
$ touch boat
```
Creates a file named "boat"

`mkdir` - is the same as `touch` but creates a directory instead.


##Creating a Repository
Creating a repository (aka a directory where you'll be storing your work) is
simple and requires the use of `mkdir`, `cd`, and `git init`. Type in the following commands in your terminal and see what happens.

```
$ mkdir reponame
$ cd reponame
$ git init
```

Congrats! You've made your first repository! In the case above your repository would be named "reponame", so all you have to do is input those commands and substitute "reponame" with the name of the repository you want to create. After you've created this repository, the `git init` command initializes the repository.

##Creating Files and Keeping Track of them.
As mentioned above using the `touch` command allows you to create a file.
Using the command `git add` followed by a filename will allow it to be added to your list of things to be commited. Ideally when you first create a file you should run `git add` "filename" in order to add it. This has to be redone every time your edit your file because the last "file" that was added into the commit pool was the version before you made changes.

**NOTE:** Never add executable files like a.out! They only make your repository cluttereed. Additionally it takes up a lot of memory just to keep track of them. Don't do it!

##Git Commit
Now we're going to learn how to unlock the powers of time travel! Commits are an important part of using GitHub. In a sense, using the `git commit -m`, followed by a description of your choice, is equivalent to checkpoints. For example after you've implemented one function in your code you could run
```
$ git commit -m "implemented function 1"
```
After you've successfully implemented another function you could run
```
$ git commit -m "implemented function 2"
```
These two commits save your progress on your code at different points.

You can easily call up a list of commits you've made by using the `git log` command! Using this will allow yo to see all of the recent commits you've made. Running it might look a little something like this:
```
$ git log
commit 0f0156b8af0b6d33ba59e1a6b133ec775d08be04
Author: Mister Derp <hd@well.cs.ucr.edu>
Date:   Tue Aug 26 13:43:51 2014 -0700

    implemented function 2

commit ae42e9a1746863246ba379f615ae0d20b9ddb6d8
Author: Mister Derp <hd@well.cs.ucr.edu>
Date:   Thu Aug 21 14:13:05 2014 -0700

    implemented function 1

```
Go ahead and try it!
One of the first things you might have noticed is the long mumbo jumbo of numbers and letters in your list of commits. Now before you panic and try to make sense of the gibberish, don't. Thats just basically your commit's SHA1 hash, in other words, its a unique indicator so that you can identify your commit. In order to go to whichever commit you want, you have to use the command `git checkout` followed by the commits hash like this:
```
$ git checkout insert_SHA1_here
```
If you check your files now they will be in the state they were when you made this commit!

**NOTE:** This only works on files that are tracked by git. Files that you never added won't be affected whenever you commit.

##Git Pull and Git Push
Now that you have your repository its time to learn about pushing and pulling. `Git push` and `git pull` are important concepts when it comes to using GitHub. You can almost think of them vaguely along the lines of downloading and uploading, respectively. When you "push" your work up into GitHub you're putting it onto the remote and syncing it with the work that you have on your local laptop, desktop, etc.



##Git Push
The command `git push` wraps a big part of what we're trying to do. Once you've got all your files nicely added and commited, you're ready to push the files onto GitHub. Imagine GitHub as a big cloud of information and code called the **remote**, and you're literally "pushing" your work into this cloud from your local computer. Of course, you have to specify where you're trying to push. Once you input the command you'll be prompted to type in your username and password for your GitHub account. Afterwards you should see a some status messages show up. If you see unhappy messages then worry not, there's plenty to ways to fix your errors.
Sometimes you may get the message:
```
Everything up-to-date
```
That simply means that the everything currently on your GitHub is already in sync with your local machine. 





##Branching
Branching is a powerful tool that you can use when editing your work, but if the concept is new to you then it may be a bit confusing.
The basic idea behind branching is to create a different version of your repository in which you can freely make edits without affecting your default main branch (called the "master" branch). If you, for example, managed to implement part of your code but wanted to add additional functions, you could create a branch and edit it. In the case that your program goes bad or crash your main branch would not

Use of branches requires creating new ones, switching between branches, and merging them together when you are satisfied. Time to test it out! First, `cd` into your repository and then run
```
$ git branch
```
That command pulls up all the branches you have for your current repository. The branch that you are actually on is denoted by an asterisk in front of the branch name. Now run
```
$ git branch test
$ git checkout test
$ git branch
```
The asterisk moved! Can you figure out what happened? It turns out that you created a new branch called "test" and switched over to it! `Git branch` on its own allows you to see all your branches, but when you append a name after the command, it will create a new branch with that name. `Git checkout` allows you to pretty much "checkout" and switch over to the branch specified. You're free to multiple branches to suit your needs, but just make sure to keep track of them and take note of which one you're working on!

##Merging and Conflicts
Once you're done working on your different branches, its time to merge them by checking out the master branch and then using `git merge` like so:
```
$ git checkout master
$ git merge test
```
Though merging is an efficient way to get different versions of your work on the same page, multiple merges can cause conflicts and yield a message like this:
```
Auto-merging main.cpp
CONFLICT (content): Merge conflict in main.cpp
Automatic merge failed; fix conflicts and then commit the result.
```
An issue that arises when you attempt to merge branches is the conflict between the contents. If you have two different versions of the same file on each branch, you will get an error message when you try to merge the branches. Opening up the file will give you a series of arrows that shows you where to make your edits. In order to resolve these conflicts you have to make changes to your file so that they're consistent.
```
#include <iostream>
int main()
{
<<<<<<< HEAD
    cout<<"yoloswag";
    return 1;
=======
    cout<<"#yoloswag" <<endl;
    cout<<"ftfy";
    return 0;
>>>>>>> branch1
}
```
Here theres a discrepancy. Whats important is that the code in between the <<<<<<< and the >>>>>>> is not consistent, and its your job to fix it. Code above the ======= only belongs in the master branch version while code below the ======= only belongs in "branch1." What you have to do is include the code from each branch that you want.

##Git Status
Got everything so far? So many new concepts can be a bit overwhelming and so a useful fucntion that you can use is the `git status` command. This command will pull up a handy menu of things for you can keep track of like this:
```
$ git status
# Not currently on any branch.
# Changes not staged for commit:
#   (use "git add <file>..." to update what will be committed)
#   (use "git checkout -- <file>..." to discard changes in working directory)
#
#       modified:   src/ls.cpp
#       modified:   src/main.cpp
#
# Untracked files:
#   (use "git add <file>..." to include in what will be committed)
#
#       .LICENSE.swp
#       bin/
#       src/a.out
no changes added to commit (use "git add" and/or "git commit -a")
```
Pretty useful, huh. It tells you your current branch, and what will or won't be commited when you run `git commit`. Instructions are also provided to tell you what you can do to commit a file that isn't going to be commited.


##Forking!
What's forking, you ask? Well it's not food related that's for sure! (insert awkward laughter) Forking is when you, in a sense, copy someone else's repository. This is useful for quickly hitting your stride if you're trying to contribute to a repository that already has work in it. Forking will allow you to have your own version of the repository. You'll then be able to edit it as you please and update it however you want.

##Pull Requests
Ask and thou shalt recieve! Well not always, actually. Pull requests are a handy way of asking the original owner to merge your proposed changes. After you've made your changes to a repository that you've forked or pulled, you have to issue a pull request to the original owner. Some days the owner my decide that your pull request shall not pass, so make sure you give a good description of what you're trying to contribute!

##Basic Gist of Keeping Track of Everything
Now with everything going on heres a quick reminder of how to keep track of everything that is going on. `Git status` will, as mentioned above, will allow you to see all files that will not be commited (unless you readd them!). `Git log` will let you see all of the commits that you've made and `Git branch` allows you to see all of the branches that you've made (use `checkout` in order to switch to the branch that you want). Using these commands regularly will make life a lot easier, so make good use of them!

##Well that's it!
This marks the end of this tutorial for GitHub. Now that you've learned the ways and have become a GitHub master, go forth and unleash its full potential! In the words of famous rapper Lil' Jon "GIT OUTTA YOUR MIND!"

![alt text](http://www.hotnewhiphop.com/public/article/600_1359263847_e44b3b098846d2282eac5ec231e5bb30.gif)







