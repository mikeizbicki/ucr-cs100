##Guide To Getting Started: The Terminal, GitHub, & VIM
Learning to use github, vim, and the terminal can be very confusing and hard to learn when you are so used to writing code and saving it your own way. Thankfully, we've created a simple video guide to help you reach your potential in most areas of the terminal, github, and vim. 

Our names are Rashid, Kyler, and Sean, Junior Computer Science Majors at the *University of California, Riverside*. We took our CS100 class not knowing how to use or even get started with the terminal, github and vim. Rest asure, we didn't want to let anyone else feel unconfident about these three things. That's why we've put together a series of video guides to get you started in the right direction towards learning the basics of the terminal, github, and vim.

Click The Images Below To Be Taken To YouTube To Watch

Click [HERE](https://www.youtube.com/watch?v=Fv5Cy8i14ck&list=PLQ6W7BIxh4zvbwT7cQJh8jSxsz47MP3Z5) To Watch The Entire Playlist In Order

Clock [HERE](https://github.com/svill014/test) To Read Our Paper On *Helpful Commands for vim* (excerpt inserted above related videos below)

Learning GitHub
---
               
####Getting Started
[![Alt text for your video](http://img.youtube.com/vi/Fv5Cy8i14ck/0.jpg)](https://www.youtube.com/watch?v=Fv5Cy8i14ck)

In this video, we will show you step by step how to create your first account on GitHub. When I first made my account, I was unsure of what the exact steps were to correctly make my repository. On top of that, I had no idea how to even get something online (eg: github) and clone it to my local machine because this was all new methods for me. We made sure to show you the exact process on the web browser and terminal so you can safely and correctly get your first repository on your local machine.



####Creating a file and Pushing/Pulling with GitHub
[![Alt text for your video](http://img.youtube.com/vi/8vrVJT29K58/0.jpg)](https://www.youtube.com/watch?v=8vrVJT29K58)

So now that you've been able to clone you directory from GitHub to your local machine, you may be asking yourself "How do I even make files and put it my GitHub?" There are a few ways to create a file. One way enables you to create the file automatically via the `touch <filename>` command. The `touch <filename>` command will create the file for you even if you specify an extention in the filename (eg: main.ccp will make a file called name in a .cpp format). The second option you could do is via the `vim <filename>` command, which will open up an editor named of a file named after the filename you inputted BUT it will not save the file for you once you create it. You could save the file once the editor opens up or after you edit the file by pressing `:w` (in the respective order) or `:wq` which will save and edit the `vim` editor for you immediately after.



####Branches
[![Alt text for your video](http://img.youtube.com/vi/Xaw0JNYUj_U/0.jpg)](https://www.youtube.com/watch?v=Xaw0JNYUj_U)_

We've all been in the position before. You've been coding up a program where most of it's files are ready to be published to the world while some may not. Thanks to GitHub, you are able to create branches off of your program that will anable you to work around your bugs and eventually merge the correct fixes to your main program. And since every repository has a branch named `master`, lets say your working on an app and theres one file in your app named count.cpp that doesn't count properly. Thankfully, you can create a `branch` named count and work on the count file and any other file without messing up your original code. This way you can mess around with any of your files till your count.cpp file works. After which, you can get back to your `master` branch and merge your two branches together. In the end, you completed your program, but safely worked out your bugs without messing up your whole program. In other terms, this is called version control.


####Tags
[![Alt text for your video](http://img.youtube.com/vi/Qf9-iMzz8tU/0.jpg)](https://www.youtube.com/watch?v=Qf9-iMzz8tU)



####Forking & Pull Requests
[![Alt text for your video](http://img.youtube.com/vi/tskyUTaJdVI/0.jpg)](https://www.youtube.com/watch?v=tskyUTaJdVI)



####`README.md` & `LICENSE` Files
[![Alt text for your video](http://img.youtube.com/vi/HZaB8uVMXAg/0.jpg)](https://www.youtube.com/watch?v=HZaB8uVMXAg)



Learning `vim`
---
Vim has so many commands that it can be intimidating for first time users.  They may feel that using a different, more familiar, editor would make coding more efficient. It may be difficult to remember what all of these new commands do, but these users may even begin to enjoy using it more than their previous editors if given enough time to practice with Vim.  I am not master at using Vim and am still learning new things about it.  Overtime, I learned a few tricks that helped me utilize Vim to make better code.



###Getting Started
[![Alt text for your video](http://img.youtube.com/vi/jQkyU6bgMIs/0.jpg)](https://www.youtube.com/watch?v=jQkyU6bgMIs)

It was difficult at first trying to transverse my code while using Vim.  I was so used to being able to use my mouse and simply click where I wanted to go. I was now at the mercy of moving my cursor one line at a time to go anywhere until I learned more about the many helpful tools Vim already had just for traveling through code.  Some are simple such as `gg` to go to the top of the code, `G` to go to the bottom of it, and `(any number)G` to go to the line number typed before the capital G.)

Some ways of moving through the text are a little more complicated but easy once a user gets used to them.  Any line of text can be searched if something specific is being searched for the text’s line is unknown.  This is done by using the command `/` and then typing what the user wants to search.  This will highlight the searched text wherever it appears in the code and place the cursor in the first highlighted area that it can find after the cursor’s original position.  There are many ways to transverse these highlighted characters, but the one I found most helpful was typing `n` for it will take you to the next highlighted word no matter where you currently are.

One problem that I would occasionally get is I would do some sort of command by ident and highlight something that I did not want to highlight. At first I did not even know that I could highlight things so I thought I messed something up and this would affect my code.  This is not the case. There are many different ways to highlight and this is exists to help with Vim.  If this is done by accident then there are a few ways to get rid of the highlight. Highlighting something else would get rid of this, but when I first started using Vim I did not even know how to do that. There is a command that will get rid of any highlights and return the text back to normal without highlighting anything else. Just type `:nohlsearch` and the highlight will go away.



####Indentation
At first it felt very time consuming to indent multiple lines. I would go to the beginning of each line and after using `i` and type tab.  With so many commands in Vim, I was surprised that there was no command to just indent a few lines.  I felt this way until I found about the `V` command.  `V` lets users highlight a line and pressing up or down can highlight as many lines as they desire.  All that was left to do was to type `>` after everything I wanted to indent was highlighted and it all would indented once to the right. Typing `<` would instead indent it to the left if I ever wanted to do that.  This greatly improved my usage of Vim for `V`, or `v` if users wanted to highlight characters instead of entire lines, was could be combined with many commands and not just indenting.
[![Alt text for your video](http://img.youtube.com/vi/UAcSoRLRLug/0.jpg)](https://www.youtube.com/watch?v=UAcSoRLRLug)



####Deletion
Just like indenting, I thought that I could only delete one character at a time when I started using vim.  This would become bothersome if I wanted to fix a big part of my code that I knew needed to be deleted.  There are plenty of different ways that I learned to speed this up.  The most helpful ways were pressing `x` after highlighting what I wanted deleted, and using the `d` command.  `d` can be used with many different things after it. `dd` will delete the entire line. `d$` will delete the rest of the current line. `dw` will delete the rest of the current word.  These commands made writing code in Vim go by much faster.

[![Alt text for your video](http://img.youtube.com/vi/qjJ3nIcExhE/0.jpg)](https://www.youtube.com/watch?v=qjJ3nIcExhE)



####Selection, Copy & Paste

Cutting, copying, and pasting took a while to get used to when using Vim. Sometimes there was something I wanted in my code that was in the instructions for the assignment.  I knew that in order to paste I would use the `p` command, but I could not paste things from outside of Vim into it.  I solved this with one of the few times I could use my mouse in Vim.  If I had something copied outside of Vim, then to paste it into Vim I would right click and just click paste.  This would paste it wherever the cursor currently is.  This can also be used to copy from Vim.  If you right click to copy, then it will not affect what is copied by using the commands `y` to copy or the commands `d` or `x` to cut.  If those commands are used, the just clicking `p` will paste them.  There are other ways to store more than one thing while copying or cutting, but these two ways were the most helpful as I learned how to use Vim.
[![Alt text for your video](http://img.youtube.com/vi/-DN_xww8jOM/0.jpg)](https://www.youtube.com/watch?v=-DN_xww8jOM)_



####Appending & Pre-pending
[![Alt text for your video](http://img.youtube.com/vi/j9MueYcWJbg/0.jpg)](https://www.youtube.com/watch?v=j9MueYcWJbg)



Learning The Terminal
---
####The `ls` command
[![Alt text for your video](http://img.youtube.com/vi/RMxvcc_QUUI/0.jpg)](https://www.youtube.com/watch?v=RMxvcc_QUUI)_


####The `cd` and `mv` commands
[![Alt text for your video](http://img.youtube.com/vi/xzN-sY5oyFk/0.jpg)](https://www.youtube.com/watch?v=xzN-sY5oyFk)



####Replacing
Similar to using d to get rid of code, I learned a few ways to replace what was already typed. Lower case r can replace one letter while upper case R can replace one letter with many. Just type r or R and what you want to replace it with. Some commands allow the user to replace multiple characters with as many as the user wants to using the c command. A few of these that I found most helpful were cw to replace the rest of the current word, cb replaces the characters before the cursor on the current word, c$ replaces the rest of the current line, and c0 replaces the entire line before the cursor.

[![Alt text for your video](http://img.youtube.com/vi/qLM7ej9Ures/0.jpg)](https://www.youtube.com/watch?v=qLM7ej9Ures)



####PERROR
[![Alt text for your video](http://img.youtube.com/vi/qx4yQ7-im_c/0.jpg)](https://www.youtube.com/watch?v=qx4yQ7-im_c)_



####Scripts
[![Alt text for your video](http://img.youtube.com/vi/a2JDWoYeGq8/0.jpg)](https://www.youtube.com/watch?v=a2JDWoYeGq8)



Helpful Hints
---
It took me quite a while to completely understand the `%` command.  It is supposed to match the current parenthesis, or a character similar to parentheses, to the one that closes it but there were times when it just did not work.  When it works, it is very helpful for it helps users to see if something is outside of a loop or if a loop ends where it should, but I noticed that it sometimes would be buggy if there was some parenthesis in comments.  The `%` command does not differentiate between something a comment or normal code.  This led to some very confusing moments where it would seem that my code would work even if `%` told me that the parenthesis did not match up correctly.  Users should make sure to keep track of any parenthesis in comments if they decide to use the `%` command.

Many of these commands are very helpful to speed up coding, but can still take quite a while if they are needed to be done multiple times.  This can be solved by simply typing the number of times a user wants the command to be done before the user types the command.  If I wanted to indent multiple lines three times, then I would do what I normally would do but type `3>` instead of just `>` by itself.  This may not seem like much, because highlighting it and using `>` three times will give the same result and may seem easier.  The reason why using a number is so useful is it would be quite time-consuming to highlight one 100 lines of code each time it is to be indented. This helps save time when doing that command a great number of times or over a large amount of code.



####How To SSH (into well server)
[![Alt text for your video](http://img.youtube.com/vi/CLv1hpLw3is/0.jpg)](https://www.youtube.com/watch?v=CLv1hpLw3is)



####Spectacle App
One of the first things I noticed about Vim that I initially disliked was that it took over the terminal when I used it.  I thought that I would have to close Vim each time I wanted to test if my program could run correctly.  To get around this issue, I started using two terminals instead of just one while I was programming.  I would run Vim using the first terminal and would run the executable in the second.  It was as simple as using `:w` to save on Vim instead of using `:wq` to save and quit. I could now test my code without ever having to close Vim.
[![Alt text for your video](http://img.youtube.com/vi/-PWJe6vr0rk/0.jpg)](https://www.youtube.com/watch?v=-PWJe6vr0rk)



####Modifying vim (.vimrc file)
[![Alt text for your video](http://img.youtube.com/vi/fck6HFCUg2s/0.jpg)](https://www.youtube.com/watch?v=fck6HFCUg2s)



In Conclusion
---
Vim can seem frustrating at first and it may appear to be much more difficult to do what people are used to. Users may want to give up because they have to relearn commands that were once second nature with other editors.  It may take a while to relearn things such as `u` is now undo and `cntrl-R` is now redo, but it will be worth it in the end.  Vim has many tricks that can help speed up programming, even if new users do not learn it all right away.  The information can always be found if new users need a reminder on how to do something.  With time, the commands in Vim will start to become just as easy to use as the commands in any other editor.  If users stick to learning how to use Vim a little at a time, then they will begin to be surprised how they ever coded without it.

