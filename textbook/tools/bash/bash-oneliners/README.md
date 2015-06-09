#10 Useful Bash One-liners#

Here are 10 useful bash one-line commands.

##1. Create a copy of all pdf files into a directory called backup:
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
