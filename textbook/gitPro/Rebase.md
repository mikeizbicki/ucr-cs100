#Rebasing

The `rebase` is one of  the most common ways to **integrate from one branch into another** in Git.
This part will focus on `rebase` and you will learn how to do it, why it is a pretty amazing tool and in what kind of cases you won't want to use it.

##How to Rebase
Assuming that we creat a branch `cs100` on your remote branch `master`:
```
$ git init
$ git checkout -b cs100 origin
```
The commit history goes like this:

![commit 2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit2.png)

After switch to `cs100` we can make some changes and commit them:
```
$ touch file
$ git add file
$ git commit -m "add file"
```
On the same time your colleague has pulled two requests to origin branch, and you use `git pull` to make your master branch up-to-date. 
And the history will be like:

![commit 1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit1.png)

If you want to keep all your commits **only** on the `cs100` branch, then you can use git rebase
(While `merge` will creat a merge commit and integrate all commits on `master` branch, I will compare them later):
```
$ git checkout cs100
$ git rebase master
First, rewinding head to replay your work on top of it...
Applying: add file
```

This command will save all your commits in `cs100` (in the example is `C2`) under a directory `.git/rebase` in patch format.
And reapply them/it to the on the top of the branch to be rebased ( here is `C4`), the graph will be like:

![commit 4 rebase](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebase.png)

Or if you want to temporarily rebase on to a commit on `master` but not at the end,  using `--onto [branch name]~[number after the commit where branches apart] [dst branch]` as an option for `git rebase`, the result of command `$ git rebase --onto master~1 master` would be:

![commit 4 rebase onto](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit4rebaseonto.png)

Once `cs100` point to a new commit, for instance, you commit another change after `C2`, the old patch (in the example is `C2` which have already been applied) will be thrown away.
If you run `$ git gc`(garbage collection), the old patch will also be removed.

If the rebase process find a conflict, for example, you colleague's also developing the file that you are working on, after you fix the conflict manually, use git add and continue with `$ git rebase --continue` or if we want to back to status before rebase, run `$ git rebase --abort`.

##Merge vs Rebase
We have learned another way `merge` to integrate branches in `lab1-git` , and the way of `merge` to integrate is pushing a new `merge commit` and combine branches with all commits before `merge`. 
Here is an example:

We get a git history like this:

![commit 1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit1.png)

and what `merge` does is creating a new merge commit `C2'` on `master` which doesn't actually include any part of your work.

![commit 3 conflict](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/commit3conflict.png)

Compared with `rebase`, `merge` would be a little bit messy for the `merge commits` everytime using `git merge`.
So `rebase` will present a better history not only for the contributors but also for the future readers.

##Inerteractive Rebasing
Under this mode, you could rewrite your commits before pull request.
This is really important for a beginner in Github because if you mess up the history in repo forked from Mike, you had to delete your repo and fork again which cause a lot problem that may let you get a F in this course.

You can add `-i` after `git rebase` or `--interactive` to apply interactive mode to commit, it facilitates you to separate merge and re-order commit and remove commits that you have already pulled to your laptop.
And the following information will display in our favoraite text editor as an example:
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

That is to say, we have several commits and every one follow format like:
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

It looks like huge work but by doing them step by step, it will be much easier.

First we modify the text in the file like this:

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

Now we have done the text part to modify the commits to what we intend to.
Save and quit with command `:wq` (with `Esc` first to input `vim` command)

Next the interactive rebase will start :
The interactive rebase will skip commands start with `pick` `ce9a29f` then to the `squash` on second line `9f27616` and open a new `vim` to edit the squash message:

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

This file is what Git tells you how it will `squash` the commits.
And `"Enrolled in CS100"` tells you the message of your first commit and `"added myself to class"` of the second commit, you can modify them as you wish.

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

Interactive rebase skips next two `pick`s and then processes the `fixup` command which automatically merge `2dcfbe6` into `57ecb22`. Both changes contain the same message `"Corrected spelling errors in Lab0"`.

Then it goes to `edit bffd586`, and stop to display information on terminal:
```
Stopped at bffd586c33f2ec5f992d379a632f3eefde422062... Small typo fix
You can amend the commit now, with

	git commit --amend

Once you are satisfied with your changes, run

	git rebase --continue
```

And you could use `git commit --amend` to commit changes you've made.
Then continue with `git rebase --continue`.
It will reach `reword db42315` with opening a new text editor to let you know you are editing you message.

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
And the interactive rebase will run the command after `exec` and shows:

```
Executing: echo the interactive rebase success
the interactive rebase success
Successfully rebased and updated refs/heads/2015winter.
```

Now we check the git log again with 

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

since you have changed exist history on the server.
But I only recommend you to do it **locally** with commits that don't exist on the server using `git push origin` because change exist history on the server will cause serious problem.

##The drawbacks of Rebasing
Rebasing is great, but depends on how you use it.
It's not perfect, and will easily induce a lot problem with a few steps.
Now we are teaching you how to **destory** other's repository like an expert. 

**rebase commits that exist outside one's repository.**

If you follow our guideline above, the repository will survive, otherwise you'll be cursed by your colleagues and your boss will fire you.

When you rebase, you’re throwing away commits in `git log` and creating a similar but different new one.
Assuming you have push some commits to the server which your colleagues' work based on, and you modified them with `git rebase` and push them to server again, your partners have to merge their work and the commits will get messy once you want to pull their work.

Here is a successful example of destorying a repository by rebasing.
Assuming you are pretending to work on a central server and you have fixed some bugs on your computer:
**(The upper commits are in server and the lower commits are locally)**

![rebase1](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase1.png)
 
Then someone pushes some commits without rebasing to the central server.
 
 ![rebase2](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase2.png)
 
He keeps waiting until his pull your commits to your computer and then use `git rebase` and `git push --force` to modify the commits to make them look clear and pushes the new commit to server.
 
  ![rebase3](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase3.png)

Now you are in a pickle that if you use `git pull` to get stuff 'up-to-date', you will creat a merge commit which is exactly same as last commit.
Further more, when you use `git push`, you will send commits those are not exist in others git log and creat more confusions.

  ![rebase4](https://github.com/jinhangwang/git-patch-and-rebase/blob/master/image/rebase4.png)
