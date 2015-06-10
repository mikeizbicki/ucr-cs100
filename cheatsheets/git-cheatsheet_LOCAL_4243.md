Cheat Sheet
===========
###Git and GitHub

#####SETUP GIT

After installing Git, you can make modifications to customize the environment and identify yourself in it. 
You just need to make these changes once.

```
$ git config --global user.name [your username]
```
This command will set the username that will appear on your commit transactions.


```
$ git config --global user.email [email address]
```
This command will set the email of your commit transactions.


```
$ git config --list
```
Command to list all the settings of your Git, including username and email.


#####USING HELP

If you need help to use some Git command, you can always use the command `git help`. 
There are three ways to use it:
```
$ git help [command name]
$ git [command name] --help
$ man git-[command name]
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
With `git init`, you will create a new Git repository on the project that you are working on. 
This project can be a new one (that doesn’t have anything on it) or it can be a project that already exists but you want to use version control on it. 
You should run this command on the folder of your project.


```
$ git clone [url]
```
With `git clone`, you will download a copy of a Git project that already exists. 
For example, you can take a url from a GitHub project that you want to contribute to, and clone it. 
This will create a new folder with all the projects on it, in the current directory.


#####MAKE CHANGES

After creating a new repository, you can start doing your project. 
To keep the repository up to date, you have to commit the changes that you've made on your local machine.

```
$ git status
```
This command will list for you all the files that were modified since the last time you committed something, for example, you made some changes in a `main.cpp` file of your project. 
If you have not committed yet, the command `git status` will show it for you.


```
$ git add [file]
````
With the `git add` command, the files that you changed will be ready to commit.

```
$ git rm [file]
```
If you want to remove a file from your project, you also have to remove it from Git so you can commit your changes.


```
$ git diff
```
`git diff` will compare what is in your working directory with what is in your staging area (the things you changed, but have not used the command `git add` yet). 
The result tells you the changes you’ve made that you have not staged.


```
$ git commit -m [descriptive message]
```
You will use this command to commit the changes that you've made and staged. 
After using `git add` on the files that you want to add, you will use `git commit -m "..."` to commit it. 
The `-m` flag will set the commit message.


```
$ git commit
```
If you want to use the command `git commit` without the `-m` flag, the editor of your choice will be launched and you can type your commit message there. 
Your commit must have a message. 
If you don't do it, the commit will be aborted.


```
$ git tag [tag name]
```
The git tag command will give a name (tag) to the last commit that you made. 
This is helpful because you can access this commit later, even if you've already commit something else.


#####GROUP CHANGES
Name a series of commits and combine completed efforts. 

Using Git, you can work with multiple versions of the same project at the same time. 
This is called branching. 
Every project can have many branches (versions) and they can be completely different from each other. 
This is very useful when you want to add a new feature to a project that is already working, and not ruin it. 
You can just make another branch, work on your new feature in it, and when the feature is ready, you merge the new branch with the origin.

```
$ git branch
```
The command `git branch` will list every branch that your project has, and it will mark the branch that you are currently in with a `*` sign. 
The main branch (that every project has) is called `master`. 

```
$ git branch [branch-name]
```
Using `git branch` with a name as 3rd parameter will create a new branch. This branch will point to the spot on the project that you are at the moment. 
For example, If I call `git branch test` with the repository up-to-date on the `master` branch, my new branch (`test`) will point to the last commit of the `master` branch. 
This means that everything that the branch `master` has, the branch `test` will have as well.

```
$ git checkout [branch-name]
```
This command will switch from the branch that you are in to the one specified.

```
$ git checkout -b [branch-name]
```
You can use the `-b` flag to create the new branch and switch to it at the same time.

```
$ git merge [branch]
```
To merge branches, you will checkout to the branch that you want to add the modifications to. 
For example, now that we are done with the `test` branch, we want to merge it with the `master` branch, so we have to run `git checkout master` and then run `git merge test`. 
This will merge what is in the `test` branch with the `master` branch, but this command can create a conflict problem. 
The conflict will happen if we change the same file in different branches. 
For example, we made changes in the file `main.cpp` in the `test` branch. 
Then, we went back to the `master branch` and made more changes there, in the same `main.cpp` file. 
When you try to merge the branches, you will get an error message. 
To solve this problem you have to open the file that has the conflict and manually merge the different lines of code. 
The lines between `<<<<<<< HEAD` and `=======` are from the `master` branch, while the lines between `=======` and `>>>>>>> test` are from the `test` branch.


```
$ git branch -d [branch-name]
```
Command to delete a branch.


#####REVIEW HISTORY
Browse and inspect the history of the project.
```
$ git log
$ git log -p
$ git log -p -2
```
With `git log` command, you will have the list of the commits made in that repository in reverse chronological order. If you add the flag `-p`, the output will be a list of commits with the diff introduced in each one.
You can also limit the number of commits you want displayed with the flag `-[number]`, which will display the number of commits you want.


```
$ git diff [first-branch]...[second-branch]
```
The `git diff` command is used to see the difference between commits, branches, etc. 
For example, the `git diff test...master` will show the changes that occurred on the master branch since when the test branch was started off it.


#####SYNCHRONIZE CHANGES
Keep your local repository and your project on GitHub the same.

```
$ git push
```
With `git push`, you will send all the commits you've made in your local repository to GitHub.


```
$ git pull
```
  With `git pull`, you will update your local repository with what is in GitHub. 
For example, you are working on a team on the same project. 
When somebody changes the code and push it to GitHub, you will take those changes with the `git pull` command.


```
$ git push origin [tag name]
```
When you use the `git push` command, every commit is pushed to GitHub. 
But to push your tags you have to use the command `git push origin [tag name]` with the tag name. 
This will update the tags on GitHub. 

```
$ git push origin --tags
```
Using the `--tags` flag, you will push all tags to GitHub.

