# Advanced Vim Usage
One of the most powerful feature of Vim is its ability to be customized. You can remap keys, change its interface, and even add plugins to add completely new features! This tutorial will go a little bit in-depth about some more features in Vim. 

### Sourcing the `.vimrc`

The commands such as mapping keys in this tutorial can be run while in a Vim session, but won't be kept after you close Vim. If you want to keep the commands for future use, write them in your `~/.vimrc`. If you do edit your `.vimrc` while using Vim, you will not see any immediate changes. In order for the changes to take effect, you can either restart Vim, or run the command 
```
:source ~/.vimrc
```
in order to apply the changes. This does not necessarily have to be the `.vimrc` file in your home folder. It can be any file as long as it has a valid Vimscript syntax.

###Remapping keys
You can map keys or combinations of keys to character sequences so that when you hit that key, you'll automatically perform the associated sequence.

This can be done by using the `map` command. Mapping a key will cause it to perform exactly the same as if you had typed in the keys yourself. For example, let's map `q` to delete whatever word the cursor is currently on. While a command like `dw` will delete until the end of the word, we might want a way to easily delete the word we are currently on.

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

What happened? Vim did exactly what you wanted it to do! Try going into visual mode, go into the middle of a word, and try typing `bdw`. The exact sequence of characters will give the same result. Essentially, Vim will interpret keys as literally as possible. 

If we only want `q` to work in normal mode, we have to specify the mode that we are mapping to. We do this with the `*map` command, where `*` is any mode `n`, `i`, or `v`. For normal mode mapping, we use the `nmap` command.

```
:nmap q bdw
```

`q` will then only perform delete words when in normal mode. 

Now let's try to map something in insert mode. Say we want access to deleting a word in insert mode as well! Instead of remapping `q` this time, we'll remap a sequence of characters so we can still type the `q` character.

```
:imap jk bdw
```

To access this mapping, quickly type `jk` while in insert mode (If at some point you really do need to type `jk`, just type them slowly). You'll quickly see a problem with this mapping. 

```
There ain't no such thing as a f|ree lunch.
There ain't no such thing as a fbdw|ree lunch.
```

Vim interpreted the keys as exactly as was stated, and typed in `bdw`. If we want to actually map `jk` to `bdw`, we need to type exactly what we would normally press in order to delete the word.

```
:imap jk <esc>bdwi
```

The `<esc>` means the escape character. There are other such replacements for special characters, such as `<space>` for spaces or `<C-x>` for Ctrl-x. With this mapping, we exit out of insert mode, delete, and then go back into insert mode.

While `map` is a powerful command that allows you to remap your keys, we will not be using it anymore. There is a fundamental problem as to why `map` should not be used.

Say we decide to map `jj` to go down 4 lines. (Yes, we could have just used 4j, but this is for an example.)
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

These will not use other mappings when you map keys to certain sequences. In doing so, we guarantee that no infinite loops will occur from mapping keys to other keys. This is also safer as it prevents conflicts with plugins that may use certain keys to automate certain tasks. It is always safer to use the `noremap` instead of `map`. 

#### Other tidbits

##### Unmapping keys
Sometimes we define a mapping that we don't actually want. To remove any sort of mappings, we use the `unmap` command, or the `*unmap` command where `*` is the mode.

```
:unmap f
:nunmap <space>
:iunmap jk 
```

##### Seeing all mappings
We sometimes might want to see all of the mappings that are currently enabled.

```
:map
:map!
```

The first displays mappings in normal and visual mode, while the second displays maps in insert mode and command-line mode. We can also specify which mode's mappings that we might want to see, and we can also put a character to see all mappings that begin with that character.

```
:imap f
```

This will display all mappings in insert mode that begin with `f`.

##### Prefix key
There aren't many keys by themselves that don't already have their own function. However, we do not have enough keys on the keyboard for each one to have that many mappings. The solution to this problem is having a Leader key that prepends your mappings.

```
let mapleader=","
:set inoremap <Leader>d <esc>ddi
```

First we set the Leader key to a some character. In this example I chose the comma key. Then, every time we set some mapping, we can prefix it with the `<Leader>` key, which means that every time we press the sequence of the Leader key with whatever other key is associated, it will perform the mapping. Setting the Leader key to a variable is useful as if we ever decide to change the prefix key, we can change it just by simply setting the value of `mapleader` to whatever we want.

## Tabs, Viewports, and Sessions

Vim has built in support for multiple tabs and split views. 

### Tabs

#### Starting up

When starting Vim with multiple files, we can use the `-p` flag in order to open up all of the files in tabs. 
```
vim -p file1 file2 file3
```

#### Creating and Navigating tabs

We can create new tabs by using the `:tabe` function. You can specify a filename after calling the `tabe` command in order to open that file in a new tab.
```
:tabe 
:tabe fileIWantToOpen
```
You can only specify one file at a time when opening a new tab.

To navigate around each tab, we can either type out `:tabn` or `:tabp` multiple times in order to navigate, or we can use the `gt` and `gT` commands to quickly traverse through multiple tabs. We can also specify a number `i` using `igT` in order to go to a specific tab number. If you want to move tabs around, use the `tabm i` command where `i` is a number in order to move the tab to that position. Not specifying a number will move the tab to the last position.

```
:tabn
:tabp
gt
gT
igt
`tabm 
:tabm i
```

You can close tabs as you would when you close Vim by calling the `:q` command, the `:tabclose` command, or even the `:tabclose i` command to close the `i-th` tab.

### Viewports

#### Creating viewports

If you want to view one or more files on a single screen at a time, then `:split` and `:vsplit` will allow you to split to screen to view multiple files.

```
:split
:vsplit
```

You can specify a filename to automatically have that view open the supplied filename. Otherwise it will open up another view of the current file. Closing these viewports would be the same as closing tabs. 

#### Navigating and adjusting viewports
The following commands allow you to navigate and adjust viewports. The `<C-w>` notation means ctrl-w.
 
```
<C-w><C-w> - moves between viewports
<C-w> h - moves to the viewport left
<C-w> j - moves to the viewport below
<C-w> k - moves to the viewport above
<C-w> l - moves to the viewport right

<C-w> r - rotates viewports to the right
<C-w> R - rotates viewports to the left

<C-w> = equalizes the size of viewports
<C-w> + increases number of lines in viewport by 1
<C-w> - decreaes number of lines in viewport by 1
<C-w> > increases number of columns in viewport by 1
<C-w> < decreases number of columns in viewport by 1

```

Most of these commands can have a number prefixed to them in order to repeat the command that many times. 

### Saving Vim sessions
While you can keep opening tabs and viewports, they'll be gone when its closed. You might have 20-30 files ope, and having to open and close them multiple times can be very annoying. If you want to keep the current vim session, you can use the `:mksession` command.
```
:mksession current_session.vim
```

To restore it, you use the `:source` command, or open the `.vim` file with the `-S` flag.
```
:source current_session.vim
vim -S current_session.vim
```
By saving vim sessions, you can quickly resume work on a large number of files without having to reconfigure your workspace.

# Closing

This is barely a mere step into the world of Vim. If you want to learn more about Vim, you can start off by learning some [Vimscript](http://learnvimscriptthehardway.stevelosh.com). You can also take a look at other `.vimrc` files to see what they've done, and attempt to implement them into your own. While you might get a few snazzy commands from others, the important thing to do in Vim is to figure out what's best for you, and customize your own settings accordingly.
