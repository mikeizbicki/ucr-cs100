dvanced git, and some other stuff about git
   In this tutorial, you will learn about some small things that you should
    be familiar with, after you finish cs100.
    
   Some important things that we will cover in this tutorial includes:
   * git remote - making sure that you can pull from other forked copies, or the original copy, and push to other repos on github/other git version hosting website
   * git fetch - which is required to update your forked repository
   * git rebase - which allows you to do many things, but we will be explaining squashing in this tutorial
   * git reset - To change the HEAD back to a different point in time for the project.
   * git diff - allows you to check out the differences in your files between either branches or commits.
   * git blame - checking the authors on the files that you have in your repo
   * git stash - stashing away your changes before checking out something else, just incase you don't want to commit

#starting git
I will be assuming that you have completed the git lab for this course, and you have some general knowledge about how git works. You can use git init, git pull, git push, git checkout, git branch, and git tag. If you don't know, here is a basic rundown.

* git init - inits a repo inside the folder allowing for you to track changes
* git pull - pulls from the remote that you have set up, makes sure you have the most recent repository
* git push - pushes to the remote that you have set up, makes sure that your changes are saved online somewhere, or to a different location
* git checkout - allows you to checkout a branch, a tag, or a commit, when you checkout a tag or commit, you go into a detached HEAD state, more on this later.
* git branch - can either create a new branch, or list the branches that you have setup
* git tag - allows you to create a new tag, or list all the tags that you have setup.

Now to the juicier parts of git! :]

#git remote
git remote allows you to add remotes to control your repository from a variety of sources.
In this class, you should be constantly updating your repository with the professor's main repository.

To do that you will create a remote named `upstream`. We will first check which remotes you have with:

    git remote -v

This will show you a list of the remotes that you have currently set up.
To configure a new remote, you can use the command:

    git remote add <remote_name_for_upstream> <git_remote_URL>
    
If at any time, you messed up, you can remove remotes with:

    git remote rm <remote_name>

#git fetch
git fetch allows you to check the remotes that you have in your repository,
and allows you to update the repository with other remote values.
To complete this for your `ucr-cs100` repository, you can use the following command:

    git fetch <upstream_remote_name>
    
After you fetch the contents of the repository, you can try to merge it with your branch with the following command:
    
    git merge <upstream_remote_name>/<your_branch_name>
    
You should fix any merge conflicts if you have any. If you don't have any, then the merge should be completed.
This updates your branch with the remote repositories that you have just fetched the data from.

In a big group project, this is required, as there will be several versions floating around, and it's important to have the updated versions, as bugs can be squashed, and fixes will have been completed.

#git rebase
git rebase allows you to do many things, but the main one we will be talking about is squashing commits.
Squashing commits is preferred by most git repositories to make it easier to check the points where the files were changed. 
You can use this to find errors, and later fix them if you need to, or revert back to an older version to negate some changes.

You can use the command

    git rebase -i HEAD~<number_of_commits_you_go_back_by>

This should pull up the amount of commits from the HEAD pointer to the number of commits that you want to go back by.

It should pull up a window with "pick" proceeded by the commit numbers.
If you use "pick", you proceed to add that into the repository. 
If you use "squash" you can recombine those commits into a different commit in your repository. 
After you exit out of the window, git will automatically try to rebase your repository. 
You should solve any merge conflicts that you get, and when it finishes completely, you should be at a point in your project that has all the recombined commits.

#git reset
git reset allows you to revert commits back to the point in time that you wish to reset to.
If you accidently changed your repository, and added a bunch of empty commits with git rebase, then you can use git reset to revert the repo to the commit number of your choosing. The command is:

    git reset <commit-number> --hard
    
This resets the pointer back to the commit number that you wish to reset to.

##NOTE: THIS WILL RESET YOUR HEAD POINTER, AND YOU WILL LOSE YOUR WORK.
You should only do this if you really need to reset your repository back to it's original format.
 
 #git diff
 git diff allows you to check the differences between the branchs, or the commits.
 If you type it out automatically, you can checkout the differences between your last commit and the current changes that you have.
 You need to make sure that the two that you are comparing should be the same, so two branches, or two different commits.
 
 To use, type in the command:
 
    git diff [<branch_or_commit_name>] [<second_branch_or_commit>]
    
It can tell you the differences in the files that you have, or the files that you need to add in your next commit.
 
 #git blame 
 git blame is a cool little feature in git that allows you to see who wrote what in the repository. The command to use this feature is:
 
    git blame <filename>

This will pull up the contents of the file, along with the commit number that the line was changed in, as well as the person who changed it, and at what time it was changed at.

This is a cool little feature to let you know who changed what lines in the repository, and what time you changed the file at.

If you want to know who changed certain lines, you can use the -L flag to figure out who changed those lines. You can use the command:

    git blame -L <line-number><ending-linenumber> <filename>
    
This will tell you who edit the file within those line numbers.
 
 #git stash
 git stash is another little cool feature that allows you to save your changes without making any commits. You can git stash several times, and check it out as well.
 
 You can run a git status to check what changes you have on the project. This allows you run a git stash if you need to.
 
 To stash your changes without committing them, use:
 
    git stash

This will save your changes all the way to the previous commit. This allows you to modify or add anything that you might need prior to commiting your older changes.

To replace your changes you can use the following command:

    git stash pop
    
This pops the last change that you have onto your working directory. If you have more stashes, you can use a different method described below.

With more stashes, you can use:

    git stash list

This will allow you to check out the list of stashes that you have in a list.
To choose the one that you want to use, use:

    git stash apply <number-in-list>

When you apply the command, you will be able to reapply everything you have in that specific stash. This allows you to continue working on that portion of the project.

If you apply without putting a number, then you apply the most current one in the stash.

---------------------------
#more infomation
If you need more information on git, there are two amazing websites that you can checkout.

[git-scm](http://git-scm.com/) - 
This website is really helpful for other advanced techniques, and gives plenty of examples to help you with more flags and other commands.

[atlassian](https://www.atlassian.com/git/tutorials/setting-up-a-repository) - 
This guide is very helpful for learning how to set up the repo, and making commits.
It does belong to a private git hosting website, so some of the git remotes might be pointing to that website.
