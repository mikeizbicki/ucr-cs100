# Advanced Vim Usage
This tutorial will go a little bit in-depth about some more features in Vim, covering tabs, viewports, and sessions.

### Tabs

#### Starting up

![Opening Tabs] (gifs/newtab.gif)

When starting Vim with multiple files, we can use the `-p` flag in order to open up all of the files in tabs.
```
vim -p src/rshell.cpp README.md Makefile
```

![Open with Tabs] (gifs/openwithtabs.gif)

#### Creating tabs

We can create new tabs by using the `:tabe` function. You can specify a filename after calling the `tabe` command in order to open that file in a new tab.
```
:tabe
:tabe README.md
```

You can only specify one file at a time when opening a new tab.

To navigate around each tab, we can either type out `:tabn` or `:tabp` multiple times in order to navigate.
Alternatively we can use the `gt` and `gT` commands to quickly traverse through multiple tabs.
We can also specify a number `i` using `igT` in order to go to a specific tab number.

#### Navigating and moving tabs

![Navigating and Moving Tabs] (gifs/movingtabs.gif)

If you want to move tabs around, use the `tabm i` command where `i` is a number in order to move the tab to that position.
Not specifying a number will move the tab to the last position.

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

![Creating Viewports] (gifs/viewports.gif)

If you want to view one or more files on a single screen at a time, then `:split` and `:vsplit` will allow you to split to screen to view multiple files.
Splitting views can be useful when you need to refer to multiple files at once, such as referring to a header file and its implementation.

```
:split
:vsplit
:sp
:vsp
```

You can specify a filename to automatically have that view open the supplied filename.
Otherwise it will open up another view of the current file.
Closing these viewports would be the same as closing tabs.

#### Navigating and adjusting viewports

![Adjusting Viewports] (gifs/adjustvp.gif)

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

### Running `bash` commands in Vim
![Running in Vim] (gifs/make.gif)

You can run `bash` commands in Vim without having to put it in the background.
Just go into command mode, and then type a `!` before your command.
This will cause those commands to be executed as if you were using `bash`.
This is convenient if you want to compile and immediately execute your program.

```
:!<command>
:!make
:!make && ./a.out
```
While running `bash` commands in Vim, the `%` character will be the same as the current file.
This can let you easily make a bindable command that compiles and runs your program on success.
```
:!g++ % -o foo && ./foo
```

### Saving Vim sessions

![Saving sessions] (gifs/sessions.gif)
While you can keep opening tabs and viewports, they will disappear when its closed.
You might have 20-30 files open, and having to open and close them multiple times can be very annoying.
If you want to keep the current vim session, you can use the `:mksession` command.
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
This is barely a mere step into the world of Vim.
If you want to learn more about Vim, you can start off by learning some [Vimscript](http://learnvimscriptthehardway.stevelosh.com).
You can also take a look at other `.vimrc` files to see what they've done, and attempt to implement them into your own.
While you might get a few snazzy commands from others, the important thing to do in Vim is to figure out what's best for you, and customize your own settings accordingly.
