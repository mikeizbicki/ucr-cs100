Git Cheat Sheet
===========

#####CONFIGURING GIT

After installing Git, you can make modifications to customize the environment and identify yourself in it.
You just need to make these changes once.

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

If you need help to use some Git command, you can always use the command `git help`.
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
Create a new Git repository in the current directory.
This directory can be empty or contain an existing project.
If the directory contains files, you will have to run `git add` and `git commit` before they are added to the repo.


```
$ git clone <url>
```
Downloads a copy of a Git repo that already exists.
For example, you can take a url from a GitHub project that you want to contribute to, and clone it.
This will create a new folder with the same name as the project in the current directory.


#####MAKE CHANGES

After creating a new repository, you can start doing your project.
To keep the repository up to date, you have to commit the changes that you've made on your local machine.

```
$ git add <files>
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
This is a more detailed version of `git status`.
It compares what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet).
It outputs all the lines on each file that has changed.


```
$ git commit -m "descriptive message"
```
Creates a new commit in your repo with all the changes in your staging area.
You should run this command after using `git add` on the files that you want to add/modify.
The `-m` flag lets you set the commit message from the command line.


```
$ git commit
```
Without the `-m` flag, Git will launch an editor so you can type your commit message.
Use this version of the command if you've made lots of changes, and so have a long commit message.
All commit must have a message.
If you don't add one, the commit will be aborted.


#####GROUP CHANGES

You can work with multiple versions of your project at the same time.
Each version is called a branch.
A repo can have many branches, and each branch can be completely different.

Branches let many different developers work the project without interfering with each other.
Branches are used when adding new features to a project.
You make a new branch for your feature, and commit all your changes to that branch.
When the feature is ready, you merge this feature branch with master.

```
$ git branch
```
List every branch that your project has.
Your "current branch" is marked with a `*`.
Any commit you make will be applied to your current branch.

```
$ git branch <branchname>
```
Create a new branch called `<branchname>`.
This branch's head will point to the current commit you have checked out.
For example, If I call `git branch test` with the repository up-to-date on the `master` branch, my new branch (`test`) will point to the last commit of the `master` branch.
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
Lists the commits made in the current branch in reverse chronological order.
If you add the flag `-p`, the output will be a list of commits with the diff introduced in each one.
You can also limit the number of commits you want displayed with the flag `-number`.


```
$ git diff <branch1> <branch2>
```
Shows all the lines of all the files that have changed between `<branch1>` and `<branch2>`.


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
Update your local repository's `<branch>` with the commits from `<remote>`.
This is useful when collaborating with others.
If Alice recently pushed some changes to your shared repo on GitHub, then you will need to run `git pull` to update your local repo with those changes.


```
$ git push [<remote> [<tag>]]
```
Pushes a tag (instead of a branch) to the remote repo.
You must do this in order to share your tagged commits with others.

```
$ git push [<remote>] --tags
```
Pushes all tags to the remote repo.

