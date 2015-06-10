#10 Useful Bash One-liners#

![bash one-liner logo](https://pbs.twimg.com/profile_images/2032590984/brand_400x400.png)

Here are 10 useful bash one-line commands. 

These commands are extremely versatile in that a LOT of these commands can be substituted with all files types, directories, etc.

<<<<<<< HEAD
##1. Create a copy of all pdf files into a directory called backup:
    $ for i in *.pdf; do cp $i /backup/; done
Wait, what? 
Yes, although it make seem confusing at first, it will become clear very soon.
Let's break it down into components.
This command contains three core parts:
=======
##1. Create a copy of all pdf files into a directory called backup.
    $ for i in *.pdf; do cp $i /backup/; done
![file backup](http://www.bestbackupservices.com/wp-content/uploads/2010/07/CopyBackupFiles.jpg)
>>>>>>> 44f2df77beb52827b65e47a12384a0f239d58318

You aren't limited to only `.pdf` files!
For example, you could replace, the `.pdf` extension with whatever your heart desires:

    $ for i in *.txt; do cp $i /backup/; done
    $ for i in *.md; do cp $i /backup/; done
    $ for i in *.cpp; do cp $i /backup/; done

<<<<<<< HEAD
Here we are iteratively going through the current directory in search for `.pdf` files. If a `.pdf` file is detected, then it 

The `*` symbolizes anything before it is completely fine.

Part B)
=======
The same applies for the folder where these backup files are stored. You can place them in an already existing folder or a newly created one that will be made when you run the command.
>>>>>>> 44f2df77beb52827b65e47a12384a0f239d58318

##2. Display the ten largest files in current directory and subdirectories.
    $ du -a ./ | sort -n -r | head -n 10

<<<<<<< HEAD
Here we take

Part C)
=======
![low disk space](http://www.datareign.com/wp-content/uploads/2013/08/low-disk-space-solution.jpg)
>>>>>>> 44f2df77beb52827b65e47a12384a0f239d58318

Something hogging your computer hard drive space? Need to figure out what it? 

Run the above command, but before you do it, change to your home directory. The command search will start in the current directory so changing to your home directory will search the majority of your filesystem.

In other words, run

    $ cd; du -a ./ | sort -n -r | head -n 10
    

Here, `cd` will take you to your home directory. **then** you will run the command allowing you to retain the one-liner aspect. 

##3. Find all executable files in the current directory and subdirectories
    $ find ./ -type f -perm -o+rx -exec ls -ld '{}' \;

![exe files](http://outlookrepairhelp.com/wp-content/uploads/2013/08/ac829ddeecc44c12987cab354ba6ae7e.png)

Combining `ls` and `find` commands along with some flag parameters, we can generate a list of executable files that exist within the current and subdirectories.



##4. Print your top 10 most frequently used bash commands
    $ history | sed 's/^ \+//;s/  / /' | cut -d' ' -f2- | awk '{ count[$0]++ } END { for (i in count) print count[i], i }' | sort -rn | head -10
    
What commands are you typing the most?
If you're anything like me, you'll see a lot of `ls` and `clear`. 
Find out your most frequently typed bash commands by using the one-liner listed above.

You'll see an output similar to this:
    
##5. Find the 5 most recently updated .txt files
    $ find . -name "*.txt" -mtime 5
    
If you are developing a large project, you probably already have a TON of documentation, right?
With large projects that contain multiple README or `.txt` files, it is easy to lose track of what gets updated. 
If you're not especially careful in continuously committing your work, you'll potentially skip or overwrite some valuable information. 

Use the above command to keep track and prevent the loss of precious information.


Use the command above to track the top 5 `.txt` files
    
##6. Display the top 10 memory intensive processes on your computer
    $ ps aux | sort -nk +4 | tail

Similar to #2, the command above prints out, in descending order, the top 10 processes that are utilizing the memory.

![Image of Google Chrome eating ram](http://i.imgur.com/bhfYx6R.jpg)

Just like google chrome, there can be many other programs that are slowing down your computer.


##7. Grab files from a remote server to you local machine
    $ scp your_username@remotehost.edu:foobar.txt /some/local/directory
    
##8. Execute a command at midnight
    $ echo cmd | at midnight

    
