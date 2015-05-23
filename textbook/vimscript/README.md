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

You can map keys or combinations of keys to character sequences so that when you hit that key, you'll automatically perform the associated sequence.

Currently, when you are in normal mode, typing `dd` will delete the line the cursor is on.

Since typing two letters to delete a line is quite a burden, we will map the letter `m` to `dd` by insterting the following:

    map m dd

Now, if you type `m` in normal mode, the line the cursor is on will get deleted as if `dd` had been typed.

Let's map `q` to delete whatever word the cursor is currently on.
While a command like `dw` will delete until the end of the word, we might want a way to easily delete the word we are currently on.

```
:map q bdw

map <key> <result> - map the key to result
q - key to be remapped
b - back of current word
d - delete
w - go to next word
```

If we hover over anywhere in a word while we're in normal mode, hitting `q` will delete the word.
```
Mike Izbicki is a good b|ad programmer.
Mike Izbicki is a good |programmer.
```

While this is fine and dandy, mapping keys like this is a bad idea. Go into visual mode and you'll see a problem.

```
Mike Izbicki is a g|ood programmer.
Mike Izbicki is a od |programmer.
```

What happened? Vim did exactly what you wanted it to do!
Try going into visual mode, go into the middle of a word, and try typing `bdw`.
The exact sequence of characters will give the same result.
Essentially, Vim will interpret keys as literally as possible.

If we only want `q` to work in normal mode, we have to specify the mode that we are mapping to.

#### Mapping in specific modes

You can tell vim to be more specific about where to map these keys by using `nmap`, `vmap`, and `imap`.

* `map` by default will map keys in _normal mode_

* `nmap` will map keys in _normal mode_

* `vmap` will map keys in _visual mode_

* `imap` will map keys in _insert mode_

We can fix the previous command by interpreting typing this instead:

```
:nmap q bdw
```

`q` will then only perform delete words when in normal mode.

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
    
###Multiple character mapping

Now let's try to map something in insert mode.
Say we want access to deleting a word in insert mode as well! Instead of remapping `q` this time, we'll remap a sequence of characters so we can still type the `q` character.

```
:imap jk bdw
```

To access this mapping, quickly type `jk` while in insert mode.
(If at some point you really do need to type `jk`, just type them slowly).
You'll quickly see a problem with this mapping.

```
There ain't no such thing as a f|ree lunch.
There ain't no such thing as a fbdw|ree lunch.
```

Vim interpreted the keys as exactly as was stated, and typed in `bdw`.
If we want to actually map `jk` to `bdw`, we need to type exactly what we would normally press in order to delete the word.


#### Issues with `map`

While `map` is a powerful command that allows you to remap your keys, we will not be using it anymore.
There is a fundamental problem as to why `map` should not be used.

Say we decide to map `jj` to go down 4 lines.
(Yes, we could have just used 4j, but this is for an example.)
```
:nmap jj jjjj
```

Now, we get stuck in an infinite loop as `nmap` sees 2 pairs of `jj` and decides to run the `jj` keybinding which then sees another 2 pairs of `jj` and so on.

In order to fix this, we use the `*noremap` command.

```
:noremap
:nnoremap
:inoremap
:vnoremap
```

These will not use other mappings when you map keys to certain sequences.
In doing so, we guarantee that no infinite loops will occur from mapping keys to other keys.
This is also safer as it prevents conflicts with plugins that may use certain keys to automate certain tasks.
It is almost always better to use the `noremap` instead of `map`.

##### Unmapping keys
Sometimes we define a mapping that we don't actually want. To remove any sort of mappings, we use the `unmap` command, or the `*unmap` command where `*` is the mode.

```
:unmap f
:nunmap <space>
:iunmap jk
```

#### Seeing all mappings
We sometimes might want to see all of the mappings that are currently enabled.

```
:map
:map!
```

The first displays mappings in normal and visual mode, while the second displays maps in insert mode and command-line mode.
We can also specify which mode's mappings that we might want to see, and we can also put a character to see all mappings that begin with that character.

```
:imap f
```

This will display all mappings in insert mode that begin with `f`.

#### Prefix key
There aren't many keys by themselves that don't already have their own function.
However, we do not have enough keys on the keyboard for each one to have that many mappings.
The solution to this problem is having a Leader key that prepends your mappings.

```
let mapleader=","
:set inoremap <Leader>d <esc>ddi
```

First we set the Leader key to a some character.
In this example I chose the comma key.
Then, every time we set some mapping, we can prefix it with the `<Leader>` key.
This means that every time we press the sequence of the Leader key with whatever other key is associated, it will perform the mapping.
Setting the Leader key to a variable is useful as if we ever decide to change the prefix key,
we can change it just by simply setting the value of `mapleader` to whatever we want.

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
