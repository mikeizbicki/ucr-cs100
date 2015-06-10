#10 Useful Bash One-liners#

Here are 10 useful bash one-line commands. 

At LOT of these commands can be substituted with all files types, directories, etc.

##1. Create a copy of all pdf files into a directory called backup.
    $ for i in *.pdf; do cp $i /backup/; done
Wait, what? 

Yes, although it seems confusing at first, it will become clear very soon
Let's break it down into components.
This command contains three core parts:

Part A)

    for i in *.pdf

Here, the for-loop is iteratively searching through the current directory for `.pdf` files. 

Part B)

    do cp $i /backup/;
Here it is taking the found `.pdf` file and copying it directory into the backup folder.

Part C)

    done
    
Finally it completes the process with the `done` command.

##2. Display largest ten files in current directory and subdirectories.
    $ du -a ./ | sort -n -r | head -n 10

Something hogging your computer hard drive space? Need to figure out what it? 

Run the above command, but before you do it, change to your home directory. The command search will start in the current directory so changing to your home directory will search the majority of your filesystem.

In other words, run

    $ cd; du -a ./ | sort -n -r | head -n 10
    

Here, `cd` will take you to your home directory **and then** you will run the command. 
This way, you still retain the one-liner aspect.

##3. Find all executable files in the current directory and subdirectories
    $ find ./ -type f -perm -o+rx -exec ls -ld '{}' \;

Combining `ls` and `find` commands along with some flag parameters, we can generate a list of executable files that exist within the current and subdirectories.

##4. Print your top 10 most frequently used bash commands
    $ history | sed 's/^ \+//;s/  / /' | cut -d' ' -f2- | awk '{ count[$0]++ } END { for (i in count) print count[i], i }' | sort -rn | head -10
    
##5. Find the 5 most recently updated .txt files
    $ find . -name "*.txt" -mtime 5
    
If you are developing a large project, you probably already have a TON of documentation, right?
With large projects that contain multiple README or `.txt` files, it is easy to lose track of what gets updated. 
If you're not especially careful in continuously committing your work, you'll potentially skip or overwrite some valuable information. 

Use the above command to keep track and prevent the loss of precious information.


Use the command above to track the top 5 `.txt` files
    
##6. Display the top 10 memory intensive processes on your computer
    $ ps aux | sort -nk +4 | tail

Similar to #2, the command above, when run, prints out, in descending order, the top 10 processes that are utilizing the memory.

![Image of Google Chrome eating ram](http://i.imgur.com/bhfYx6R.jpg)

Just like google chrome, there can be many other programs that are slowing down your computer.


##7. Grab files from a remote server to you local machine
    $ scp your_username@remotehost.edu:foobar.txt /some/local/directory
    
##8. Execute a command at midnight
    $ echo cmd | at midnight

    
