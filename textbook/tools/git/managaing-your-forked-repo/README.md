#Managing your Forked Repository

So you've forked your repository. Now you're one step closer to contributing to open source software and being a real hacker! Here are a few things that will help you along the way.

In this document, we will go over a few instructions and tips when it comes to managing your forked repository, which will include:

1. Syncing your forked repository with the original repository
2. Merging multiple commits into one
3. Resetting your forked repository when things go **BAD**

##Syncing your forked repository with the original repository

After you fork a repository, you get a copy of the current version of the original repository. But say the original owner makes changes to his/her own repository. As of now, your repository won't receive those updates automatically. It's good to regularly sync your forked repository with the original to avoid issues like trying to make changes that have already been made by the original owner or someone else.

To sync changes you make in a fork with the original repository, you need to configure a remote that points to the upstream repository in git. Here are the steps:

1. Open your terminal and go into your forked repository
2. List the current configured remote repository for your fork:

  ```
    $ git remote -v
  ```

3. Specify a new remote *upstream* repository that will be synced with the fork:

  ```
    $ git remote add upstream https://github.com/ORIGINAL_OWNER/ORIGINAL_REPOSITORY.git
  ```
4. Check that the new *upstream* repository you've specified for your fork:

  ```
    $ git remote -v
  ```

As you can see, `origin` refers to your forked repository, while `upstream` will refer to the original owner's repository.

5. To finally sync your forked repository, fetch the branches and their respective commits from the upstream repository.

  ```
    $ git fetch upstream
  ```

6. From here there are two methods through git which you can use: `git merge` and `git rebase`. The differences are explained on [stackoverflow](http://stackoverflow.com/questions/16666089/whats-the-difference-between-git-merge-and-git-rebase), but `git rebase` is generally what most developers prefer. So we'll use `git rebase` to sync our local forked repository with our *upstream*:

  ```
    $ git rebase upstream/MASTER_BRANCH
  ```

7. At this point, our local repository should be completely synced up. Now we just have to push these changes to our forked repository on github.

  ```
    $ git push
  ```

##Merging multiple commits into one

Say that you were making changes to a README.md file in your forked repository, and you made a lot of commits. Now you have a bunch of commits for that same file on your forked repository. If you were to submit a pull request right now, it would be really annoying and tedious for the original owner of the `README.md` file to look at each commit individually when they've all made changes to the same file. That's where merging commits comes in!

To do this, we need to take advantage of the `git rebase -i` command. For more information on git rebase, you can learn more [here](https://help.github.com/articles/about-git-rebase/). The `-i` flag puts rebase in interactive mode, which lets you do different things commits.

Let's say that you've just made 3 small commits to the `README.md` file, and now want to merge them all into one. Here are the steps:

Go to your forked repository in your terminal and enter:

```
  $ git rebase -i HEAD~X
```

  where `X` is the number of latest commits that you want to merge. In our example, `X` would equal 3.

```
  $ git rebase -i HEAD~3
```

At this point, an editor will open containing text similar to:
```
pick 01d1124 Updated title of README.md
pick 6340aaa Added new section
pick ebfd367 Fixed grammar errors

# Rebase 01d1124..ebfd367 onto 01d1124
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit's log message
#  x, exec = run command (the rest of the line) using shell
#
# If you remove a line here THAT COMMIT WILL BE LOST.
# However, if you remove everything, the rebase will be aborted.
#
```
There are a few commands available, but we're interested in the `pick` and `squash` commands.

The `pick` command means that the commit is included. Rearranging the order of the `pick` command will change the order of the commits when the rebase is underway.

The `squash` command is what lets you combine two or more commits into a single commit. A commit is "squashed" into the commits above it.us to "squash" all of the commits we want into one commit.

Looking back at our example, we can merge all of our commits into one like so: 

```
pick 01d1124 Updated title of README.md
squash 6340aaa Added new section
squash ebfd367 Fixed grammar errors
```
This tells Git to combine commit `6340aaa` and `ebfd367` into the first commit, `01d1124`.

Once you've made those changes, save and quit. Another editor will open.
```
#This is a combination of 3 commits.
# The first commit's message is:
Updated title of README.md

#This is the 2nd commit message:

Added new section

#This is the 3rd commit message:

Fixed grammar errors

# Please enter the commit message for your changes. Lines starting
# width '#' will be ignored, and an empty message aborts the commit.
# Explicit paths specified without -i nor -o; assuming --only paths...
# Not currently on any branch.
# Changes to be committed:
#   (use "git reset HEAD <file>..." to unstage)
#       modified: README.md
#
```
At this point, Git allows you to modify the new commit's message based on the rest of the commits involved in the process. Anything that is not commented out will be the new commit message, so you can change it to one concise commit message. Once you're done, you can save and quit the editor. If all worked correctly, your terminal should display something similar this:
```
Created commit ofc4eea: Updated title, added new section, and fixed grammar errors in README.md.
 4 files changed, 48 insertions(+), 12 deletions(-)
        Successfully rebased and updated refs/heads/master.
```
If all worked correctly, it means your commits have been successfully squashed. Now you want to push this change to your forked repository on github. However, if you were to do a normal push, you'll get this error similar to this:

```
error: failed to push some refs to 'https://github.com/YOURUSERNAME/NAMEOFREPO'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

This error occurred because after you merged your commits, git thinks that you're local repository is behind the repository on github. To get your merged commit onto your github, you need to force push this change onto your forked repository on github.

```
  $ git push -f
```

The `-f` flag stands for force. It's the same as a normal `git push` except the push is forced even if it results in a non-fast-forward merge.

##Resetting your forked repository when things go **BAD**
Say you've made a commit to your forked repository that had A LOT of changes from the previous commit. And you realize later that your latest commit actually broke the program. Or say that while you were trying to squash commits, you made a mistake, and now you have even more commits or you didn't merge the commits you wanted. It can get really tricky to try to solve these types of problems. Sometimes, things just don't turn out the way you expect them to, and you want to go back to an earlier commit where things were nice and working. That's where the `git reset --hard` command comes in.

`git reset` by itself resets the commit history, but not the files. With the `--hard` option the files in the repository are also reset. If you want to revert your whole repository to an older commit, here are the steps:

1. Go to your latest commit using `git checkout`.
2. Look up the commit number of the commit you want to revert to.
3. Enter this command:

```
  $ git reset --hard OLD_COMMIT_NUMBER
```

4. At this point, your local repository should now be reverted. Now you need to force push this change onto your repository on github.

```
  $ git push -f
```

**NOTE**: `git reset --hard` is a very powerful command and cannot be undone. If you'd like to keep the changes you've made just in case, you should branch off a copy of your changes before resetting. If you'd like to learn more about `git reset`, there's a great article that explains it [here](http://git-scm.com/blog/2011/07/11/reset.html).

