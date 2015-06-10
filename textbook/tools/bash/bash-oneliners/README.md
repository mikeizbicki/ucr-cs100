#10 Useful Bash One-liners#

Here are 10 useful bash one-line commands.

##1. Create a copy of all pdf files into a directory called backup.
    $ for i in *.pdf; do cp $i /backup/; done
Wait, what? 

Yes, although it seems confusing at first, it will become clear very soon
Let's break it down into components.
This command contains three core parts:

Part A)

    for i in *.pdf

Here the for loop is iteratively searching through the current directory for `.pdf` files. 

Part B)

    do cp $i /backup/;
Here it is taking the found `.pdf` file and copying it directory into the backup folder.

Part C)

    done
    
Finally it completes the process with the `done` command.

##2. Display largest ten files in current directory and subdirectories.
    $ du -a ./ | sort -n -r | head -n 10
    
##3. Find all executable files in the current directory and subdirectories
    $ find ./ -type f -perm -o+rx -exec ls -ld '{}' \;

##4. Print your top 10 most frequently used bash commands
    $ history | sed 's/^ \+//;s/  / /' | cut -d' ' -f2- | awk '{ count[$0]++ } END { for (i in count) print count[i], i }' | sort -rn | head -10
    
##5. Find the 5 most recenetly updated .txt files
    $ find . -name "*.txt" -mtime 5
    
##6 Determine the highest memory consumer on your computer!
    $ ps aux | sort -nk +4 | tail

    

