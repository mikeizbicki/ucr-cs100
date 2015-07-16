#VIMSCRIPT

Vimscript is a scripting language for vim used for customizing and extending your vim text editor.
With vimscript, you can create scripts that can set color schemes, add automatic indenting, and add spell-checking to name a few of the possibilities.
Vim can shine once you take the time to customize it for your particular works, habits, and typing using vimscript.

Vimscript is also known as vim script and viml.

##Let's Get Started

In this tutorial, we will be editing our `.vimrc` file to do some useful things.

Access your `.vimrc` file by entering `vim ~/.vimrc` in the command line.

###Mapping

Mapping allows you to customize the functionality of what each of your keys do in any vim file.

Currently, when you are in normal mode, it takes several key strokes to yank your entire document.
To facilitate the process, we will map the letter `z` to commands responsible for highlighting and yanking an entire document:

    map z ggvG$y

Now, if you type `z` in normal mode, your entire document will get yanked.

You can tell vim to be more specific about where to map these keys by using `nmap`, `vmap`, and `imap`.

* `map` by default will map keys in _normal mode_

* `nmap` will map keys in _normal mode_

* `vmap` will map keys in _visual mode_

* `imap` will map keys in _insert mode_

To map a special character, you need to surround the key type with`<` and `>`.

Examples of common special characters include:

* `<space>` for the space bar

* `<esc>` for the escape button

* `<tab>` for the tab button

* `<enter>` for the enter button

* `<c-KEY>` for control + any `KEY`

We will map `CTRL+i` to typing out `#include` in insert mode:

    imap <c-i> #include 

Here are more commonly used maps that use special characters:

* Toggle spell check

    `nmap <F5> :set spell!<enter>`

* Comment a line by adding `//`

    `nmap <F2> ^i//<esc>`

* Uncomment a line

    `nmap <F3> ^2x`

* Yank a whole line

    `nmap Z ^v$y`

* Indent the current line

    `nmap t ^i<tab><esc>` 

###Commenting

Use the `"` character to comment in vimscript.
Everything after and including the `"` character will be considered a comment and will be ignored until the end of the line is reached.

However, there are special cases where commands preceding the `"` will not interpret `"` as the start of a comment.
To avoid these special cases, it is best to start comments on entirely separate lines.

We will use a previous example to show the safe means of including comments in vimscript

    "map CTRL i to type out #include in insert mode
    imap <c-i> #include

###Functions

Vimscript can use functions to execute specific tasks when called to make coding much cleaner.

Syntax for a vimscript function include `fun! FUNCTION NAME(PARAMETERS)` to declare a function, `return VALUE` to return a value, `endfun` to indicate the end of your function, and `call FUNCTION NAME` to call your function.

We will create another function that will delete trailing spaces in an entire file.

    fun! RmTrailSpaces()
        %s/\s\+$//ge
        noh
    endfun

Now, if we call `RmTrailSpaces`, all spaces characters that follow the end of a line will be removed.

In detail, this is how the `%s/\s\+$//ge` works:

* `%` apply command to the entire file

* `s/` search and replace

* `\s\+$` regular expression to find single or multiples spaces after the end of a line

* `//` replace with an empty string

* `ge` take the cursor back to the end of a word

* `noh` removes any vim highlighting caused by trailing spaces

We will demonstrate the handiness of functions in vimscript in the following sections. 

###Autocommands

With autocommands, you can specify which commands can execute automatically when reading or writing a file, when entering or leaving a buffer or window, and when exiting vim.

We will create autocommands that will use our `RmTrailSpaces()` function whenever we save a `.c` or `.cpp` file:

    autocmd BufWrite *.c call RmTrailSpaces()
    autocmd BufWrite *.cpp call RmTrailSpaces()

By using functions, we coded these two autocommands simply by using an easy to remember function name as opposed to memorizing the complex series of commands that delete trailing spaces.

`BufWrite` tells `autocmd` to call our `RmTrailSpaces()` function once the user saves a `.c` or `.cpp` file.

Now, we will use `autocmd` again to automatically indent `.cpp` files according to the standard C++ style upon entering vim.

    autocmd VimEnter *.cpp set cindent

`VimEnter` tells `automcd` to set `cindent` on for `.cpp` filetypes upon entering vim.

###Conditional Statements

Conditional statements can be constructed with vimscript with the use of `if`, `elseif`, and `else` statements followed by an `endif` to close the condition.
                                                                                                                
We will construct a conditional statement that will change our vim background to light and dark according to the time of day:

    if strftime("%H") < 12
        set background=light
    else
        set background=dark
    endif

`strftime()` is an internal vim function that returns a date and time string.
Arguments passed into `strftime()` modify the outputted string.
With `%H` returning the current hour, if our time function returns a number less than `12`, we then set the background to `light` - otherwise to `dark`.

Now, we will construct a function with conditional statements that will change our vim colorscheme according to the filetype and use it with an autocommand:

    fun VimColorMe()
        if &filetype == 'cpp'
            colorscheme ron 
        elseif &filetype == 'modula2'
            colorscheme slate
        else
            colorscheme default
        endif
    endfun
    
    autocmd VimEnter * call VimColorMe()

Here, upon entering vim, the autocommand calls our function `VimColorMe()` and, based off of the filetype, changes the colorscheme.

###Abbreviations

Lastly, abbreviations allow us to type in insert mode more efficiently by entering a few letters that vim will immediately replace by what you have specified.

We will abbreviate `@@` to my email:

    iabbrev @@ youremail@mail.com

Now, whenever we have finished typing `@@` in insert mode, the entire word will get replaced by your email address (this can be replaced with any other text).

Now, we will abbreviate `copyR` to a lengthy string containing standard copyright information:

    iabbrev copyR Copyright 2015 Mark Asfour, all rights reserved

Other common uses for abbreviations include automatic spelling fixes for words you know you commonly misspell.
Here are examples of using abbreviations for some of the most commonly misspelled words:

    iabbrev definately definitely
    iabbrev alot a lot
    iabbrev wierd weird
    iabbrev recieve receive  
    iabbrev thier their

##Conclusion

With these vimscript commands, you can unleash the customization powers held within vim that make it a very popular text editor.  

To view official documentation on vimscript and to find out more on vimscript's functionality, type `:help usr_41.txt` in a vim environment.
