# More about Vim
This tutorial will go a little bit in-depth about some more features in Vim.
We will cover tabs, viewports, and sessions, as well as the file explorer and command execution within Vim.

### Tabs

#### Starting up

![Opening Tabs] (images/newtab.gif)

When starting Vim with multiple files, we can use the `-p` flag in order to open up all of the files in tabs.
```
vim -p src/rshell.cpp README.md Makefile
```

![Open with Tabs] (images/openwithtabs.gif)

#### Creating tabs

We can create new tabs by using the `:tabe` function.
You can specify a filename after calling the `tabe` command in order to open that file in a new tab.
```
:tabe
:tabe README.md
```

You can only specify one file at a time when opening a new tab.

#### Navigating and moving tabs

![Navigating and Moving Tabs] (images/movingtabs.gif)

To navigate around each tab, we can either type out `:tabn` or `:tabp` multiple times in order to navigate.
Alternatively we can use the `gt` and `gT` commands to quickly traverse through multiple tabs.
We can also specify a number `i` using `igT` in order to go to a specific tab number.

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

You can close tabs as you would close Vim by calling the `:q` command, the `:tabclose` command, or even the `:tabclose i` command to close the `i-th` tab.

### Viewports

#### Creating viewports

![Creating Viewports] (images/viewports.gif)

If you want to view one or more files on a single screen at the same time, then `:split` and `:vsplit` will allow you to split to screen in order to view multiple files.
Splitting views can be useful when you need to refer to multiple files at once.
This can be useful when reading a header file and its implementation, or viewing different parts of a larger file.

```
:split
:vsplit
:sp
:vsp
```

You can specify a filename to have that viewport open the file.
Otherwise it will open up another view of the current file.
Closing these viewports can be done in the same manner as closing tabs (`:q`).

#### Navigating and adjusting viewports

![Adjusting Viewports] (images/adjustvp.gif)

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

Like many other Vim commands, most of these can have a number prefixed to them in order to repeat the command that many times.

### The `Explore` command
![Explore] (images/explore.gif)

The `:Explore` command allows you to look through your filesystem in order to open a specific file.
This also allows you to rename, move, or even delete other files.

![Explore edit] (images/exploreedit.gif)

To create a file, type `%` and type in the name of the file you want to create.
To delete a file, type `D` while selecting the file you want to delete.
To rename a file, type `R` while selecting the file you want to rename.
You can also change how the files are sorted by using the `s` key.

### Running `bash` commands in Vim
![Running in Vim] (images/make.gif)

You can run `bash` commands without having to suspend Vim to the background.
Just go into command mode, and then type a `!` before your command.
This will cause those commands to be executed as if you were using `bash`.
This is convenient if you want to compile and immediately execute your program after editing it.

```
:!<command>
:!make
:!make && ./a.out
```
While running `bash` commands in Vim, the `%` character will be the same as the current filename.
This can let you easily make a bindable command that compiles and runs your program on success.
```
:!g++ % -o foo && ./foo
```

### Saving Vim sessions

![Saving sessions] (images/sessions.gif)
While you can keep opening tabs and viewports, they will disappear when Vim is closed.
You might have 20-30 files open, and having to both open and adjust them every time can be cumbersome.
If you want to keep the current Vim workspace, you can use the `:mksession` command.
```
:mksession current_session.vim
```
To restore it, you use the `:source` command, or open the `.vim` file with the `-S` flag.
```
:source current_session.vim
vim -S current_session.vim
```
By saving Vim sessions, you can quickly resume work on a large number of files without having to reconfigure your workspace.

# Closing
Effective usage of the above commands can make Vim more convenient for you.
Using tabs and viewports can allow you to easily navigate and work with several files.
Exploring the filesystem is convenient if you need to quickly modify a specific file.
Executing commands within Vim can let you see immediate results.
Saving Vim sessions can help you quickly get back to where you were before you left.
If you want to learn more about Vim, you can start by learning some [Vimscript](http://learnvimscriptthehardway.stevelosh.com).
