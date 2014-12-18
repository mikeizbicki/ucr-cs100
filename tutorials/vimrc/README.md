Introduction:
-------------
This is a pre-configured vim package that has .vimrc and .vim with nine useful plugins that we selected.
There will be brief introductions to vim, .vimrc, and the nine plugins that we included in the .vim folder.

Installation:
--------------
Before install, make sure you have: git and vim.

To download the pre-configured vim, type the command below to download .vimrc and all the plugins that we have.

	sh <(curl https://github.com/atan009/vimrc/raw/master/download.sh -L)

If the user already have .vim and .vimrc files, this installation will create a new directory called "old_vim_config" and move all the old files in it. 

vim :neckbeard::zzz:
-----------------------
Vim is a text editor. It is similar to vi, but can be considered to have more features. Vim itself is also similar to an IDE. It is capable of compiling files and running executables as well. Vim is very different from what most users are used to, however learning it usually proves to quite convenient and efficient.

TL;DR Vim is an upgrade for vi :smile:

More info at: [The Vim Editor: What Vim Can Do] (http://www.vim.org/about.php)

.vimrc :no_mouth::question:
-----------------------------
.vimrc is a file that allows user to configure personal setting in vim. It exists in the `$HOME` directory in Unix. After install our pre-configured vim, you will get a .vimrc file with all the configurations that we think are useful. Feel free to comment out or take in any configurations that you want. 

Plugin:
-------
Plugin is a vim script file that will load automatically when vim starts. Most plugins are usefule features that people created to make vim more user-friendly and a lot of them are similar. Using plugins not only makes it easier and faster to code in vim, but it also personalizes the text editor for the programmer. Here we will introduce some plugins that are commonly used.

#####Modifications:
If the user wants to remove a plugin, just remove the directory of that plugin in the bundle directory. If the user wants to add a plugin, the first thing to do is to check whether the new plugin is compatible with the other plugins. If it is, simply install it by following the installation directions given by the creator. Depending on the plugin, the user may need to modify the .vimrc file to fit the plugins needs.

###Plugin #0 - Pathogen:
--------------------------
Pathogen is a plugin that will make installing other plugins easier. It also allows runtime files to be installed in their own private directories. Pathogen is not the only plugin manager, but it is the only one included here. There are many other plugin managers, but Pathogen appeared to be a more basic one.

Alternate Plugin Manager: [Github MarcWeber/vim-addon-manager] (https://github.com/MarcWeber/vim-addon-manager)
, [Github gmarik/Vundle.vim] (https://github.com/gmarik/Vundle.vim)
, [Github Shougo/neobundle.vim] (https://github.com/Shougo/neobundle.vim)

More info at: [Github tpope/vim-pathogen] (https://github.com/tpope/vim-pathogen)

###Plugin #1 - NERDtree:
-------------------------
NERDtree allows you to view your files and directories in the form of a tree. You can easily access your files by using the mouse or arrow keys this way. NERDtree is installed as well as tell you the many capabilities of NERDtree such as bookmarking directories/files. However, this tutorial will only cover how to view your files in a tree form :+1:. In this help page, type `:NERDTree *ONE OF YOUR ACTUAL DIRECTORIES`. On the left, it should now display all the directories inside your chosen directory. 

You can use the arrow keys to navigate between files/directories and press `<ENTER>` to read into it. To close NERDtree type `NERDTreeClose`. To open it again, type `:NERDTree *an EXISTING directory`.

![NT2](http://i.imgur.com/3OCe5YM.gif)

More info at: [Github scrooloose/nerdtree] (https://github.com/scrooloose/nerdtree)

###Plugin #2 - SuperTab:
--------------------------
SuperTab aids the user in quickly typing in strings of characters, but only already existing ones. This is useful for users that enjoy automatic text filling. By typing a few characters and pressing `<TAB>` the word will be filled automatically, unless there is more than one existing string with the same characters typed. In this situation, a list of words will be shown in which the user can choose the correct one.

![ST1](http://i.imgur.com/i12YWak.gif)

More info at: [Github ervandew/supertab] (https://github.com/ervandew/supertab)

###Plugin #3 - Solarized:
-------------------------
Solarized changes the colorscheme of the vim editor. Often times, the default is not the best. It can be extremely irritable when you cannot differentiate between different types of files in vim as well as the variety of things within source code. It is possible to change the font and customize the colors to your own
preference.

![Solarized2](http://i.imgur.com/HRqwlqz.png) ![Solarized3](http://i.imgur.com/sQKfCbm.png)

More info at: [Github altercation/vim-colors-solarized] (https://github.com/altercation/vim-colors-solarized)

Alternate color scheme: [Github sjl/badwolf] (https://github.com/sjl/badwolf/)
					, [Github tomasr/molokai] (https://github.com/tomasr/molokai)

###Plugin #4 - Syntastic:
---------------------------
Syntastic is a plugin which will save all programmers time. It detects for syntax errors BEFORE you even compile. As all programmers know, these errors happen by mistake all the time and can be annoying after receiving those thousands of other logic errors. A highly recommended plugin for anyone who hates searching through their code for one syntax error. Errors are identified only after everytime the file is saved. When highlighting a line of error, the error will be displayed at the bottom of the terminal. A line of error will be show with `>>` next
to it.

![Syntastic](http://i.imgur.com/LPHf6U7.gif)

More info at: [Github scrooloose/syntastic] (https://github.com/scrooloose/syntastic)

###Plugin #5 - NERDcommenter:
-----------------------------
NERDcommenter is a plugin that makes commenting easier. It also makes removing comments easier. All of the commands should be done in either visual or normal mode. Type `\cc` to comment out the line highlighted by the cursor. 

	\ci  toggle the state of the highlighted lines. 
	\cu  uncomment the line that the cursor is highlighting. 
	\cs  comment the highlighted using /* and */ rather than the ordinary //

![NC1](http://i.imgur.com/BU8Ffmg.gif) ![NC2](http://i.imgur.com/C7ZMtP7.gif)

More info at: [Github scrooloose/nerdcommenter] (https://github.com/scrooloose/nerdcommenter)

###Plugin #6 - Surround:
------------------------
Surround aids the user in adding, changing or deleting mappings. This includes parentheses, brackets and more. 

	cs[first character][second character] 
			replace occurences of the first character with the second character 
			on the highlighted string of characters 
	
	ds" 
			remove the delimiters

	yssb or yss)
			surround an entire line with parentheses 

![Surround1](http://i.imgur.com/7BjSTfR.gif) ![Surround2](http://i.imgur.com/upeOBA1.gif)

![Surround3](http://i.imgur.com/Ep8zeqz.gif) ![Surround4](http://i.imgur.com/VdIhp6T.gif)

More info at: [Github tpope/vim-surround] (https://github.com/tpope/vim-surround)

###Plugin #7 - EasyMotion:
--------------------------
EasyMotion helps you make large jump within a buffer easier and faster. It allows you to make jumps by searching up your destination. 

For one character search, enter `<leader><leader>w` (in vim, `<leader>` means `\`). A word `Target:` will appear in the commadn bar .Enter any character you want to search and EasyMotion will highlight all the appearances of the character in the buffer. Enter the one you want to jump to and EasyMotion will take you there.

![EasyMotionW](http://i.imgur.com/OuA4tDm.gif)

EasyMotion also supports word search. To do this, add two configurations to your .vimrc file. 
	
	map / <Plug>(easymotion-sn)
	omap / <Plug>(easymotion-tn)

After adding the configurations, you can search up word the way you do it in vim and EasyMotion will highlight the word for you.

![EasyMotionN] (http://imgur.com/DVc9xzl.gif)

For more EasyMotion configuration and explanation, go to [Github Lokaltog/vim-easymotion] (https://github.com/Lokaltog/vim-easymotion)

###Plugin #8 - Gundo:
---------------------
In vim, all the changes you make to your file are save as a tree. Gundo is a plugin that graph your vim undo tree for you so you can easily see the differences between the changes you made and jump back to any old version. 

To use Gundo, first you have to add a mapping to your .vimrc file. Here we use `<F5>` as example. 

	nnoremap <F5> :GUndoToggle<CR>

Now when we press `<F5>` in a file, Gundo will show us a graph of the tree of changes. Our current position in the undo tree is the one marker with `@`. To move between the graph, use `j` and `k` keys. Like vim, `gg` jumps to top of the file while `G` brings you ot the bottom of the file.  

Press `return` on a state to revert the content of the file and use `p` to make the preview window show the differences between current state and selected state. 

![Gundo](http://imgur.com/CJcWY8a.gif)

To quit the undo tree, press `q`. 

For more explanation on Gundo, go to [Gundo: Graph your Vim undo tree in style.] (http://sjl.bitbucket.org/gundo.vim/)

###Plugin #9 - Fugitive:
------------------------
As a git user, fugitive is probably the most useful plugin in this tutorial. It is a Git wrapper that collects and creates a lot of shortcuts of git. With fugitive, user can add, push, commit, checkout status or branches, and do any other things that they can do with `git`, but a lot faster. 

To make it easier, here are a list of fugitive commands:
	
	:Gstatus	git status
	:Gwrite		git add (filename)
	:Gcommit	git commit
	:Gblame		git blame
	:Gmove		git mv
	:Ggrep		git grep
	:Gread		git checkout --filename

The gif belows demonstrates how I check the status using :Gstatus, add my README.md using :Gwrite, commit the file using :Gcommit, and push the file to my repo using :Gpush.

![fugitive](http://imgur.com/Vqxu02C.gif)

For more explanation on `Fugitive`, go to [Github tpope/vim-fugitive] (https://github.com/tpope/vim-fugitive)


