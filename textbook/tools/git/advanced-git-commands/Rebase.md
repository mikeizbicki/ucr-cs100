#Rebasing

The `rebase` is one of  the most common ways to **integrate from one branch into another** in Git.
This part will focus on `rebase` and you will learn how to use it, why it is a pretty amazing tool and what kinds of cases you won't want to use it in.

##How to Rebase
Assuming that we create a branch `cs100` on your remote branch `master`:
```
$ git init
$ git checkout -b cs100 origin
```
The commit history goes like this:

![commit 2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit2.png)

After we switch to `cs100`, we can make some changes and commit them:
```
$ touch file
$ git add file
$ git commit -m "add file"
```
Let's say, at the same time, your colleague has pushed two commits to the origin branch, and you use `git pull` to make your master branch up-to-date. 
The history will be like:

![commit 1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit1.png)

If you want to keep all of your commits **only** on the `cs100` branch, then you can use git rebase
(Using `merge` will create a merge commit and integrate all commits on the `master` branch.
I will compare them later):
```
$ git checkout cs100
$ git rebase master
First, rewinding head to replay your work on top of it...
Applying: add file
```

This command will save all of your commits in `cs100` (in the example it is `C2`) under a directory `.git/rebase` in patch format.
Rebase will then reapply them to the top of the branch to be rebased ( here it is `C4`).
The graph will be like:

![commit 4 rebase](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebase.png)

However, if you want to temporarily rebase on to a commit on `master` but not at the end, you can use `--onto [branch name]~[number after the commit where branches apart] [dst branch]` as an option for `git rebase`. 
The result of the command `$ git rebase --onto master~1 master` would be:

![commit 4 rebase onto](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebaseonto.png)

Once `cs100` points to a new commit, for instance, you commit another change after `C2`, the old patch file (in the example is `C2` which have already been applied) will be thrown away.
If you run `$ git gc`(garbage collection), the old patch file will also be removed.

If the rebase process finds a conflict, for example, your colleague's also developing on the file that you are working on, then after you fix the conflict manually, use `$ git add` and continue with `$ git rebase --continue`.
However, if we want to go back to the status before the rebase, run `$ git rebase --abort`.

##Merge vs Rebase
Previously, we have learned how to `merge` and integrate branches in `lab1-git`.
How `merge` works to integrate is by pushing a new `merge commit` and then combine branches with all commits before `merge`. 
Here is an example:

We get a git history like this:

![commit 1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit1.png)

and what `merge` does is that it creates a new merge commit `C2'` on `master` which doesn't actually include any part of your work.

![commit 3 conflict](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit3conflict.png)

Compared with `rebase`, `merge` would be a little bit messy for the `merge commits` performed every time when using `git merge`.
Therefore, `rebase` will present a better history, not only for the contributors, but also for the future readers.

##Interactive Rebasing
Under this mode, you can rewrite your commits before the pull request.
This is really important for a beginner in Github because, if you mess up the history in the repo forked from Mike, you will have to delete your repo and fork again which can cause a lot problems that can get a F in this course.

You can add `-i` after `git rebase` or `--interactive` to apply interactive mode to commit.
It facilitates you in separating merge and in re-ordering commits and removing commits that you have already pulled to your laptop.
The following information will display in our favorite text editor as an example:
(Do not use `:wq` in it before the test)
```
$ git clone https://github.com/Laviness/ucr-cs100.git 
$ cd ucr-cs100/
$ git rebase -i HEAD~7

pick ce9a29f Enrolled in CS100
pick 57ecb22 Revert "enrolling in cs100 and fix a spelling error"
pick bffd586 Small typo fix
pick 2dcfbe6 Corrected spelling errors in Lab0
pick 9f27616 added myself to class
pick e30fc91 updated github info
pick db42315 added yliu127 info
pick 6a54209 Update README.md

# Rebase 55a8214..6a54209 onto 55a8214
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit's log message
#  x, exec = run command (the rest of the line) using shell
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
```

That is to say, we have several commits and every one follows the following format:
```
[action][partial-sha][short commit message]
```

Now you can change the action (which is `pick` in default) to `edit`, `squash` and so on or delete the line that you don't want to push.
When you quit the edit mode, git will apply the new commits.

Here is a test for you to practice:

Squash the fifth commit `9f27616` into the `"Enrolled in CS100"` commit `ce9a29f`, using `squash`.
Move the last commit `6a54209` up before the `Revert "enrolling in cs100 and fix a spelling error"` commit `57ecb22` and keep it as `pick`.
Merge the `"Corrected spelling errors in Lab0"` commit `2dcfbe6` into the `"Revert "enrolling in cs100 and fix a spelling error"` commit `57ecb22`, and disregard the commit message using `fixup`.
Split the third commit `bffd586` into two smaller commits, using `edit`.
Fix the commit message of the misspelled commit `db42315`, using `reword`.

It looks like a lot of work but by doing them step by step, it will be much easier.

First, we modify the text in the file like this:

```
pick ce9a29f Enrolled in CS100
squash 9f27616 added myself to class
pick 6a54209 Update README.md
pick 57ecb22 Revert "enrolling in cs100 and fix a spelling error"
fixup 2dcfbe6 Corrected spelling errors in Lab0
edit bffd586 Small typo fix
pick e30fc91 updated github info
reword db42315 added yliu127 info
exec echo the interactive rebase success
```

Now we have done the text part to modify the commits to what we intend them to be.
Save and quit with command `:wq` (with `Esc` first to input `vim` command)

Next, the interactive rebase will start :
The interactive rebase will skip commands that start with `pick` `ce9a29f` then to the `squash` on second line `9f27616` and open a new `vim` to edit the squash message:

```
# This is a combination of 2 commits.
# The first commit's message is:

Enrolled in CS100

# This is the 2nd commit message:

added myself to class

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# Author:    jng017 <jng017@ucr.edu>
#
# rebase in progress; onto 55a8214
# You are currently editing a commit while rebasing branch '2015winter' on '55a8214'.
#
# Changes to be committed:
#   new file:   people/students/cfan002
#   new file:   people/students/jng017
#
```

This file is where Git tells you how it will `squash` the commits.
`"Enrolled in CS100"` tells you the message of your first commit and `"added myself to class"` of the second commit.
You can modify them as you wish.

When you save and close the text editor, rebase continues:
```
pick ce9a29f Enrolled in CS100
squash 9f27616 added myself to class
pick 6a54209 Update README.md
pick 57ecb22 Revert "enrolling in cs100 and fix a spelling error"
fixup 2dcfbe6 Corrected spelling errors in Lab0
edit bffd586 Small typo fix
pick e30fc91 updated github info
reword db42315 added yliu127 info
exec echo the interactive rebase success
```

Interactive rebase will then skip the next two `pick` commands and then process the `fixup` command which automatically merges `2dcfbe6` into `57ecb22`. Both changes contain the same message `"Corrected spelling errors in Lab0"`.

Then it goes to `edit bffd586`, and it stops to display information on terminal:
```
Stopped at bffd586c33f2ec5f992d379a632f3eefde422062... Small typo fix
You can amend the commit now, with

	git commit --amend

Once you are satisfied with your changes, run

	git rebase --continue
```

You can also use `git commit --amend` to commit changes you've made.
Now, continue with `git rebase --continue`.
It will reach `reword db42315` and open a new text editor to let you know you are editing you message.

```
added yliu127 info

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
# rebase in progress; onto 55a8214
# You are currently editing a commit while rebasing branch '2015winter' on '55a8214'.
#
# Changes to be committed:
#   new file:   people/students/yliu127
#
```

Change the `"added yliu127 info"` to `"added yliu127"` and `:wq`.
The interactive rebase will run the command after `exec` and show:

```
Executing: echo the interactive rebase success
the interactive rebase success
Successfully rebased and updated refs/heads/2015winter.
```

Now we can check the git log again.

```
$ git log 

commit 830bae365d3613fc13ce7e883e97d30fc86c9b7d
Author: Laviness <liuyuqi2020@gmail.com>
Date:   Tue Jan 13 17:07:30 2015 -0800

    added yliu127

commit 3a6115a19e839ad00f3f36e98f8973781154b069
Author: cfan002 <cfan002@ucr.edu>
Date:   Tue Jan 13 14:22:53 2015 -0800

    updated github info

commit 077e3863dfef621985d4cfe7cea12473da7e3408
Author: Rica Feng <topgb@msn.com>
Date:   Mon Jan 12 20:51:24 2015 -0800


    Small typo fix
    
    Fixed small typo, made a title more consistent


    Small typo fix
    
    Fixed small typo, made a title more consistent

commit 7622a25cc2ec93e55909fc3548031f4130d6826d
Author: Mike Izbicki <mike@izbicki.me>
Date:   Tue Jan 13 11:10:01 2015 -0800

    Revert "enrolling in cs100 and fix a spelling error"

commit bcc67612a6b9b04c644395d597b59ad5d64dde83
Author: Laviness <liuyuqi2020@gmail.com>
Date:   Wed Feb 11 00:37:29 2015 -0800

    Update README.md

commit fa6ab85170eeb11fea3105da0a7777e466be4c4d
Author: jng017 <jng017@ucr.edu>
Date:   Mon Jan 12 17:48:49 2015 -0800

    Enrolled in CS100
    
    added myself to class
```

The commits have been changed successfully. To `push` your modified history to github you need to use
```
$ git push https://github.com/Laviness/ucr-cs100.git --force
```

since you have changed the existing history on the server.
But I only recommend you to do it **locally** with commits that don't exist on the server using `git push origin` because changing the existing history on the server can cause serious problems.

##The drawbacks of Rebasing
Rebasing is great, but it depends on how you use it.
It's not perfect and will easily induce a lot of problems with a few steps.
Now we will teach you how to **destroy** a repository like an expert. 

**rebase commits that exist outside one's repository.**

If you follow our guideline above, the repository will survive, otherwise you'll be cursed by your colleagues and your boss will fire you.

When you rebase, you’re throwing away commits in `git log` and creating a similar, but also different and new commit.
Assuming you have pushed some commits to the server which your colleagues' works are based on, you modified them with `git rebase`, and pushed them to the server again, your partners will have to merge their work and the commits will get messy once you want to pull their work.

Here is a successful example of destroying a repository by rebasing.
Assume you are working on a central server and you have fixed some bugs on your computer:
**(The upper commits are in the server and the lower commits are local)**

![rebase1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase1.png)
 
Then someone pushes some commits without rebasing to the central server.
 
 ![rebase2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase2.png)
 
He keeps waiting until you pull his commits to your computer and then he uses `git rebase` and `git push --force` to modify the commits to make them look clear and pushes the new commit to server.
 
  ![rebase3](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase3.png)

Now you are in a pickle because if you use `git pull` to get stuff 'up-to-date', you will create a merge commit which is exactly same as last commit.
Furthermore, when you use `git push`, you will send commits that do not exist in others' git log and create more confusion.

  ![rebase4](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase4.png)
