#GIT GAME V2

##Description
We will be creating a sequel of sorts to the Git Game, called Git Game v2. It will consist of ten levels which involve practicing with more advanced or not well known git commands such as git bisect.

**Modifications to old gaming style**
Git Game v2 will run very similar to the first game, with some exceptions. In the README of every level there will be a progress bar that shows what level you should be on, in order to prevent confusion; the old game did not do this. We will also implement a list of commands per level that the user should know, or should have learned from previous levels.

##Levels and associated Git commands

``level 1: git grep -n``

- We will give the user a specific task that can only be carried out by using git grep -n to find “nameofnextbranch@yahoo.com” where nameofnextbranch is obviously the name of the next branch. This will be hidden in the repo.

``level 2: git submodule``

- We will present the user with a riddle. The user is then supposed to answer the riddle and put the answer in where the underscores are in the following URL: https://github.com/______/______. The user is to then use (git submodule add URL) to put the repo into the current repo and navigate to the README of this new repo to find the next clue.

``level 3: git remote``

- The user will be presented with a difficult question where the answers can only be accessed by using git remote to display the remote repositories connected to the git game repository. There will be four repository names and the proper answer will be one of them. This will also be the name of the next branch to checkout.

``level 4: git reset``

- Another riddle will be presented on this level's branch. The answer itself will be a very very large number and will corresponding to how many commits the user must reset to. There will be hundreds of thousands of commits on this branch each with the same commit message. Once the user uses git reset to reset back the specified amount of commits there will be a README.md file that contains the name of the next branch to commit to.

``level 5: git revert``
- In the previous level the user is told to go to a branch with commit that contains an error. In order to advance to the next branch the user must use git revert to revert back to a non-error filled commit which contains a message that says to go to this next branch of the level.

``level 6: git show``

- User is presented with a question which he/she must answer. The answer is in one of the commit messages. Once they checkout this commit they are to run git show on the hash of the current commit to show the changes made, which in this commit it will wont be one change which will tell the user to go to the next branch.

``level 7: git describe``

- The user is told to use git describe on a commit in the branch that is pointed to by the previous level. In this, the user then is able to see what the next tag, not branch, he or she is to checkout. A riddle may not be used here.

``level 8: git cherry pick``

- Cherry pick three commits from one branch into another branch. The user will have to use git revert four commits on the current branch to get to the commit that contains the name of the next branch to checkout. In essence, the branch the commit the user is attempting the go to after cherry picking is the previous commit of the current commit before cherry picking. But the user will not know this.

``level 9: git shortlog``
￼￼￼￼
The user will be tasked with figuring out who contributed most to the repository, where this can only be done using git shortlog when playing the git game (unless the user wants to go through and tally up names and commits). The name of the next branch will correspond to the name of the highest contributor.

``level 10: git bisect``
- To be determined still.

###Partners: Juan Gerardo Ruelas (jruel006), Kevin Ortega(CompKev), John Andrew Dixon(jdixo001), Hoi Cheong Kwan(hkwan003)
