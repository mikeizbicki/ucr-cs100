#advanced git: the introductory tutorial
   After the end of this tutorial, you should know how to add a remote, fetch the contents a remote, reset your HEAD pointer to a different commit, run a git blame, and git stash some changes that you do not want to commit just yet.
   
   This is an introductory tutorial, so the goal is to get you acquainted with some of the more advanced features of git. 
If you would like a complete run down of how to use a certain command, you can click on the command under the section `Topics covered:`, and it will link you to the man page of that specific command on the internet.
   
   `<>` indicates a variable at any time in this tutorial.

#topics covered:
   * [git remote](http://git-scm.com/docs/git-remote)
   * [git fetch](http://git-scm.com/docs/git-fetch)
   * [git rebase](http://git-scm.com/docs/git-rebase)
   * [git reset](http://git-scm.com/docs/git-reset)
   * [git diff](http://git-scm.com/docs/git-diff)
   * [git blame](http://git-scm.com/docs/git-blame)
   * [git stash](http://git-scm.com/docs/git-stash)

#starting git
I will be assuming that you have completed the git lab for this course, and you have some general knowledge about how git works. 
You can use `git init`, `git pull`, `git push`, `git checkout`, `git branch`, and `git tag`. 
If you don't know, here is a basic rundown.

* `git init` - inits a repo inside the folder allowing for you to track changes
* `git pull` - pulls from the remote that you designate from
* `git push` - pushes to the remote that you designate to
* `git checkout` - allows you to checkout a branch, a tag, or a commit
* `git branch` - create a new branch, or list the branches that you have setup
* `git tag` - create a new tag, or list all the tags that you have setup.

Now to the juicier parts of git! :]

#git remote
`git remote` lets you manage a set of tracked repositories. 
These tracked repositories are labeled as 'remotes'.

In the workplace, you might have to update your repository with the original repository to get the most current source code and other files that you are working with.

To update your repository, create a remote named `upstream`. 
Then fetch the `upstream` for any changes to the tracked repository. 
Finally, merge the contents of that repository to your forked repository, which updates your forked repository with the main tracked repository

We will first check which remotes you have with:

    git remote -v

This will show you a list of the remotes that you have currently set up.
The `-v` in the code stands for `verbose`, which will show you the name and the URL of the remote in a list.

To configure a new remote, you can use the command:

    git remote add <remote_name> <git_remote_URL>
    
In this case, you can change `remote_name` to anything you want. 
we chose to put down my `remote_name` as `upstream`, because we want to update my forked repository with the original repository that I forked from.

The `git_remote_url` is the remote link that you can obtain from the Github repository page.

If at any time, you messed up, you can remove remotes with:

    git remote rm <remote_name>

#git fetch
`git fetch` downloads all the objects and references from a specified repository. 
This will download every branch and tag in the specified repository, unless you choose to not download branches and/or tags.

To complete this for your repository, you can use the following command:

    git fetch <remote_name>

If we want to fetch from Mike Izbicki's repository, then we would configure a remote to his repository labeled `upstream` and run `git fetch upstream`.
This will pull all the current files that he has in his repository.
    
If you want to combine all his files with your repository, you can try to merge it with your branch with the following command:
    
    git merge <fetched_remote_name>/<your_branch_name>
    
`fetched_remote_name` is the remote that you just fetched everything from.

`your_branch_name` is the branch that you would like to merge all the files that you just fetched from `fetched_remote_name` into the branch on your current repository.
    
You should fix any merge conflicts if you have any. 
If you don't have any, then the merge should automatically complete.
This updates your branch with the remote repositories that you have just fetched the data from.

In a big group project, several versions of the same repository can be floating around. 
Therefore, it's important to have the updated versions of the repository, as bugs can be squashed, and fixes will have been completed.

#git rebase
`git rebase` allows you to do many things, but the main feature we will cover in this tutorial is squashing commits.
Squashing commits cleans up your commit history. 
Instead of having 15 commits, you can have 3 or 4 commits that focus more on features that were added or removed.
This allows you to find the point in time where you added or removed major portions of your code, and fix them if you need to, or revert back to an older version to negate some changes.

You can use the command

    git rebase -i HEAD~<number_of_commits>
    
`-i` pulls up interactive mode, which allows you to choose the commits that you want in a window. 
It allows for picking, squashing, and several other features.

`HEAD` is the pointer that your repository is currently at. 
You can think of this like the current pointer in a list that points to the item in the list that you are currently working with.

`number_of_commits` is the number of commits that you wish to go back by. 
If you have 10 commits that you want to squash, you can type in 10, and git will start at the head, and traverse back 10 commits.


A window in your preferred text-editor should open with "pick" proceeded by the commit numbers.
If you use "pick", you proceed to add that particular commit into the repository. 
If you use "squash", you proceed to merge that commit with the previous commit where you put squash.
When you are doing picking and squashing the commits, exit from the text-editor.

After you exit out of the window, git will automatically try to rebase your repository. 
You should solve any merge conflicts that you get, and when it finishes completely, your project should reflect the commits that you have picked and squashed.

#git reset
`git reset` reverses the HEAD pointer to the specified commit or state.

If you accidently changed your repository, and added a bunch of empty commits with git rebase, then you can use git reset to revert the repo to the commit number of your choosing. The command is:

    git reset <mode> <commit>

`commit` is the commit number that you wish to revert back to.

There are two `mode` values that are pretty important to know.
The first one is `--hard`. 
This resets the pointer back to the commit number that you wish to reset to.

##NOTE: THIS WILL RESET YOUR HEAD POINTER, AND YOU WILL LOSE YOUR WORK.
You should only do this if you really need to reset your repository back to it's original format.

The second one is `--soft`. This mode will reset your repository to the state at that time, and keeps your changes as `changes to be committed`.

 
 #git diff
 `git diff` allows you to check the differences between the branches or commits.
 If you type it out automatically, you can checkout the differences between your last commit and the current changes that you have.
 You need to make sure that the two that you are comparing should be the same, so two branches, or two different commits.
 
 To use, type in the command:
 
    git diff <branch_or_commit_name> <second_branch_or_commit>
    
It can tell you the differences in the files that you have, or the files that you need to add in your next commit.
 
 #git blame 
 `git blame` is a cool little feature in git that allows you to see who wrote what in the repository. The command to use this feature is:
 
    git blame <filename>

`filename` is the file that you would like to run `git blame` on.

This will pull up the contents of the file, along with the commit number that the line was changed in, as well as the person who changed it, and at what time it was changed at.

If you want to know who changed certain lines, you can use the -L flag to figure out who changed those lines.
You can use the command:

    git blame -L <line-number><ending-linenumber> <filename>
 
`line-number` is the line you wish to start at.

`ending-linenumber` is the line you wish to end at.

This will tell you who edit the file within those line numbers on the command line instead of pulling up a text-editor.
 
 #git stash
`git stash` is another cool feature that allows you to save your changes without making any commits. 
You can `git stash` several times, and later apply those changes when you see fit.
 
 You can run a `git status` to check what changes you have on the project. 
This allows you run a `git stash` if you need to.
 
 To stash your changes without committing them, use:
 
    git stash

This will save your changes all the way back to the previous commit. 
This allows you to modify or add anything that you might need prior to committing your older changes.

To replace your changes you can use the following command:

    git stash pop
    
This pops the last change that you have onto your working directory. 
If you have more stashes, you can use a different method described below.

With more stashes, you can use:

    git stash list

This will allow you to check out the list of stashes that you have in a list.
To choose the one that you want to use, use:

    git stash apply <number-in-list>

`number-in-list` should be the number in the stash list that you would like to apply the changes that you have stashed. 
This allows you to continue working on that portion of the project.

If you apply without putting a number, then you apply the most current one in the stash.

---------------------------
#more information
If you need more information on git, here are some resources that you can checkout.

[git-scm](http://git-scm.com/) - 
This website is really helpful for other advanced techniques, and gives plenty of examples to help you with more flags and other commands. 
All the man pages are on this website.

[atlassian](https://www.atlassian.com/git/tutorials/setting-up-a-repository) - 
This guide is very helpful for learning how to set up the repo, and making commits.
It does belong to a private git hosting website, so some of the git remotes will be pointing to that website.

[git for ages 4 and up](https://www.youtube.com/watch?v=1ffBJ4sVUb4) -
This was a really handy tutorial video on YouTube which helped me out a lot. 
He goes over a lot of git features, but the video is about 1 1/2 hours long. 
It's great if you have some free time, and you want to learn more about git.

