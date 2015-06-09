#10 Useful Bash One-liners#

Performing tasks for each file can be tedious.

Here are 10 bash one-liners that may be useful to you at some point in the future.

Using bash commands cuts down process so you save time!

##1. Create a copy of all pdf files into a directory called backup:
    for i in *.pdf; do cp $i /backup/; done
Wait, what? 
Yes, although it make seem confusing at first, it will become clear very soon.
Let's break it down into components.
This command contains three core parts:

Part A)

    for i in *.pdf

Part B)

    do cp $i /backup/;

Part C)

    done
