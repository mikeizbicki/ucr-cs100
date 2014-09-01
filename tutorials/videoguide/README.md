##Guide To Getting Started: The Terminal, GitHub, & VIM
Learning to use github, `vim`, and the terminal can be very confusing and hard to learn when you are so used to writing code and saving it your own way. Thankfully, we've created a simple video guide to help you reach your potential in most areas of the terminal, github, and `vim`. 

Our names are Rashid, Kyler, and Sean, Junior Computer Science Majors at the *University of California, Riverside*. We took our CS100 class not knowing how to use or even get started with the terminal, github and `vim`. Rest asure, we didn't want to let anyone else feel unconfident about these three things. That's why we've put together a series of video guides to get you started in the right direction towards learning the basics of the terminal, github, and `vim`.

Click The Images Below To Be Taken To YouTube To Watch

Click [HERE](https://www.youtube.com/watch?v=Fv5Cy8i14ck&list=PLQ6W7BIxh4zuHBegLOCUL11uUIsHcszzQ) To Watch The Entire Playlist In Order

Clock [HERE](https://github.com/svill014/test) To Read Our Paper On *Helpful Commands for `vim`* (excerpt inserted above related videos below)

Learning GitHub
---
               
####Getting Started
[![Alt text for your video](http://img.youtube.com/vi/Fv5Cy8i14ck/0.jpg)](https://www.youtube.com/watch?v=Fv5Cy8i14ck)

In this video, we will show you step by step how to create your first account on GitHub. When I first made my account, I was unsure of what the exact steps were to correctly make my repository. On top of that, I had no idea how to even get something online (eg: github) and clone it to my local machine because this was all new methods for me. We made sure to show you the exact process on the web browser and terminal so you can safely and correctly get your first repository on your local machine.



####Creating a file and Pushing/Pulling with GitHub
[![Alt text for your video](http://img.youtube.com/vi/8vrVJT29K58/0.jpg)](https://www.youtube.com/watch?v=8vrVJT29K58)

So now that you've been able to clone you directory from GitHub to your local machine, you may be asking yourself "How do I even make files and put it my GitHub?" There are a few ways to create a file. One way enables you to create the file automatically via the `touch <filename>` command. The `touch <filename>` command will create the file for you even if you specify an extention in the filename (eg: main.ccp will make a file called name in a .cpp format). The second option you could do is via the `vim <filename>` command, which will open up an editor named of a file named after the filename you inputted BUT it will not save the file for you once you create it. You could save the file once the editor opens up or after you edit the file by pressing `:w` (in the respective order) or `:wq` which will save and edit the `vim` editor for you immediately after.



####Branches
[![Alt text for your video](http://img.youtube.com/vi/Xaw0JNYUj_U/0.jpg)](https://www.youtube.com/watch?v=Xaw0JNYUj_U)

We've all been in the position before. You've been coding up a program where most of it's files are ready to be published to the world while some may not. Thanks to GitHub, you are able to create branches off of your program that will anable you to work around your bugs and eventually merge the correct fixes to your main program. And since every repository has a branch named `master`, lets say your working on an app and theres one file in your app named count.cpp that doesn't count properly. Thankfully, you can create a `branch` named count and work on the count file and any other file without messing up your original code. This way you can mess around with any of your files till your count.cpp file works. After which, you can get back to your `master` branch and merge your two branches together. In the end, you completed your program, but safely worked out your bugs without messing up your whole program. In other terms, this is called version control.


####Tags
[![Alt text for your video](http://img.youtube.com/vi/Qf9-iMzz8tU/0.jpg)](https://www.youtube.com/watch?v=Qf9-iMzz8tU)

You've learn about `branch` but now we'll show you another feature of vim you might recognize in the software world. Recall downloading programs where it shows the different version numbers (For example: 1.0, 1.1, 1.2, 2.1, 2.2.1)? Well, tags enable you to immediately go to and from different times of your work. You might also be thinking how different are tags from branches? Well, tags are different way of accessing different version of your work (just like a checkpoint in a mario game!). If you're still unsure of how different tags can be, watch the video above as we've demonstrated the uses.


####Forking & Pull Requests
[![Alt text for your video](http://img.youtube.com/vi/tskyUTaJdVI/0.jpg)](https://www.youtube.com/watch?v=tskyUTaJdVI)

For myself, I've always wondered how people contributed to online projects. With GitHub, you can get a copy of someone's repository and modifying it to your liking or even contribute to it if you've found/fixed a bug. For pull requests, you'd only use it if you've found a bug and would like to submit the code you've changes in your copy of the original repository, to the original owner's copy. Although, pull requests are done online at github.com.



####`README.md`
[![Alt text for your video](http://img.youtube.com/vi/sg6KBi-TP7M/0.jpg)](https://www.youtube.com/watch?v=sg6KBi-TP7M)

README.md files are going to be the main focus of documenting and explaining to anyone who comes across your document what it does. A `README.md` allows you to explain your program and all its possibilities and defects. You can talk about the contributors, files included, what the program entitles the user to do, how to install it and much more! The easiest way I was told what a `README.md` file does is "it explains to someone else who has absolutely no idea what your program does or how to code, but it enables the user to understand the concepts and basic directions to execute your program."

Watch the video above and let us drive through both of these documents together to help you create a well organzied `README.md` file.



Learning `vim`
---
Vim has so many commands that it can be intimidating for first time users.  They may feel that using a different, more familiar, editor would make coding more efficient. It may be difficult to remember what all of these new commands do, but these users may even begin to enjoy using it more than their previous editors if given enough time to practice with Vim.  I am not master at using Vim and am still learning new things about it.  Overtime, I learned a few tricks that helped me utilize Vim to make better code.



###Getting Started
[![Alt text for your video](http://img.youtube.com/vi/jQkyU6bgMIs/0.jpg)](https://www.youtube.com/watch?v=jQkyU6bgMIs)

It was difficult at first trying to transverse my code while using Vim.  I was so used to being able to use my mouse and simply click where I wanted to go. I was now at the mercy of moving my cursor one line at a time to go anywhere until I learned more about the many helpful tools Vim already had just for traveling through code.  Some are simple such as `gg` to go to the top of the code, `G` to go to the bottom of it, and `(any number)G` to go to the line number typed before the capital G.)

Some ways of moving through the text are a little more complicated but easy once a user gets used to them.  Any line of text can be searched if something specific is being searched for the text’s line is unknown.  This is done by using the command `/` and then typing what the user wants to search.  This will highlight the searched text wherever it appears in the code and place the cursor in the first highlighted area that it can find after the cursor’s original position.  There are many ways to transverse these highlighted characters, but the one I found most helpful was typing `n` for it will take you to the next highlighted word no matter where you currently are.

One problem that I would occasionally get is I would do some sort of command by ident and highlight something that I did not want to highlight. At first I did not even know that I could highlight things so I thought I messed something up and this would affect my code.  This is not the case. There are many different ways to highlight and this is exists to help with Vim.  If this is done by accident then there are a few ways to get rid of the highlight. Highlighting something else would get rid of this, but when I first started using Vim I did not even know how to do that. There is a command that will get rid of any highlights and return the text back to normal without highlighting anything else. Just type `:nohlsearch` and the highlight will go away.



####Indentation
[![Alt text for your video](http://img.youtube.com/vi/UAcSoRLRLug/0.jpg)](https://www.youtube.com/watch?v=UAcSoRLRLug)

At first it felt very time consuming to indent multiple lines. I would go to the beginning of each line and after using `i` and type tab.  With so many commands in Vim, I was surprised that there was no command to just indent a few lines.  I felt this way until I found about the `V` command.  `V` lets users highlight a line and pressing up or down can highlight as many lines as they desire.  All that was left to do was to type `>` after everything I wanted to indent was highlighted and it all would indented once to the right. Typing `<` would instead indent it to the left if I ever wanted to do that.  This greatly improved my usage of Vim for `V`, or `v` if users wanted to highlight characters instead of entire lines, was could be combined with many commands and not just indenting.



####Deletion
[![Alt text for your video](http://img.youtube.com/vi/qjJ3nIcExhE/0.jpg)](https://www.youtube.com/watch?v=qjJ3nIcExhE)

Just like indenting, I thought that I could only delete one character at a time when I started using `vim`.  This would become bothersome if I wanted to fix a big part of my code that I knew needed to be deleted.  There are plenty of different ways that I learned to speed this up.  The most helpful ways were pressing `x` after highlighting what I wanted deleted, and using the `d` command.  `d` can be used with many different things after it. `dd` will delete the entire line. `d$` will delete the rest of the current line. `dw` will delete the rest of the current word.  These commands made writing code in Vim go by much faster.




####Selection, Copy & Paste
[![Alt text for your video](http://img.youtube.com/vi/-DN_xww8jOM/0.jpg)](https://www.youtube.com/watch?v=-DN_xww8jOM)

Cutting, copying, and pasting took a while to get used to when using Vim. Sometimes there was something I wanted in my code that was in the instructions for the assignment.  I knew that in order to paste I would use the `p` command, but I could not paste things from outside of Vim into it.  I solved this with one of the few times I could use my mouse in Vim.  If I had something copied outside of Vim, then to paste it into Vim I would right click and just click paste.  This would paste it wherever the cursor currently is.  This can also be used to copy from Vim.  If you right click to copy, then it will not affect what is copied by using the commands `y` to copy or the commands `d` or `x` to cut.  If those commands are used, the just clicking `p` will paste them.  There are other ways to store more than one thing while copying or cutting, but these two ways were the most helpful as I learned how to use Vim.



####Appending & Pre-pending
[![Alt text for your video](http://img.youtube.com/vi/j9MueYcWJbg/0.jpg)](https://www.youtube.com/watch?v=j9MueYcWJbg)

There are many ways to maneuver inside of `vim`. Some may just use the `h,j,k,l`, `up, down, left, right arrow keys`, or the `w, e, b` keys to move. Luckily, `vim` has two special keys to get you edditing much easier. The two, which are my favorite features of `vim`, are the `shift-a` (takes you to the end of the line and into insert mode) and the `shift-i` (takes you to the beginning of the line and into insert mode) command.



####Replacing
[![Alt text for your video](http://img.youtube.com/vi/qLM7ej9Ures/0.jpg)](https://www.youtube.com/watch?v=qLM7ej9Ures)

Similar to using `d` to get rid of code, I learned a few ways to replace what was already typed. Lower case `r` can replace one letter while upper case `R` can replace one letter with many. Just type `r` or `R` and what you want to replace it with. Some commands allow the user to replace multiple characters with as many as the user wants to using the `c` command. A few of these that I found most helpful were cw to replace the rest of the current word, `cb` replaces the characters before the cursor on the current word, `c$` replaces the rest of the current line, and `c0` replaces the entire line before the cursor.



Learning The Terminal
---
####The `ls` command
[![Alt text for your video](http://img.youtube.com/vi/-ksa4SnabAs/0.jpg)](https://www.youtube.com/watch?v=-ksa4SnabAs)

The `ls` command is one of the most used commands in bash. I would say that there isn't a time that I don't use `ls` when using the terminal. Proper knowledge of the `ls` command and the useful flags for `ls` helps to streamline the programming process. 

Passing in a directory name will display the contents of that directory. It is also possible to pass in a path for a directory to display any directory, regardless of the directory the user is currently in.

The basic `ls` command, when run, displays the contents within the current working directory.

If the `-a` flag is passed in with `ls`, all items in the current working directory prepended with a `.` are also displayed, along with the rest of the items.

Passing in the `-l` flag prints information for each item in the directory in a series of columns on a single line. The first column displays the read, write, and executable permissions for the main user, the group the current user is in, and any user in that order. The next column shows the owner of the item and the next column shows the group owner. The fourth column displays the size, in bytes, of the item. The fifth column displays the moment the item was created, and the last column displays the name of the item.

If the `-R` flag is passed in, the command will display the contents of the current directory, and then recursively enter every directory within the current directory and display the contents of that directory, then keep going into every directory until there are no more directories in the current directory it is in.

All these options are combinable for different uses. For example, the user could use the `-l` and `-a` flags to display the information for the items prepended with a `.` , or use `-R` and `-l` together.



####The `cd` and `mv` commands
[![Alt text for your video](http://img.youtube.com/vi/xzN-sY5oyFk/0.jpg)](https://www.youtube.com/watch?v=xzN-sY5oyFk)
 

The `cd` and `mv` commands are crucial commands in order to actually use the terminal. Without cd, a person would forever be stuck in their home directory. The `mv` command is necessary for moving files from one section of the hard drive. They're really simple commands, but without them, there'd be no way to orginize contents within a hard drive. 

The `cd` command by itself will change the current working directory to the home directory. If passed a directory name that is within the current working directory, the current working directory will be changed to the name of the passed in directory. `cd` will also take a path as an argument. When a path is passed in, the current working directory will be changed to the directory specified by the path. When `cd` is passed with `..`, the directory will go backwards, the directory that the current directory is in.

The `mv` command will move an item within a certain directory to the directory passed in. The structure of this command is `$ mv filename/directory_name destination` . If the destination argument is not a path, the command will look for the destination in the current working directory. The destination argument can be a path, so a user can move the item to any directory in the hard drive.



####PERROR
[![Alt text for your video](http://img.youtube.com/vi/qx4yQ7-im_c/0.jpg)](https://www.youtube.com/watch?v=qx4yQ7-im_c)

`perror(const char*);`

When programming for unix based operating systems (which is a primary component of CS100), system calls are a prominent component for code. When coding, error checking is always necessary. System calls make error checking very simple and very easy to implement with `perror` . Every unix system call returns an error value if the call fails. The `perror` function captures this error value (if returned) and prints to stdout an error message based on the system call and the type of error. It takes in one c-string argument, which is a message the user can pass in. 

When using system calls, it is absolutely neccessary to implement `perror` with every system call. Any program is not complete without `perror` . Without it, bugs will be exponentially harder to find and fix and will significantly stifle programming speed. Also, if you're like me and essentially did not use any `perror` functions whatsoever, your grade will suffer. It's really simple to implement, essentially adding only a line or two per system call, but the benefits are enormous.


####Scripts
[![Alt text for your video](http://img.youtube.com/vi/WKIbIO9ti38/0.jpg)](https://www.youtube.com/watch?v=WKIbIO9ti38)

Have you ever wondered how you could possibly record data output from a program, or how you could record a list of commands within your terminal to share it with your colleague or professors in the future? With the `script` command, all of this is possible. By just typing `script file_name_here`, you can start a script. Also, you don't need to worry about making a file beforehand, because when you specify the filename, it will make once for you in that name. Once you've gotten your script started, anything and everything you do within that terminal window, will be recorded as text within the document. Then when you're done, type `exit` and your terminal will say your script session has ended and re-state the filename in which it recorded all your commands in. You can then share or upload your script to show the any bugs or amazing new programs you've gotten to make.



Helpful Hints
---
####How To SSH (into well server)
[![Alt text for your video](http://img.youtube.com/vi/CLv1hpLw3is/0.jpg)](https://www.youtube.com/watch?v=CLv1hpLw3is)

`$ ssh your_netID@bell.cs.ucr.edu`


For the CS100 class, working within UCR's well server is crucial to succeed. The version of linux that the school's well server uses is different than other linux builds. Because of this, compilers will work differently in the well server than other local bash terminals, giving error messages after compilation on local bash terminals when compilation on the school servers will not, or compiling fine locally but failing to compile when compiled on the well server. Therefore, it is necessary to `ssh` into the well server and compile and run any code before submission. If it works on well, then it will work when it is graded. It's not neccessary to write the code in the school's server, but I would recommend doing all writing in the well server so that it is faster to debug and test, as opposed to writing locally, copying the file, saving it to your personal server, then compiling. I know for myself, when working on my first assignment for CS100, I wrote and compiled all my on my local machine and then submitted the final version without first checking if it compiled and ran on the school's server. Sure enough, I received a zero for inability to compile. From then on, I never wrote any code on my local terminal, doing all work on the school's server. I then checked my final version after modifying it to work on the school's server, and it didn't compile in my own bash terminal.

To `ssh` into the server, write in the command line `ssh`, followed by your net ID, and append `@bell.cs.ucr.edu` . You will be prompted for the password associated with the net ID (the password you use when signing into the lab computers), then placed in the home directory. To exit out of the server, type into the command line `exit`. You will exit the server and be placed back into your local bash. Any change saved to the server will be saved, so if you exit and re-enter the server, the changes will remain.



####Spectacle App
[![Alt text for your video](http://img.youtube.com/vi/-PWJe6vr0rk/0.jpg)](https://www.youtube.com/watch?v=-PWJe6vr0rk)

One of the first things I noticed about Vim that I initially disliked was that it took over the terminal when I used it.  I thought that I would have to close Vim each time I wanted to test if my program could run correctly.  To get around this issue, I started using two terminals instead of just one while I was programming.  I would run Vim using the first terminal and would run the executable in the second.  It was as simple as using `:w` to save on Vim instead of using `:wq` to save and quit. I could now test my code without ever having to close Vim.



####Modifying `vim` (.vimrc file)
[![Alt text for your video](http://img.youtube.com/vi/fck6HFCUg2s/0.jpg)](https://www.youtube.com/watch?v=fck6HFCUg2s)

Ever wondered how've we get our `vim` editor to work in the way we have it versus the default editor? `vim` has a file where you can setup it's defaults such as auto parentheses, auto-indent, and much more. By watching our video above, you can easily create new defaults for your `vim` editor that can cut time spent formating your text to spend more on coding.



In Conclusion
---
There are many commands that are quite useful but untaught. For example, the `%` command. It took me quite a while to completely understand the `%` command but it became really useful as I mastered it.  It is supposed to match the current parenthesis, or a character similar to parentheses, to the one that closes it but there were times when it just did not work.  When it works, it is very helpful for it helps users to see if something is outside of a loop or if a loop ends where it should, but I noticed that it sometimes would be buggy if there was some parenthesis in comments.  The `%` command does not differentiate between something a comment or normal code.  This led to some very confusing moments where it would seem that my code would work even if `%` told me that the parenthesis did not match up correctly.  Users should make sure to keep track of any parenthesis in comments if they decide to use the `%` command.

Many of these commands are very helpful to speed up coding, but can still take quite a while if they are needed to be done multiple times.  This can be solved by simply typing the number of times a user wants the command to be done before the user types the command.  If I wanted to indent multiple lines three times, then I would do what I normally would do but type `3>` instead of just `>` by itself.  This may not seem like much, because highlighting it and using `>` three times will give the same result and may seem easier.  The reason why using a number is so useful is it would be quite time-consuming to highlight one 100 lines of code each time it is to be indented. This helps save time when doing that command a great number of times or over a large amount of code.

Vim can seem frustrating at first and it may appear to be much more difficult to do what people are used to. Users may want to give up because they have to relearn commands that were once second nature with other editors.  It may take a while to relearn things such as `u` is now undo and `cntrl-R` is now redo, but it will be worth it in the end.  Vim has many tricks that can help speed up programming, even if new users do not learn it all right away.  The information can always be found if new users need a reminder on how to do something.  With time, the commands in Vim will start to become just as easy to use as the commands in any other editor.  If users stick to learning how to use `vim` a little at a time, then they will begin to be surprised how they ever coded without it.

