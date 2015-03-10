Welcome all, for those of you who are reading this you may have heard of a program that is 
called git that is used to manage the source code of various projects.

Note: All text with <TEXT> means to replace TEXT with the proper text/path/name
For these examples we will be using github.com, which you can create an account for free at.

* Usage:
  * Git remote
  * Git push
  * Git fetch
  * Git merge
  * Git pull
  * Git rebase
  * Git workflows 


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

###SECTION D: Git fetch
Now that you can create, and push changes to a git repo its time to learn how create a branch and grab external changes. 
Assuming that you have been fallowing the guide up to this point, you have commited to your non-cloned repo, you have 
added a remote and set up a traking branch. I will now show how to pull in changes that others have commited while you
were away. To do this set up a remote to the repository that you wish to update from. In our case we update from the 
classes main repo. This is ussualy called the upstream repo but can be called anything you like.

	git remote add <remote name> <url>
	git remote add upstream https://github.com/mikeizbicki/ucr-cs100.git

So no we have two remotes. One to our own repository and one to the original repository. Lets get a copy of the upstream 
version but let's not make any changes to ours just yet. This is done using the 'fetch' git command. 

	git fetch
 
Wait a minute this did't fetch our upstream remote that grabbed the remote named origin. If there is no remote specified 
the remote origin will be used as a default, unless it is configued differently. We dont need to do that, lets just 
specify we want that remote fetched

	git fetch <remote>
	git fetch upstream

Right now were on the master branch that we created. Lets get onto the 2015winter branch. Since this was a barren repo
lets checkout out our remote branch 2015winter. To verify the branch is there first run git branch with the -r (remote)
option passed

	git branch -r

The branch is there

	git checkout origin/2015winter

You should see something similar to this. Don't be alarmed its just telling us that we are not on a branch
and the changes we make wont be saved unless we create one from this point. 

>Note: checking out 'origin/2015winter'.
>
>You are in 'detached HEAD' state. You can look around, make experimental
>changes and commit them, and you can discard any commits you make in this
>state without impacting any branches by performing another checkout.
>
>If you want to create a new branch to retain commits you create, you may
>do so (now or later) by using -b with the checkout command again. Example:
>
>  git checkout -b new_branch_name
>
>HEAD is now at e3a3a63... Merge branch '2015winter' of https://github.com/mikeizbicki/ucr-cs100 into 2015winter

Lets go ahead and do it the little checkout message is preciesly the command we will use to create out local branch.

	git checkout -b 2015winter

###SECTION ?: Git merge
Now that you know how to use fetch to get remote branches into you repo lets update our local branch. 
Before you update the local branch its a good idea to check for changes make upstream against your 
own branch. To do that we will use git log again, this time passing a revision instead of a single
brach. This will give us the difference in commits, if there is no difference there will be
no commits to display.
	
	git log <branch name>..<branch name>
	where <branch name> also be a <remote/branch>

	git log 2015winter..upstream/2015winter

Okay so now we know that there are commit differences so lets check them out visually. We can use git diff for this

	git diff <branch name> <branch name>
	
	git log 2015winter upstream/2015winter

Depending on how many commit differences there the could be a lot of files changes. This can give you an idea of the state
of changes against your current repo. I think its time to merge this upstream branch into our. Lets play it safe on work on
a temporary branch and a temporary 2015winterbranch
	
	git checkout -b 2015winter-base
	git checkout 2015winter
	git checkout -b 2015winter-tmp

Lets merge out upstream into the -tmp branch(we are currently on it)
	
	git merge <branch name>
	git merge upstream/2015winter

Edit the merge commit so the branch name reflects the branch you wanted to merge into, 2015winter-base.
This merge finishes without any problems. lete go ahead and merge it into our 2015winter-base branch.
This merge resolves as a fast forward and there is nothing to do. Thats no fun though, so lets create a problem.
Delete the -base and -tmp branches and recreate them. Run git diff again and modify something that has a change 
in both. Once that is done commit that that change. This time we should have a problem when we merge.

	git merge upstream/2015winter

You should get a message similar to

>Auto-merging README.md
>CONFLICT (content): Merge conflict in README.md
>Automatic merge failed; fix conflicts and then commit the result.

Last time you saw a merge conflict you dealt with it manually this time lets use some tools to help us along.

###Section ?: Git mergetool

	
With our repository waiting to have the merge conflct fixed we can run git mergetool. This starts a test editor
to help deal with the changes. 
	
	git mergetool

>This message is displayed because 'merge.tool' is not configured.
See 'git mergetool --tool-help' or 'git help config' for more details.
'git mergetool' will now attempt to use one of the following tools:
meld opendiff kdiff3 tkdiff xxdiff tortoisemerge gvimdiff diffuse diffmerge ecmerge p4merge araxis bc3 codecompare emerge vimdiff
Merging:
>

In my case vimdiff was the automatically selected mergetool. In any case when the tools open up their will genrally be three windows.
The window labled *.REMOTE is the file to be merge from the remote repository. The *.LOCAL file is the file the is being merged into
and the .BASE file is the common base to base files. These programs genrally let you view all the files at one letting you visually
inspect the code between all three simultaneausly. Once you resolve these merge confilcts save the files and run git commit to finish
the commit
	
	git commit

Notics the commit mesage tells you what files had a confict. Dont forget to set it to the apppriate branch for the fast forward merge.

There are many mergetools that can be used. A common one that is used is meld which is on the list of tools git knows about.
To use another tool that is not configured for automatic use pass mergetool the -t (--tool) flag and the name of the tool.

	git mergetool -t meld

Meld will bring up a GUI based mergetool to help you finish the merge. 
Lets bring our -base branch up to date.
	
	git checkout 2015winter-base
	git merge 2015winter-tmp


Up to this point 'git remote' was used to add remotes to a repository, 'git fetch' was used to grab those repo's, 'git merge' was
used to merge those repo's, 'git meregtool' was used to resolve the confilcts if any. Well that seems like an awful lot to update a 
repository. Thankfully there is a command to do most of that work for us. It is 'git pull'. Though this does not follow the prevois 
steps exeactly, it does perform a 'git fetch' followed by a 'git merge'. Checkout the original 2015 winter branch and recreate the 
-base and -tmp branches again. checkout the -tmp branch.

	git pull <remote> <branch>
	git pull upstream 2015winter	

This will fetch and merge just like we did manually before. 
Check out the -tmp branch and make the conflicting change again.

	git pull upstream 2015winter

It results in a merge confilct again. This is a great time to use mergetool


