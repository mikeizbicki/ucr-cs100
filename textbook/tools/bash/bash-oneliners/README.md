#10 Useful Bash One-liners#

Performing tasks for each file can be tedious.

Here are 10 bash one-liners that may be useful to you at some point in the future.

Using bash commands cuts down process so you save time!

##1. Create a copy of all pdf (or any other file type) into a directory called backup (or another name of your liking):
    for i in *.pdf; do cp $i /backup/; done
 

###Wait, what? 
###Yes, although it make seem confusing at first, it will become clear very soon.
### Let's break it down into components that are separated by each `;`
###First we have the
    for i in *.pdf
