#How to issue a pull request to someone else's repository

So you want to contribute to someone else's repository or open source software? That's great! Contributing to someone else's projects by adding features or fixing errors/bugs is one of the key things about being a hacker.

In this document, we will go over a few instructions and tips when it comes to contributing to open source software, which will include:

1. Forking a repository and syncing it
2. Making the changes/additions and issuing a pull request
3. Merging multiple commits into one
4. Resetting your forked repository when things go **BAD**

##Forking a repository and syncing it

Forking a repository has already been explained in [lab1-git](
https://github.com/mikeizbicki/ucr-cs100/tree/cs100-2014fall/assignments/lab/lab1-git), but to quickly summarize, here are the steps:

1. Go to the page of the repository you want to fork on github
2. Click the `fork` button on the top right-hand side of the page (Make sure you are signed in to your github account)
3. To get your forked repository onto your local machine, go to your terminal and enter:

`$ git clone https://github.com/YOUR_USERNAME/YOUR_FORK.git`

When you fork a repository, you get a copy of the current version of the original repository. But say the original owner makes changes to his/her own repository. As of now, your repository won't receive those updates automatically. It's good to regularly sync your forked repository with the original to avoid issues like trying to make changes that have already been made by the original owner or someone else.

To sync changes you make in a fork with the original repository, you need to configure a remote that points to the upstream repository in git. Here are the steps:

1. Open your terminal and go into your forked repository
2. List the current configured remote repository for your fork:

  `$ git remote -v`
3. Specify a new remote *upstream* repository that will be synced with the fork:

  `$ git remote add *upstream* https://github.com/ORIGINAL_OWNER/ORIGINAL_REPOSITORY.git`
4. Check that the new *upstream* repository you've specified for your fork:

  `$ git remove -v`

As you can see, `origin` refers to your forked repository, while `upstream` will refer to the original owner's repository.

5. To finally sync your forked repository, fetch the branches and their respective commits from the upstream repository.

  `$ git fetch upstream`

6. From here there are two methods through git which you can use: `git merge` and `git rebase`. The differences are explained on [stackoverflow](http://stackoverflow.com/questions/16666089/whats-the-difference-between-git-merge-and-git-rebase), but `git rebase` is generally what most developers prefer. So we'll use `git rebase` to sync our local forked repository with our *upstream*:

  `$ git rebase upstream/MASTER_BRANCH`

7. At this point, our local repository should be completely synced up. Now we just have to push these changes to our forked repository on github.

  `$ git push`

##Making changes and issuing a pull request


Now that your forked repository is all nice and synced up with the original repository, you can now make the changes/additions you wanted. To demonstrate this, say you wanted to change the `README.md` file from the original repository.  Here are the general steps:

1. Go to that `README.md` file in your forked repository, open it in an editor like vim, and make the changes that you wanted.
2. `$ git add README.md`
3. `$ git commit -m "SHORT MESSAGE DESCRIBING YOUR CHANGE"`
4. `$ git push`

  Now you are ready to issue a pull request. To do that, you need to go to your forked repository on github. You should see a message that says something like  "This branch is # commit(s) ahead of the original repository." This shows that the changes you made have been successfully pushed onto your forked repository on github. Next to this message are two links: **PullRequest** and **Compare**. If you click on compare, it will show side-by-side the changes you've made to the repository and how it compares with the original.

  If all of the changes you made are correct, press the big green button that says **Create pull request**. You'll be directed to a form where you fill out the title of your pull request and an optional comment section where you can describe the reason for your pull request in more detail. **MAKE SURE TO BE CLEAR AND CONCISE IN YOUR PULL REQUEST!!** In general, a one sentence summary of "what are the benefits of merging your pull request" is good to have in the title section. If you feel the need to explain your pull request in greater detail, then you can write that out in the comment section. 

##Merging multiple commits into one

Taking the `README.md` example mentioned earlier, say that you made a lot of changes at different times to that `README.md` file, and now you have a bunch of commits for that same file on your forked repository. It would be really annoying and tedious for the original owner of the `README.md` file to look at each commit individually when they've all made changes to the same file. That's where merging commits comes in!

To do this, we need to take advantage of the `git rebase -i` command.

Let's say that you've just made 3 small commits to the `README.md` file, and now want to merge them all into one. Here are the steps:

Go to your forked repository in your terminal and enter:

  `$ git rebase -i HEAD~X`

  where `X` is the number of latest commits that you want to merge. In our example, `X` would equal 3.

  `$ git rebase -i HEAD~3`

At this point, a editor should open up. It should look something like this.
```
pick 01d1124 Updated title of README.md
pick 6340aaa Added new section
pick ebfd367 Fixed grammar errors

# Rebase 01d1124..ebfd367 onto 01d1124
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
There are a few options available, but what we're interested in is the `squash` command. This will allow us to "squash" all of the commits we want into one commit. To do this, we just change the commit lines like so will do the trick.

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
# Changes to be commited:
#   (use "git reset HEAD <file>..." to unstage)
#       modified: README.md
#
```
At this point, Git allows you to modify the new commit's message based on the rest of the commits involved in the process. Anything that is not commented out will be the new commit message, so you can change it to once concise commit message. One you're done, you can save and quit the editor. If all worked correctly, you should see a dialogue like this:
```
Created commit ofc4eea: Updated title, added new section, and fixed grammar errors in README.md.
 4 files changed, 48 insertions(+), 12 deletions(-)
        Successfully rebased and updated refs/heads/master.
```
If all worked correctly, it means your commits have been successfully squashed. Once that's done, you need to force push this change onto your forked repository on github.

`$ git push -f`

##Resetting your forked repository when things go **BAD**
Say you've made a commit to your forked repository that had A LOT of changes from the previous commit. And you realize later that your latest commit actually broke the program. Or say that while you were trying to squash commits, you made a mistake, and now you have even more commits or you didn't merge the commits you wanted. It can get really tricky to try to solve these types of problems. Sometimes, things just don't turn out the way you expect them to, and you want to go back to an earlier commit where things were nice and working. That's where the `git reset --hard` command comes in.

`git reset` by itself resets the commit history, but not the files. With the `--hard` option the files in the repository are also reset. If you want to revert your whole repository to an older commit, here are the steps:

1. Go to your latest commit using `git checkout`.
2. Look up the commit number of the commit you want to revert to.
3. Enter this command:

  `$ git reset --hard OLD_COMMIT_NUMBER`
4. At this point, your local repository should now be reverted. Now you need to force push this change onto your repository on github.

  `$ git push -f`

**NOTE**: `git reset --hard` is a very powerful command and cannot be undone. If you'd like to keep the changes you've made just in case, you should branch off a copy of your changes before resetting. If you'd like to learn more about `git reset`, there's a great article that explains it [here](http://git-scm.com/blog/2011/07/11/reset.html).
