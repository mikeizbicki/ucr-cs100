Git Cheat Sheet
===========

#####CONFIGURING GIT

<<<<<<< HEAD
<<<<<<< HEAD
After installing Git, you can make modifications to customize the environment and identify yourself in it. 
You just need to make these changes once.
=======
Git has a number of global configuration settings. You just need to make these changes once, and they will be applied anytime you use Git.
>>>>>>> dac379d... Update git-cheatsheet.md
=======
After installing Git, you can make modifications to customize the environment and identify yourself in it.
You just need to make these changes once.
>>>>>>> upstream/2015spring

```
$ git config --global user.name "firstname lastname"
```
Sets the name that will appear on your commit transactions.
You should set this value to your full proper name.


```
$ git config --global user.email "email@domain"
```
Set the email that will appear on your commit transactions.


```
$ git config --list
```
Displays all of your globally configured settings, including name and email.


#####USING HELP

<<<<<<< HEAD
<<<<<<< HEAD
If you need help to use some Git command, you can always use the command `git help`. 
=======
If you need help to use some Git command, you can always use the command `git help`.
>>>>>>> dac379d... Update git-cheatsheet.md
=======
If you need help to use some Git command, you can always use the command `git help`.
>>>>>>> upstream/2015spring
There are three ways to use it:
```
$ git help <command>
$ git <command> --help
$ man git <command>
```
For example, if you need some help with the config command, you can use:
```
$ git config --help
```


#####CREATE A NEW REPOSITORY

You can create a Git project using two different methods: By creating a new repository in an existing local project or directory or by cloning an existing remote repository.

```
$ git init
```
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
With `git init`, you will create a new Git repository on the project that you are working on. 
This project can be a new one (that doesn’t have anything on it) or it can be a project that already exists but you want to use version control on it. 
You should run this command on the folder of your project.
=======
With `git init`, you will create a new Git repository on the project that you are working on. This project can be a new one (that doesn’t have anything on it) or it can be a project that already exists but you want to use version control on it. You should run this command from the root folder of your project.
>>>>>>> dac379d... Update git-cheatsheet.md
=======
Create a new Git repository in the current directory.
This directory can be empty or contain an existing project.
If the directory contains files, you will have to run `git add` and `git commit` before they are added to the repo.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Create a new Git repository in the current directory.
This directory can be empty or contain an existing project.
If the directory contains files, you will have to run `git add` and `git commit` before they are added to the repo.
>>>>>>> upstream/2015spring


```
$ git clone <url>
```
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
With `git clone`, you will download a copy of a Git project that already exists. 
For example, you can take a url from a GitHub project that you want to contribute to, and clone it. 
This will create a new folder with all the projects on it, in the current directory.
=======
With `git clone`, you will download a copy of a Git repo that already exists. For example, you can take a url from a GitHub project that you want to contribute to, and clone it. This will create a new folder with all the projects on it, in the current directory.
>>>>>>> dac379d... Update git-cheatsheet.md
=======
Downloads a copy of a Git repo that already exists.
For example, you can take a url from a GitHub project that you want to contribute to, and clone it.
This will create a new folder with the same name as the project in the current directory.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Downloads a copy of a Git repo that already exists.
For example, you can take a url from a GitHub project that you want to contribute to, and clone it.
This will create a new folder with the same name as the project in the current directory.
>>>>>>> upstream/2015spring


#####MAKE CHANGES

<<<<<<< HEAD
After creating a new repository, you can start doing your project. 
To keep the repository up to date, you have to commit the changes that you've made on your local machine.

```
<<<<<<< HEAD
<<<<<<< HEAD
$ git status
```
This command will list for you all the files that were modified since the last time you committed something, for example, you made some changes in a `main.cpp` file of your project. 
If you have not committed yet, the command `git status` will show it for you.


```
=======
>>>>>>> dac379d... Update git-cheatsheet.md
$ git add [file]
=======
$ git add <files>
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
After creating a new repository, you can start doing your project.
To keep the repository up to date, you have to commit the changes that you've made on your local machine.

```
$ git add <files>
>>>>>>> upstream/2015spring
````
Adds all `<files>` to the "staging area".
You must later run `git commit` to add these changes into the repo.
You can add as many files as you want in a single command.
If you add a directory, all files within the directory will be added.
You should only ever run `git add` on text files, never on binary files.

```
$ git rm <files>
```
Delete all `<files>` from the harddrive (if they exist) and removes them from the staging area.
You must later run `git commit` to add this change to the repo.

```
$ git status
```
Lists all the files that were modified since your last commit.
You should run this everytime before running `git commit` to make sure you're committing the right files.


```
$ git diff
```
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
`git diff` will compare what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet). 
The result tells you the changes you’ve made that you have not staged.
=======
This is a more detailed version of `git status`.  It will compare what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet). It outputs all the lines on each file that has changed.
=======
This is a more detailed version of `git status`.
It compares what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet).
It outputs all the lines on each file that has changed.
>>>>>>> d0d6fc6... Update git-cheatsheet.md

>>>>>>> dac379d... Update git-cheatsheet.md
=======
This is a more detailed version of `git status`.
It compares what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet).
It outputs all the lines on each file that has changed.
>>>>>>> upstream/2015spring


```
$ git commit -m "descriptive message"
```
<<<<<<< HEAD
<<<<<<< HEAD
You will use this command to commit the changes that you've made and staged. 
After using `git add` on the files that you want to add, you will use `git commit -m "..."` to commit it. 
The `-m` flag will set the commit message.
=======
Creates a new commit in your repo with all the changes in your staging area. 
You should run this command after using `git add` on the files that you want to add/modify.
The `-m` flag lets you set the commit message from the command line.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Creates a new commit in your repo with all the changes in your staging area.
You should run this command after using `git add` on the files that you want to add/modify.
The `-m` flag lets you set the commit message from the command line.
>>>>>>> upstream/2015spring


```
$ git commit
```
<<<<<<< HEAD
<<<<<<< HEAD
If you want to use the command `git commit` without the `-m` flag, the editor of your choice will be launched and you can type your commit message there. 
Your commit must have a message. 
If you don't do it, the commit will be aborted.
=======
=======
>>>>>>> upstream/2015spring
Without the `-m` flag, Git will launch an editor so you can type your commit message.
Use this version of the command if you've made lots of changes, and so have a long commit message.
All commit must have a message.
If you don't add one, the commit will be aborted.
<<<<<<< HEAD
>>>>>>> d0d6fc6... Update git-cheatsheet.md


<<<<<<< HEAD
```
$ git tag [tag name]
```
The git tag command will give a name (tag) to the last commit that you made. 
This is helpful because you can access this commit later, even if you've already commit something else.
=======
>>>>>>> dac379d... Update git-cheatsheet.md
=======
>>>>>>> upstream/2015spring


#####GROUP CHANGES

<<<<<<< HEAD
<<<<<<< HEAD
Using Git, you can work with multiple versions of the same project at the same time. 
This is called branching. 
Every project can have many branches (versions) and they can be completely different from each other. 
This is very useful when you want to add a new feature to a project that is already working, and not ruin it. 
You can just make another branch, work on your new feature in it, and when the feature is ready, you merge the new branch with the origin.
=======

=======
>>>>>>> upstream/2015spring
You can work with multiple versions of your project at the same time.
Each version is called a branch.
A repo can have many branches, and each branch can be completely different.

Branches let many different developers work the project without interfering with each other.
Branches are used when adding new features to a project.
You make a new branch for your feature, and commit all your changes to that branch.
When the feature is ready, you merge this feature branch with master.
<<<<<<< HEAD
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
>>>>>>> upstream/2015spring

```
$ git branch
```
<<<<<<< HEAD
<<<<<<< HEAD
The command `git branch` will list every branch that your project has, and it will mark the branch that you are currently in with a `*` sign. 
The main branch (that every project has) is called `master`. 
=======
List every branch that your project has.
Your "current branch" is marked with a `*`.
Any commit you make will be applied to your current branch.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
List every branch that your project has.
Your "current branch" is marked with a `*`.
Any commit you make will be applied to your current branch.
>>>>>>> upstream/2015spring

```
$ git branch <branchname>
```
<<<<<<< HEAD
<<<<<<< HEAD
Using `git branch` with a name as 3rd parameter will create a new branch. This branch will point to the spot on the project that you are at the moment. 
For example, If I call `git branch test` with the repository up-to-date on the `master` branch, my new branch (`test`) will point to the last commit of the `master` branch. 
=======
Create a new branch called `<branchname>`.
This branch's head will point to the current commit you have checked out.
For example, If I call `git branch test` with the repository up-to-date on the `master` branch, my new branch (`test`) will point to the last commit of the `master` branch.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Create a new branch called `<branchname>`.
This branch's head will point to the current commit you have checked out.
For example, If I call `git branch test` with the repository up-to-date on the `master` branch, my new branch (`test`) will point to the last commit of the `master` branch.
>>>>>>> upstream/2015spring
This means that everything that the branch `master` has, the branch `test` will have as well.

```
$ git checkout <branchname>
```
Changes your current branch to `<branchname>`.

```
$ git checkout -b <branchname>
```
Creates a new branch and switches to it in one command.
This is equivalent to calling `git branch <branchname>` followed by `git checkout <branchname>`.

```
$ git merge <branchname>
```
<<<<<<< HEAD
<<<<<<< HEAD
To merge branches, you will checkout to the branch that you want to add the modifications to. 
For example, now that we are done with the `test` branch, we want to merge it with the `master` branch, so we have to run `git checkout master` and then run `git merge test`. 
This will merge what is in the `test` branch with the `master` branch, but this command can create a conflict problem. 
The conflict will happen if we change the same file in different branches. 
For example, we made changes in the file `main.cpp` in the `test` branch. 
Then, we went back to the `master branch` and made more changes there, in the same `main.cpp` file. 
When you try to merge the branches, you will get an error message. 
To solve this problem you have to open the file that has the conflict and manually merge the different lines of code. 
The lines between `<<<<<<< HEAD` and `=======` are from the `master` branch, while the lines between `=======` and `>>>>>>> test` are from the `test` branch.
=======
=======
>>>>>>> upstream/2015spring
Merges all the commits in `<branchname>` into your current branch.
For example, now that I am done with the `test` branch, I want to merge it with the `master` branch.
So I run `git checkout master`; then `git merge test`.
This adds the changes from the `test` branch into the `master` branch.

Sometimes this creates a "merge conflict" if we change the same file in both branches.
For example, I made changes in the file `main.cpp` in the `test` branch.
Then, I went back to the `master` branch and also changed `main.cpp` there.
When you try to merge the branches, you will get an error message saying there was a merge conflict.
To procede with the merge, you have to open the conflicting file that and manually merge the code.
The lines between `<<<<<<< HEAD` and `=======` are from the current branch,
while the lines between `=======` and `>>>>>>> test` are from the `test` branch.
Select which version you want and delete the rest.
<<<<<<< HEAD
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
>>>>>>> upstream/2015spring


```
$ git branch -d <branchname>
```
Deletes `<branchname>` from your local machine only.

```
$ git tag <tagname>
```
Assigns the name `<tagname>` to your currently checkedout commit.
Unlike a branch, a tag always stays attached to the same commit.
This makes tags useful for releasing versions.

#####REVIEW HISTORY
Browse and inspect the history of the project.
```
$ git log
$ git log -p
$ git log -p -2
```
<<<<<<< HEAD
<<<<<<< HEAD
With `git log` command, you will have the list of the commits made in that repository in reverse chronological order. If you add the flag `-p`, the output will be a list of commits with the diff introduced in each one.
You can also limit the number of commits you want displayed with the flag `-[number]`, which will display the number of commits you want.
=======
Lists the commits made in the current branch in reverse chronological order.
If you add the flag `-p`, the output will be a list of commits with the diff introduced in each one.
You can also limit the number of commits you want displayed with the flag `-number`.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Lists the commits made in the current branch in reverse chronological order.
If you add the flag `-p`, the output will be a list of commits with the diff introduced in each one.
You can also limit the number of commits you want displayed with the flag `-number`.
>>>>>>> upstream/2015spring


```
$ git diff <branch1> <branch2>
```
<<<<<<< HEAD
<<<<<<< HEAD
The `git diff` command is used to see the difference between commits, branches, etc. 
For example, the `git diff test...master` will show the changes that occurred on the master branch since when the test branch was started off it.
=======
Shows all the lines of all the files that have changed between `<branch1>` and `<branch2>`.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Shows all the lines of all the files that have changed between `<branch1>` and `<branch2>`.
>>>>>>> upstream/2015spring


#####SYNCHRONIZE CHANGES
Once you've committed your changes to your local repo, you should send them to a remote repository like GitHub.
This gives you a backup in case your computer dies, a way to work on multiple computers, and a way to communicate

```
$ git push [<remote> [<branch>]]
```
Update the `<remote>` repo with all the commits you've added to `<branch>`.
Both the `<remote>` and `<branch>` parameters are optional.
If they are ommitted, then Git will default to pushing to every location you've previously pushed to.


```
$ git pull [<remote> [<branch>]]
```
<<<<<<< HEAD
<<<<<<< HEAD
  With `git pull`, you will update your local repository with what is in GitHub. 
For example, you are working on a team on the same project. 
When somebody changes the code and push it to GitHub, you will take those changes with the `git pull` command.
=======
Update your local repository's `<branch>` with the commits from `<remote>`.
This is useful when collaborating with others.
If Alice recently pushed some changes to your shared repo on GitHub, then you will need to run `git pull` to update your local repo with those changes.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Update your local repository's `<branch>` with the commits from `<remote>`.
This is useful when collaborating with others.
If Alice recently pushed some changes to your shared repo on GitHub, then you will need to run `git pull` to update your local repo with those changes.
>>>>>>> upstream/2015spring


```
$ git push [<remote> [<tag>]]
```
<<<<<<< HEAD
<<<<<<< HEAD
When you use the `git push` command, every commit is pushed to GitHub. 
But to push your tags you have to use the command `git push origin [tag name]` with the tag name. 
This will update the tags on GitHub. 
=======
Pushes a tag (instead of a branch) to the remote repo.
You must do this in order to share your tagged commits with others.
>>>>>>> d0d6fc6... Update git-cheatsheet.md
=======
Pushes a tag (instead of a branch) to the remote repo.
You must do this in order to share your tagged commits with others.
>>>>>>> upstream/2015spring

```
$ git push [<remote>] --tags
```
Pushes all tags to the remote repo.

