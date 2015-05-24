# the `vim` text editor

*You will need to be comfortable with the bash terminal in order to complete this lab.
Some previous cs100 students created a [short tutorial](./terminal.md) you can work through if you need a refresher.
You will not lose any points if you can't finish the main lab in time due to working through this tutorial.
You will be able to finish the lab later.*

In this course, we won't be using any graphical interfaces.
All our programming will be done on the terminal using a text editor called `vim`.
The purpose of this lab is to introduce you to `vim`.
It will seem weird at first.
But with practice, you will find `vim` much more powerful than either the `geany` or `Cloud9` editors you are already familiar with.

### part 1: vimtutor

Open up a terminal and type the command:
```
$ vimtutor
```
This command walks you through the basics of using the `vim` editor.
Don't just read the file!!!
Make sure to actually do the exercises!!!

**IMPORTANT:**
The key to mastering `vim` is practice.
Therefore, you are required to use `vim` for all lab and homework assignments in this course.
**Using any editor other than `vim` will result in a 0 on the assignment.**

### part 2: the vim-adventures game

Once you have finished `vimtutor`, start playing the game: http://vim-adventures.com.
The first three levels are free (and that's all you're required to do).
You're welcome to pay for the full game if you want, but I'm not requiring you to do so.

### part 3: the `.vimrc` file

`vim` stores its settings in a file called `.vimrc` located in your home directory.
Your task is to add ten customizations of your choice to this file.

To edit your `.vimrc` file, run the command:
```
$ vim ~/.vimrc
```
The `~` is a shortcut name for your home directory.

For some good ideas on what options to use, you can look at these examples:

* [Mike Izbicki's (the instructor's) personal `.vimrc` file](https://github.com/mikeizbicki/dotfiles/blob/master/.vimrc)

* [A vim configuration prepared by previous cs100 students](https://github.com/atan009/vimrc)

You may also find the following links useful:

* [stackoverflow: what is your most productive shortcut with vim?](http://stackoverflow.com/questions/1218390/what-is-your-most-productive-shortcut-with-vim)

* [stackoverflow: simple vim commands you wish you'd known earlier](http://stackoverflow.com/questions/1276403/simple-vim-commands-you-wish-youd-known-earlier)

* [vim for people who think things like vim are weird and hard](http://csswizardry.com/2014/06/vim-for-people-who-think-things-like-vim-are-weird-and-hard/)

## deliverables

Everyone gets full credit on this lab just for showing up.
But you can't leave until you finish all three parts and show the TA your modified `.vimrc` file.
