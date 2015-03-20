# git-patch-and-rebase

[Purpose](##purpose)

[Patch](##Patch)
* [What is patch](###What is patch)
* [Create patch with git diff](###Create patch with git diff)
* [Create patch with git format patch](###Create patch with git format patch)

[Rebase](##Rebase)
* [Inerteractive Rebasing -i](###Inerteractive Rebasing -i)
* [Interactive Adding](###Interactive Adding)
* [Stashing](###Stashing)
* [Stashing Queue](Stashing Queue)


## Purpose
This tutorial will show you
* how to create a patch from your recent commits in your repository
* how to apply such patch to another repository correctly
* how to rebase your repo
* 

Just a reminder, if your want to develop the previous work in the repo, do it in a separate branch!
Now, let's start!

##Patch
###What is patch
When a software or a system releases a new version, we can download all the code and then install it. 
While huge projects like the Linux kernel can be over 70MB even after compressing. Meanwhile, the
new version of the code may change less than 1MB compared with the previous version. Git has offered 
us such a powerful tool that we can update the projects under extreme low cost -- ```patch```.

###Create patch with git diff
First, let's clone a repo and make some change:
```
$ git clone https://github.com/jinhangwang/example-repo.git
$ git checkout -b fix_empty_README.md
Switched to a new branch 'fix_empty_README.md'
$ echo Add a new line in README!!! >> README.md
$ git diff
diff --git a/README.md b/README.md
index 869ef75..fe8efa4 100644
--- a/README.md
+++ b/README.md
@@ -1 +1,2 @@
 # example-repo
+Add a new line in README!!!
```
The output of ```git diff``` is a typical patch file, we can redirect the output of command ```git diff```
to a file named patch, and the file patch will be a magic file to update your repo in the next step.
```
$ git commit -a -m "Add a new line"
[fix_empty_README.md eb93f96] Add a new line
 1 file changed, 1 insertion(+)
$ git diff master > patch
$ git checkout master
Switched to branch 'master'
Your branch is up-to-date with 'origin/master'.
$ ls
README.md patch
```
Now we are at the branch ```master``` and get the file ```patch``` which contains the diff information. We'll use ```git apply``` to utilize this patch. In fact, we barely create a patch at the branch and apply it in another branch (you can simply ```merge``` it). Now we assume the branch ```fix_empty_README.md``` doesn't exist. Normally, we are supposed to create a branch to handle the branches which commit new patches.
```
$ git checkout -b PATCH
Switched to a new branch 'PATCH'
$ git apply patch
$ git commit -a -m "Patch Apply"
[PATCH 15695e4] Patch Apply
 1 file changed, 1 insertion(+)
```
Now the ```patch``` has been applied to  the branch ```PATCH```, we can use ```git diff``` to check the differences between the branch of ```PATCH``` and ```fix_empty_README.md```, they will be absolutely same.


###Create patch with git format patch

This time, we will create the file ```patch``` with ```git-format-patch``` as below:
```
$ git checkout fix_empty_README.md
Switched to branch 'fix_empty_README.md'
$ echo "One more line" >> README.md
$ cat README.md 
# example-repo
Add a new line in READMEgit checkout -b fix_empty_README.md!
One more line
$ git commit -a -m "one more line"
[fix_empty_README.md 21641f7] one more line
 1 file changed, 1 insertion(+)
$ git format-patch -M master
0001-Add-a-new-line.patch
0002-one-more-line.patch
```
the option ```-M``` shows the branch to compare with, now there is two files for ```patch```, let's check it:
```
$ cat 0001-Add-a-new-line.patch 
From eb93f969ccc476a2a0050e9ee192216cf282da16 Mon Sep 17 00:00:00 2001
From: jinhangwang <jinhangwang001@gmail.com>
Date: Wed, 25 Feb 2015 11:28:56 -0800
Subject: [PATCH 1/2] Add a new line

---
 README.md | 1 +
 1 file changed, 1 insertion(+)

diff --git a/README.md b/README.md
index 869ef75..fe8efa4 100644
--- a/README.md
+++ b/README.md
@@ -1 +1,2 @@
 # example-repo
+Add a new line in READMEgit checkout -b fix_empty_README.md!
-- 
1.9.3 (Apple Git-50)

$ cat 0002-one-more-line.patch 
From 21641f7b1eee992896ed814bcd34a5c72047987f Mon Sep 17 00:00:00 2001
From: jinhangwang <jinhangwang001@gmail.com>
Date: Wed, 25 Feb 2015 11:59:17 -0800
Subject: [PATCH 2/2] one more line

---
 README.md | 1 +
 1 file changed, 1 insertion(+)

diff --git a/README.md b/README.md
index fe8efa4..544f799 100644
--- a/README.md
+++ b/README.md
@@ -1,2 +1,3 @@
 # example-repo
 Add a new line in READMEgit checkout -b fix_empty_README.md!
+One more line
-- 
1.9.3 (Apple Git-50)
```
This time, more information are offered! We can tell when and who submitted it, etc.

For the patch created by ```git-format-patch```, we have to use ```am``` to apply it.
```
$ git checkout PATCH
Switched to branch 'PATCH'
$ git am 0002-one-more-line.
Applying: one more line
$ git commit -a -m "PATCH-0002 apply"
```
Then we can check README.md to see if the new line has been added:
```
$ cat README.md
# example-repo
Add a new line in READMEgit checkout -b fix_empty_README.md!
One more line
```
Attention, if there are several commits between master and fix, it will create patch file for every commit.

===




#Rebasing

##What is Rebasing
The ```merge``` and the ```rebase``` are the most common ways to integrate from one branch into another in Git. This tutorial will focus on ```rebase`` since ```merge``` have been taught in lab1-git. And you will learn how to do it, why it is a pretty amazing tool and in what cases you won't want to use it.

##How to do Rebasing
Assuming that you creat a branch 'mywork' on your remote branch 'master'.

```
$git checkout -b mywork origin
```

After switch to it you make some change 

```
$touch file
$git add file
$git commit -m "add file"
```

On the same time  your colleague have pulled two requests to origin branch ,which means the 'master' and 'mywork'  will have conflict on each other. It is similiar to the 'Merge conflict' you have encountered in lab1.

But merge will creat a new merge commit on 'master' which you dont want to commit. You want to keep the commits on the 'mywork' branch without merge, then you can use git rebase:
```
$git checkout mywork
$git rebase origin
```

This command will save all your commits in 'mywork' under a directory '.git/rebase' in patch format. When you updated origin to "already up-to-date" the patch will patch back to new 'mywork' without leaving merge commits.

Once your 'mywork' point to a new commit, the old one will be through away. If you run 
```
$git gc
```
(garbage collection), they may be removed.

If the rebase process find a conflict, after you fix the conflict, use git add and continue with
```
$git rebase --continue
```

or you want to back to status before rebase, run
```
$git rebase --abort
```



##Inerteractive Rebasing -i
Under this mode, you could rewrite your commits before pull request.(If I know this before my first commits, I would not have messed up my commits and had to delete the repo and forked again.) 
It facilitates you to separate merge and re-order commit and remove commits that you have already pulled to your laptop.

You can add '-i' after git rebase or '--interactive' to apply interactive mode to commit
```
$git rebase -i origin/master
```

Once you run the command, you will turn to edit mode :
```
pick fc62e55 added file_size
pick 9824bf4 fixed little thing
pick 21d80a5 added number to log
pick 76b9da6 added the apply command
pick c264051 Revert "added file_size" - not implemented correctly

# Rebase f408319..b04dc3d onto f408319
#
# Commands:
#  p, pick = use commit
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#
# If you remove a line here THAT COMMIT WILL BE LOST.
# However, if you remove everything, the rebase will be aborted.
#
```

That is to say, you have five commits and every one follow this format:
```
[action][partial-sha][short commit message]
```

Now you can change the action (which is 'pick' in default) to 'edit', 'squash' or delete the line that you dont want to push. When you quit the edit mode, git will apply the new commits.



##The Perils of Rebasing
Ahh, but the bliss of rebasing isn't without its drawbacks, which can be summed up in a single line:

####Do not rebase commits that exist outside your repository.

If you follow our guideline, you'll be fine. If you don't, people will hate you, and you'll be scorned by friends and family.

When you rebase stuff, you’re abandoning existing commits and creating new ones that are similar but different. If you push commits somewhere and others pull them down and base work on them, and then you rewrite those commits with```git rebase``` and push them up again, your collaborators will have to re-merge their work and things will get messy when you try to pull their work back into yours.

Let’s look at an example of how rebasing work that you’ve made public can cause problems. Suppose you clone from a central server and then do some work off that. Your commit history looks like this:



#Stashing

When you find a bug that is obvious but small enough, like```cout<<"nama="<<endl;```, you may become crazy if you don''t fix it before continuing your former work. You can use ```git stash``` to save the current work status,  fix that bug and go on with your work.
```
$git stash "work in progress for foo feature"
```

This command will store you current change in ```stash```, and reset your work tree?? and match index ??? to the status when you modify the code for the bug. So when you commit the fixed code, a conflict will not happen between the status now and your previous work status.

```
$vim src/code.cpp
...
...
:wq
$git commit -a -m "fixed typo bug"
```

Then you can go back to you previous work status by:
```
$git stash apply
```

It seems that SVN does''nt have that function.

#Stashing Queue
You can stash many status.(Always fixing the bugs)

Use this command you can check the stash list:
```
$git stash list
stash@{0}: WIP on book: 51bea1d... fixed images
stash@{1}: WIP on master: 9705ae6... changed the browse code to the official repo
```
You also can use this command to go back to the stash you want:
```
$git stash apply stash@{1}
```
and clear stash with command ```git stash clear```.


