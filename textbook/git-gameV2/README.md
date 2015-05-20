# Git Game V2

## Descriptions:
We will be creating a sequel of sorts to the Git Game, called Git Game v2. It will consist of ten levels which involve practicing with more advanced or not well known git commands such as git bisect. 

## Modifications to old gaming style
Git Game v2 will run very similar to the first game, with some exceptions. In the README of every level there will be a progress bar that shows what level you should be on, in order to prevent confusion; the old game did not do this. We will also implement a list of commands per level that the user should know, or should have learned from previous levels.

## Levels and associated Git commands
``level 1: git clean``
- We will create a C++ program that writes over one hundred files, each with different names. The user is then to consider a riddle, whose answer will be the name of one of the many files that were created. The user is to commit this file and then use git clean to get rid of the other untracked files. The file itself has the next branch to checkout.


``level 2: git archive``
- To be determined still.


``level 3: git stash``
- The user will answer a riddle in the README and add it. In order to move onto the next branch, without committing (as will be specified to not commit) the user must use git stash to hide away the changes in memory. 


``level 4: git reset``
- Another riddle will be presented on this level's branch. The answer itself will be in the commit message of a commit about ten commits ago, to which they will git reset to. It is here they will check the README of this commit and that will give them the name of the next branch.


``level 5: git revert``
- In the previous level the user is told to go to a branch with commit that contains an error. In order to advance to the next branch the user must use git revert to revert back to a non-error filled commit which contains a message that says to go to this next branch of the level. 
``level 6: git rebase``
- User is presented with a question which he/she must answer, which is the name of the branch that the user must checkout next. To complete the level itself the user must use rebase on the next branch he/she is to go to.


``level 7: git describe``
- The user is told to use git describe on a commit in the branch that is pointed to by the previous level. In this, the user then is able to see what the next tag, not branch, he or she is to checkout. A riddle may not be used here.


``level 8: git cherry pick``
- Cherry pick three commits from one branch into another branch. The user will have to use git revert four commits on the current branch to get to the commit that contains the name of the next branch to checkout. In essence, the branch the commit the user is attempting the go to after cherry picking is the previous commit of the current commit before cherry picking. But the user will not know this.


``level 9: git filter-branch``
- In order to proceed to the next level the user must answer yet another riddle which is the name of the file that is to get deleted from all the commits of said branch. Once this happens, the user is to checkout a tag on the same branch which will be the last level. Note: The bug that will be detected by git bisect is caused by level 9. 


``level 10: git bisect``
- To be determined still.

Partners: Juan Gerardo Ruelas (jruel006), Kevin Ortega(CompKev), John Andrew Dixon(jdixo001), Hoi Cheong Kwan(hkwan003)
