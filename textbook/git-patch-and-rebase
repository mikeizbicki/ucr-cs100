# git-patch-and-rebase

[Purpose](##purpose)

[Patch](##Patch)
* [Create patch with git diff](###Create patch with git diff)
* [Create patch with git format patch](###Create patch with git format patch)
* [difference between git diff and git format patch](###difference between git diff and git format patch)

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
The output of ```git diff``` is a typical patch file, we can use this output as a patch directly:
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
Now we are at the branch ```master``` and get a file named ```patch```, which contains the diff information. Now we'll use ```git apply``` to ultilize this patch. In fact, we barely create a patch at the branch and apply it in another branch (you can simply ```merge``` it). Now we assume the branch ```fix_empty_README.md``` doesn't exist. Normally, we are supposed to create a branch to handler the branches which commit new patches.
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

This time, we will create the ```patch file``` with ```git-format-patch```.
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
Attention, if there are sever commits between master and fix, it will create patch file for every commit.

###difference between git diff and git format patch
===

##Rebase

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



###Inerteractive Rebasing -i
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


###Interactive Adding
This is a good way to manipulate you git add files to git index by typing 
```
$git add -i
```
and returns
```
staged     unstaged path
1:    unchanged        +4/-0 assets/stylesheets/style.css
2:    unchanged      +23/-11 layout/book_index_template.html
3:    unchanged        +7/-7 layout/chapter_template.html
4:    unchanged        +3/-3 script/pdf.rb
5:    unchanged      +121/-0 text/14_Interactive_Rebasing/0_ Interactive_Rebasing.markdown

*** Commands ***
1: status   2: update   3: revert   4: add untracked
5: patch    6: diff     7: quit     8: help
What now>
```
I dont know what exactly those commands means, so I type
```
8
```
or
```
help
```
then get
```
status        - show paths with changes
update        - add working tree state to the staged set of changes
revert        - revert staged set of changes back to the HEAD version
patch         - pick hunks and update selectively
diff          - view diff between HEAD and index
add untracked - add contents of untracked files to the staged set of changes
*** Commands ***
1: [s]tatus      2: [u]pdate      3: [r]evert      4: [a]dd untracked
5: [p]atch      6: [d]iff      7: [q]uit      8: [h]elp
What now>
```

Under this mode, you have many choices. When finish, type
```
7
```
or
```
q(quit)
```
git commit you change. But remember Do NOT use
```
$git commit -a
```
Otherwise all you have done above becomes nothing.

###Stashing

###Stashing Queue



