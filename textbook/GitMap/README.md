#GitMap 
##Description
GitMap creates a map of a git repository, showing all the commits of each branch. 
The map will be saved in a plain text file with the name of **Mike_Izbicki's_Treasure_Map**. 

The state of your git repo is very important - you should know what's going on in it, and what's happened to it,
especially when you're working on a project with multiple people contributing to it.
GitMap enhances the `git log` command, displaying commits for all branches while tagging the current position of each branch.

Currently, the script will only work if every branch is derived from the same head branch. 
The map will show the author, date, and message of each commit. 
The information of each commit is contained within a box. 
Currently, the box will look like:
```
.______________________   
|......................|
|Author: Name of Author|		
|Date: Date of commit..|    		
|Commit Message........|		
|______________________|   
```
The commits at the top of the file refer to the most recent commits. 
The box points upwards to show the next/more recent commit. 
An arrow pointing to the side from the commit message means that the branch has ended.
The long list of periods is to format the box correctly. 
An example would be:
```
.______________________________   
|..............................|
|Author: Timothy Truong........|		
|Date: Wed Jun 10 14:29:09 2015|   
|Most recent commit............| -----> (master)	
|______________________________|

^    
|    
.______________________________   
|..............................|
|Author: Timothy Truong........|		
|Date: Wed Jun 10 14:20:28 2015|   
|Less recent commit............|    
|______________________________|
```
The program's run time will depend upon the amount of branches and commits that your git repository contains; 
the greater the number of commits and branches, the longer it will take for the program to finish executing.
A git repository with only the master branch and 100 commits will take about 40 seconds to run.
The resulting file will be stored in the directory that was passed into the command.

##Warning
Before running this program on a git repository, commit all changes to the repository. 
All uncommited changes will be reverted to the last commit.

##Downloading and Running
To download, run the command:    
```
$ git clone https://github.com/ykamo001/GitMap  
$ . PathToGitMap/src/GitMap.sh PathToYourGitRepo 
```
If no PathToYourGitRepo is passed in such as
```
$ . PathToGitMap/src/GitMap.sh
```
The script will run on the current directory.

#Error Messages
* If PathToYourGitRepo is not passed in when running the script,   
`Path was not specified. Script will execute in current directory` 
* If `PathToGitMap/src/GitMap.sh PathToYourGitRepo` is passed in, 
the screen will output 
`bash: PathToGitMap/src/GitMap.sh: /bin/bash: bad interpreter: Not a directory`
* When run on a directory that is not a git repository, 
the screen will output 
```
fatal: Not a git repository (or any parent up to mount point /homeDirectory)    
Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).   
wc: ./RandomTempFileName/master: No such file or directory    
bash: [: 0: unary operator expected
bash: ./RandomTempFileName/master: Nosuch file or directory
```

##Examples
You can see an example of the script run on [@ykamo001's](https://github.com/ykamo001/rshell) rshell repository in GitMap/example.

##Bugs and Issues
* If the folder isn't a git repository, our script will still try to run and an empty file will be created
* When run, the screen will output 
`Switched to branch \'exampleBranch\'` 
for every branch in the git repository
* If passing in more than one PathToYourGitRep, 
the script will be run only on the first one 
(or third arguement of the command).
* The output file will be placed in the repository that GitMap.sh is ran on
* The program's runtime is long, and depends solely upon the amount of branches and commits in the git repository.
* Only works if all branches are from the same head branch

