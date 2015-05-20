#VIMSCRIPT

_Note:_ for complete documentation on vimscript, type `:help usr_41.txt` in a vim environment to view the official vim manual explaining vimscript. 

##What is Vimscript

Vimscript is a scripting language for vim used for customizing and extending your vim text editor.  

With vimscript, you can create scripts that can set color schemes, add automatic indenting, and add spell-checking to name a few of the possibilities. 

Vimscript is also known as vim script and viml. 

Vim can shine once you take the time to customize it for your particular works, habits, and typing using vimscript.

##Let's Get Started

In this tutorial, we will be editing our `.vimrc` file to do some useful things.

Access your `.vimrc` file by entering `vim ~/.vimrc` in the command line.

###Mapping

Mapping allows you to customize the functionality of what each of your keys do in any vim file.

Currently, when you are in normal mode, typing `dd` will delete the line the cursor is on.

Since typing two letters to delete a line is quite a burden, we will map the letter `m` to `dd` by insterting the following:

    map m dd

Now, if you type `m` in normal mode, the line the cursor is on will get deleted as if `dd` had been typed.

You can tell vim to be more specific about where to map these keys by using `nmap`, `vmap`, and `imap`.

* `map` by default will map keys in _normal mode_

* `nmap` will map keys in _normal mode_

* `vmap` will map keys in _visual mode_

* `imap` will map keys in _insert mode_

We will now map `a` in visual mode to select all text in the file below the cursor and yank it by using the command `Gy`:

    map m dd
    vmap a Gy

Now, if you type `a` in visual mode, all lines below the cursor will have been yanked.

To map a special character, you need to surround the key type with`<` and `>`.

Examples of common special characters include:

* <space> for the space bar

* <esc> for the escape button

* <tab> for the tab button

* <enter> for the enter button

* <c-_key_> for control + any _key_

We will map `CTRL+i` to typing out `#include` in insert mode:

	map m dd
    vmap a Gy
    imap <c-i> #include 

###Abbreviations

Abbreviations allow us to type in insert mode more efficiently by entering a few letters that vim will immediately replace by what you have specified.

We will abbreviate `Mark was here` to `LOL`:

    map m dd
    vmap a Gy
    imap <c-i> #include 
    iabbrev LOL Mark was here

Now, whenever we have finished typing `LOL` in insert mode, the entire word will get replaced by `Mark was here`.

###Autocommands

With autocommands, you can specify which commands can execute automatically when reading or writing a file, when entering or leaving a buffer or window, and when exiting vim.

We will create an autocommand that will give a friendly welcome whenever a user enters vim:

    map m dd
    vmap a Gy
    imap <c-i> #include 
    iabbrev LOL Mark was here
    autocmd VimEnter * echo "Welcome to vim :)"

`VimEnter` tells `autocmd` to run the `echo` command after the user enters vim.

Now, if you enter any vim environment, you will be greeted with `Welcome to vim :)` at the bottom of the page.

###Conditional Statements

Conditional statements can be constructed with vimscript with the use of `if`, `elseif`, and `else` statements followed by an `endif` to close the condition.

We will construct a conditional statement that will change our vim background to light and dark according to the time of day:

    map m dd
    vmap a Gy
    imap <c-i> #include 
    iabbrev LOL Mark was here
    autocmd VimEnter * echo "Welcome to vim :)"

    if strftime("%H") < 12
    	set background=light
    else
    	set background=dark
    endif

If our time function returns a number less than `12`, then we set the background to `light` - otherwise to `dark`.

##Conclusion

With these vimscript commands, you can unleash the customization powers held within vim that make it a very popular text editor.  

To view official documentation on vimscript and to find out more on vimscript's functoinality, type `:help usr_41.txt` in a vim environment.
