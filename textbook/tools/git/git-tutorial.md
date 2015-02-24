Welcome all, for those of you who are reading this you may have heard of a program that is 
called git that is used to manage the source code of various projects.

Note: All text with <TEXT> means to replace TEXT with the proper text/path/name
For these examples we will be using github.com, which you can create an account for free at.

* Usage:
  * Section A: Git basics
  * Section B: Git remote
  * Section G: Git push
  * Section C: Git fetch
  * Section D: Git merge
  * Section E: Git pull
  * Section F: Git rebase
  * Section H: Git workflows 


###Section A: Git basics
After git is installed you should setup a couple of setting

	$ git config --global user.name "<your name>"
	$ git config --global user.email "<your email>"

Try not to think of git as a complex program but as many simple programs 
rolled into one, each with there own purpose. Almost all of Git's commands 
are prefixed by.... you guessed it, git.

So to start of lets get an already created git repository or "repo".

	$ git clone https://github.com/mikeizbicki/ucr-cs100.git

This shell command means invoke the git command and create a git repo called ucr-cs100
using the information from the url to grab the data. This is the most basic of commands.
 Optionally you can specify the directory to clone into is called by adding it after the URL.
	
	$ git clone https://github.com/mikeizbicki/ucr-cs100.git CS100

Now lets say you whant to create a new git repo from scratch. We create a 
new clean git directory by first creating a empty directory. After the directory 
is created we will then initialize the repo.

	$ mkdir <name>
	$ cd <name>
	$ git init

Now that the repo is initialized we can add some files to repository.  We add files to git 
repository by first creating a file then using 'git add \<file name\>'. Here I am telling git to 
include all the files the are in the current working directory, optionally you can individually 
specify which files to include.
	
	$ touch README
	$ git add .
		Or
	$ git add <path_to_file_in_git_repo>

Once the files are added we can then 'commit' them to the repo. 'Committing' means that 
we want to include that file in the repository and track the changes that are made to that file. 
Commits are the saved state of the repo. Commits take a message that allows them to be looked over 
with a title and message so that users can tell what has happened.  If 'git commit' is used
 without passing the -m flag, or message flag, the default text editor will be brought up to 
prepare a message for the commit. 

	$ git commit
	or
	$ git commit -m'<message>'

Note: If a branch hasnt been created prior to first commiting git will create one called the
'master' branch

##Uploading and downloading changes
Now that we have created the git repository and commited some files we probaly want to upload 
or 'push' the changes to a semi-central location github.com. Assuming that you used github.com 
to create the repoistory to push to and is the repo is called GitGuides then the URL I would use is
https://github.com/mikeizbicki/ucr-cs100.git 
We might also want to download changes that others have made. This is called 'pulling'

##SECTION ?: Git Remote
First to push to a location you will have to add a remote,
a place to download/upload changes from. To view the current remotes for the repo issues the "git remote"
command

	$ git remote


Notice their is not much information in this output. Just the names of the remotes. To get a little 
more detail about the remote use the -v flag. On our newly initialized repo there is no remotes to display. 

Now Lets add a remote so that we can push to our remote reposity. This can be done by telling "git remote" 
to add a remote. we do this by passing the 'add' argument to git remote. After that argument we pass the 
name of the remote to add and the url to associate with
that remote name. git remote add \<remote name\> \<url\>

	$ git remote add origin https://github.com/<your username>/ucr-cs100.git

Lets view our remote again. 
	
	$ git remote

This doesnt give us much information, just the names. To get a little more detail about the remote use
 the -v flag

	$ git remote -v

This gives both the remote names as well as their push/push url associated with that remote. Why is their
a seprate url for both push and pull. That is because each can be set seperate for a remote.

###SECTION ?: Git push

Now that our repository has a remote we can now push the changes to github using 'git push'
	
	$ git push <remote> <branch>
	ours would be
	$ git push origin master

This does not set up tracking of the remote branch though. To do that you can set the remote tracking
branch during the push

	$ git push -u origin master

Now you may be asking why you didnt have to add the remote when you cloned the first repo. Well when you clone 
a repository using git clone, a tracking branch is set up automatically called master that tracks origin/master.

There you go, now you can get a already created repo, create a repo yourself and you can push changes to the repo. 
You may be wondering, 'How do I get changes from others that commited on the project'. Since that can be a little more 
tricky it will be covered in the next section

###SECTION D: Git fetch and Git Pull
Now that you can create, and push changes to a git repo its time to learn how create a branch and grab external changes. 
Assuming that you have been fallowing the guide up to this point, you have commited to your non-cloned repo, you have 
added a remote and set up a traking branch. I will now show how to pull in changes that others have commited while you
were away. To do this set up a remote to the repository that you wish to update from. This is ussualy called the upstream
repo.

	git remote add upstream https://github.com/mikeizbicki/ucr-cs100.git

So no we have two remotes. One to our own repository and one to the original repository. Lets get a copy of the upstream 
version but let's not make any changes to ours just yet. This is done using the 'fetch' git command. git fetch \<repo\>

	$ git fetch upstream 

Note that the tags for a repository are not fetch with this command. The need to be explicitly fetched with the --tags
or -t option

	$ git fetch -t upstream
	
	
