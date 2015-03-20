# The [vim](http://www.vim.org/about.php) text editor

*You will need to be comfortable with the bash terminal in order to complete this lab.
Some previous cs100 students created a [short tutorial](./terminal.md) you can work through if you need a refresher.
You will not lose any points if you can't finish the main lab in time due to working through this tutorial.
You will be able to finish the lab later.*

In this course, we won't be using any graphical interfaces.
All our programming will be done on the terminal using a text editor called `vim`.
The purpose of this lab is to introduce you to `vim`.
It will seem weird at first.
But with practice, you will find `vim` much more powerful than either the `geany` or `Cloud9` editors you are already familiar with.

Vi IMproved or `vim`, is a powerful text editor who's reliance in a text user interface rather than icons and menus creates a powerful environment that is built to enable efficient text editing.
Often referred to as a "programmer's editor", proper usage of `vim` can make programmers more efficient and in general improves the productivity among its users.

### Part 1: vimtutor

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

### Part 2: The vim-adventures game

Once you have finished `vimtutor`, start playing [vim-adventures](http://vim-adventures.com).
The first three levels are free (and that's all you're required to do).
You're welcome to pay for the full game if you want, but I'm not requiring you to do so.

### Part 3: The .vimrc file

#### Configuring vim
Part of Vim's power is that it can be extensively customized.
The `vim` runtime configuration file or `.vimrc`, located in your home directory, holds the startup information for `vim`.
The `vim` editor can be configured by altering the `.vimrc` file.

To edit your `.vimrc` file, run the command:
```
$ vim ~/.vimrc
```
The `~` is a shortcut name for your home directory.

Add the following lines to your .vimrc file:
```vim
set number
colorscheme darkblue
```
* Save the file using the `:w` command in Normal mode.
* Source the file by running the `:source %` command in Normal mode.
(The `:source %` command in `vim` will source the vimrc, meaning `vim` will run this script on startup.)

Watch as your `vim` editor comes to life with a dark  blue theme and line numbers enabled.
Vim will default to these settings when you open up the editor so long as these
two lines exist in the sourced `.vimrc`.

#### Plugins
Vim plugins allow you to enhance, change, or add to Vim's existing behaviors.
Though don't just add every plugin available.
Too many plugins can clutter your .vimrc file and essentially cause ambiguity.
It is important to think first about what you need from them.
For example, you might need a plugin that [highlights syntax errors](https://github.com/tpope/vim-markdown) in code or one that [completes words using the `<Tab>` key](https://github.com/ervandew/supertab).
More `vim` plugins can be found [here](http://vimawesome.com/).

 Managing plugins is difficult without the use of plugin managers like [Vundle](https://github.com/gmarik/Vundle.vim), [NeoBundle](https://github.com/Shougo/neobundle.vim), [VimPlug](https://github.com/junegunn/vim-plug), and [Pathogen](https://github.com/tpope/vim-pathogen).
Plugin managers make it easier to modify your `.vimrc` file without you having to move files around yourself.
They do the work for you.

### Part 4: The task at hand

For this lab we will be using a configuration prepared by a former CS100 student.
This will also give us a small taste of the power of `vim`. (Its real power lies in the productivity boost one gains when effectively using vim but will take a lot of practice)

We will start by taking a look at the repository for the [vim configuration](https://github.com/Anthony1234567/Vimrc1234567).
Since we have not yet learned about Git and git commands in lecture, here is a command that will automate the process.

Type the command below into the terminal.
```
bash <(curl https://github.com/Anthony1234567/Vimrc1234567/raw/master/install1thru7.sh -L)>
```

Your task is to add (or remove) customizations of your choice to this file.

#### Suggestions:
1. There are a number of plugins that aren't doing anything in our vim configuration (Lab computers do not allow students to install the software necessary for the plugins to work properly)
2. There might be some lines in the file that cause errors when starting vim.
3. You might want to add a feature to vim that isnt in the file.
4. You might want to change the colorscheme. (other colorschemes can be found [here](http://cocopon.me/app/vim-color-gallery/))
 You might not like the autoindent setting or maybe you are used to tabs being four spaces long and not two.
5. Organization is key to knowing what goes into your .vimrc file. It'll make
	 searching up settings and adding to the file easier

After making your changes to the `.vimrc` file save using the `:w` command in Normal mode.
Then source the file using the `:source %` command.

For some good ideas on what options to use, you can look at these examples:

* [Mike Izbicki's (the instructor's) personal `.vimrc` file](https://github.com/mikeizbicki/dotfiles/blob/master/.vimrc)

* [A vim configuration prepared by previous cs100 students](https://github.com/atan009/vimrc)

#### In General
Personalizing your `.vimrc` is a good way to improve your knowledge of the `vim` editor but that alone wont make you and expert.
Practicing and learning the commands although, can seem difficult at first, help make `vim` the powerful tool that it is.
Once you've mastered `vim` less of your time will be spent navigating your code and typing up your program and more of it can be spent actually thinking about your program. (Of course mastering the art of Touch Typing is also important)

You may find the following links useful:
* [Doug Black: A Good Vimrc](http://dougblack.io/words/a-good-vimrc.html)

* [stackoverflow: what is your most productive shortcut with vim?](http://stackoverflow.com/questions/1218390/what-is-your-most-productive-shortcut-with-vim)

* [stackoverflow: simple vim commands you wish you'd known earlier](http://stackoverflow.com/questions/1276403/simple-vim-commands-you-wish-youd-known-earlier)

* [vim for people who think things like vim are weird and hard](http://csswizardry.com/2014/06/vim-for-people-who-think-things-like-vim-are-weird-and-hard/)

## deliverables

Everyone gets full credit on this lab just for showing up.
But you can't leave until you finish all three parts and show the TA your modified `.vimrc` file.
