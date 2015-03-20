# git patch, rebase and stash

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
This time, more information is offered! We can tell when and who submitted it, etc.

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




#Rebasing

##What is Rebasing
The ```merge``` and the ```rebase``` are the most common ways to integrate from one branch into another in Git. This tutorial will focus on ```rebase``` since ```merge``` have been taught in lab1-git. And you will learn how to do it, why it is a pretty amazing tool and in what cases you won't want to use it.

##How to Rebase
Assuming that we creat a branch 'cs100' on your remote branch 'master'.

```
$git checkout -b cs100 origin
```
![commit 2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit2.png)

After switch to it we can make some change 

```
$touch file
$git add file
$git commit -m "add file"
```
On the same time  your colleague have pulled two requests to origin branch ,which means the `master` and `cs100` will have conflict on each other. It is similiar to the 'Merge conflict' you have encountered in lab1.

![commit 1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit1.png)

But merge will creat a new merge commit on `master` which you don't want to commit.  
![commit 3 conflict](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit3conflict.png)

You want to keep the commits on the `cs100` branch without merge, then you can use git rebase:
```
$git checkout cs100
$git rebase master
First, rewinding head to replay your work on top of it...
Applying: add file
```

This command will save all your commits in `cs100` under a directory `.git/rebase` in patch format. When we updated origin to "already up-to-date" the patch will patch back to new `cs100` without leaving merge commits.
The result would be like this:

![commit 4 rebase](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebase.png)

Or if you find a specific commit on master is you want to rebase on to the result of following command:
```
$ git rebase --onto master~1 master
```
would be:

![commit 4 rebase onto](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebaseonto.png)

Once `cs100` point to a new commit, the old one will be through away. If you run 
`$git gc`(garbage collection), they may be removed.

If the rebase process find a conflict, after you fix the conflict, use git add and continue with
`$git rebase --continue` or if we want to back to status before rebase, run `$git rebase --abort`.



##Inerteractive Rebasing
Under this mode, you could rewrite your commits before pull request.(If I know this before my first commits, I would not have messed up my commits and had to delete the repo and forked again.) 
It facilitates you to separate merge and re-order commit and remove commits that you have already pulled to your laptop.

You can add `-i` after git rebase or `--interactive` to apply interactive mode to commit
```
$git rebase -i origin/master

pick fc62e55 added trash1
pick 9824bf4 added trash2
pick 21d80a5 added file

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

That is to say, we have five commits and every one follow this format:
```
[action][partial-sha][short commit message]
```

Now you can change the action (which is `pick` in default) to `edit`, `squash` or delete the line that you don't want to push. When you quit the edit mode, git will apply the new commits.



##The Perils of Rebasing
Rebasing is great, but depends on how you use it. It's not perfect, and will easily induce a lot problem with a few steps. Now we are teaching you how to **destory** other's repository like an expert. 

**rebase commits that exist outside one's repository.**

If you follow our guideline above, the repository will survive, otherwise you'll be cursed by your colleagues and your boss will fire you.

When you rebase, you’re throwing away commits in `git log` and creating a similar but different new one. Assuming you have push some commits to the server which your colleagues' work based on, and you modified them with `git rebase` and push them to server again, your partners have to merge their work and the commits will get messy once you want to pull their work.

Here is a successful example of destorying a repository by rebasing. Assuming you are pretending to work on a central server and you have fixed some bugs on your computer:
**(The upper commits are in server and the lower commits are locally)**

![rebase1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase1.png)
 
 Then someone pushes some commits without rebasing to the central server.
 
 ![rebase2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase2.png)
 
 He keeps waiting until his pull your commits to your computer and then use `git rebase` and `git push --force` to modify the commits to make them look clear and pushes the new commit to server.
 
  ![rebase3](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase3.png)

Now you are in a pickle that if you use `git pull` to get stuff 'up-to-date', you will creat a merge commit which is exactly same as last commit. Further more, when you use `git push`, you will send commits those are not exist in others git log and creat more confusions.

  ![rebase4](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase4.png)

#Stashing

Imagine this situation: you just made a commit for a.cpp and are half way developing b.cpp, but you suddenly realize that there is a small mistake in a.cpp.
If you want to keep your work in b.cpp, you have to make a commit for b.cpp with half-way work and then back to a.cpp and fix the bug. If you back to fix the bug in a.cpp without making the commit for b.cpp, you'll lose all the work in b.cpp since the last commit. 

Stashing is a way to solve this kind of problem -- fix the bug in previous commit without losing your recent work.

Now let's try the stash command:
Create a.cpp and b.cpp, make a commit for a.cpp and make some development in b.cpp after the commit.
```
$ touch a.cpp
$ toch b.cpp
$ vim a.cpp
$ cat a.cpp
// hello world
$ git add a.cpp
$ git commit -m "helloworld a.cpp"
[master cd3e990] helloworld a.cpp
 1 file changed, 1 insertions(+)
$ git add b.cpp # suppose b.cpp has already been in the stage in the real situation
$ echo int main() >> b.cpp
$ echo { >> b.cpp
$ echo } >> b.cpp
$ cat b.cpp
int main()
{
}
```
Now use git stash to interupt the current work and back to the last commit cd3e990:
```
$ git stash
Saved working directory and index state WIP on master: df93074 helloworld a.cpp
HEAD is now at df93074 helloworld a.cpp
```
make some change(fix the bug in a.cpp) and commit it:
```
$ echo // a new line in a.cpp to test stash >> a.cpp
$ cat a.cpp
// hellow world
// a new line in a.cpp to test stash
$ git add a.cpp
$ git commit -m "add a line in a.cpp"
[master e495093] add a line in a.cpp
 1 file changed, 1 insertion(+)
```
Using ```git stash list``` to check your stash status:
```
$ git stash list
stash@{0}: WIP on master: cd3e990 helloworld a.cpp
```
Back to the status which updates the develop in a.cpp and keeps the work in b.cpp by ```git stash apply```
```
$git stash apply
$ cat b.cpp
int main()
{
}
$ cat a.cpp
// hellow world
// a new line in a.cpp
```
just a reminder: it seems that SVN doesn't have that function.


####Stashing Queue
You can stash many status.(Always fixing the bugs)

Use this command you can check the stash list:
```
$git stash list
stash@{0}: WIP on book: 51bea1d... fixed images
stash@{1}: WIP on master: 9705ae6... changed the browse code to the official repo
```
You can also use this command to go back to the stash you want:
```
$git stash apply stash@{1}
```
and clear stash with command ```git stash clear```.


