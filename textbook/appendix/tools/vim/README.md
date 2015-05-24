# More about Vim
This tutorial will go a little in-depth about some more features in Vim.
We will cover tabs, viewports, and sessions, as well as the file explorer and shell command execution within Vim.

### Tabs
In Vim, tab pages allow you to edit multiple files in a single window.

In the following gif, I start up Vim with the `-p` flag and several files in order to open them in new tabs.
Then, I navigate them using the `:tabn` and `:tabp` colon commands.

![Open with Tabs] (images/openwithtabs.gif)

#### Starting up

When starting Vim with multiple files, we can use the `-p` flag in order to open up all of the files in tabs.

```
$ vim -p src/rshell.cpp README.md Makefile
```

We can create new tabs by using the `:tabe` colon command.
You can specify a filename after calling the `:tabe` colon command in order to open that file in a new tab.

```
:tabe
:tabe README.md
```

You can only specify one file at a time when opening a new tab.

In the following gif, I start by opening my `rshell.cpp` file.
Then I use the `:tabe` colon command to open a new blank tab.
I then open my `mv.cpp` file by using the command `:tabe mv.cpp`.

![Opening new Tabs] (images/newtab.gif)

#### Navigating and moving tabs

To navigate between tabs, we can enter the colon commands `:tabn` or `:tabp`.
Alternatively we can use the `gt` and `gT` normal mode commands to quickly traverse through tabs.
Just like many other normal mode commands, you can also prepend a number `i` as in `igT` in order to go to a specific tab number.

Use the `:tabm i` colon command to move the current tab to after `i-th` position.
Not specifying a number will move the tab to the last position.

In the following gif, I open all of my `.cpp` files in tabs and navigate through them using the `gt` and `gT` normal mode commands.
I then go to my `rshell.cpp` file and move the tab by using the `:tabm` colon commands.
Finally, I finish by closing tabs with a combination of the `:tabclose` colon command and the standard `:q` colon command.

Note that the normal mode commands are shown in the bottom-right corner.

![Navigating and Moving Tabs] (images/movingtabs.gif)

The following table summarizes the tab-related commands and their effects.

| Command       | Effect                                                |
|-----------    |-----------------------------------------------------  |
| `:tabe`       | Creates a new tab.                                    |
| `:tabe <file>`| Opens a tab with the specified file.                  |
| `:tabn`       | Goes to the next tab.                                 |
| `:tabp`       | Goes to the previous tab.                             |
| `gt`          | Goes to the next tab.                                 |
| `gT`          | Goes to the previous tab.                             |
| `igt`         | Goes to the 'i-th' tab.                               |
| `:tabm`       | Moves the current tab to the end of all other tabs.   |
| `:tabm i`     | Moves the current tab to after 'i-th' position.       |
| `:tabclose`   | Closes the current tab.                               |
| `:tabclose i` | Closes the `i-th` tab.                                |

### Viewports

Viewports are another way to view multiple files in a single window.
Unlike tabs, viewports allow you to view multiple files at the same time.
This can be useful when reading a header file and its implementation, or viewing different parts of a larger file.

In the following gif, I create several viewports and open different files in each of them.
I then navigate through them with the standard normal mode commands such as `<C-w>w` and `<C-w>j`.
The `<C-w>` notation means pressing the control and w keys simultaneously.

![Creating Viewports] (images/viewports.gif)

To create a viewport, you can use either the `:split` and `:vsplit` colon commands.

You can specify a filename to have that viewport open the file.
Otherwise it will open up another view of the current file.
Closing these viewports can be done in the same manner as closing tabs (`:q`).

The following table summarizes the viewport-related commands and their effects.

| Command           | Effect                                                        |
|-----------        |-----------------------------------------------------------    |
| `:split`          | Creates a new viewport horizontally.                          |
| `:split <file>`   | Creates a new viewport horizontally with the specified file.  |
| `:vsplit`         | Creates a new viewport vertically.                            |
| `:vsplit <file>`  | Creates a new viewport vertically with the specified file.    |
| `:sp`             | Creates a new viewport horizontally.                          |
| `:vsp`            | Creates a new viewport vertically.                            |

#### Navigating and adjusting viewports

In the following gif, I open multiple viewports and adjust their sizes.

![Adjusting Viewports] (images/adjustvp.gif)

The following normal mode commands allow you to navigate and adjust viewports.

| Command       | Effect                                                            |
|-------------- |---------------------------------------------------------------    |
| `<C-w><C-w>`  | Moves between viewports.                                          |
| `<C-w>h`      | Moves to the left viewport.                                       |
| `<C-w>j`      | Moves to the below viewport.                                      |
| `<C-w>k`      | Moves to the above viewport.                                      |
| `<C-w>l`      | Moves to the right viewport.                                      |
| `<C-w> r`     | Rotates viewports to the right.                                   |
| `<C-w>R`      | Rotates viewports to the left.                                    |
| `<C-w>=`      | Equalizes the size of viewports.                                  |
| `<C-w>+`      | Increases the number of lines in the current viewport by 1.       |
| `<C-w>-`      | Decreases the number of lines in the current viewport by 1.       |
| `<C-w>>`      | Increases the number of columns in the current viewport by 1.     |
| `<C-w><`      | Decreases the number of columns in the current viewport by 1.     |

Like many other Vim normal mode commands, most of these can have a number prefixed to them in order to repeat the command that many times.
For example, if we want to increase the width of my current viewport by 5 columns, we can enter `5<C-w>>`.

### The `Explore` command

The `:Explore` colon command opens Vim's file explorer, which allows you to browse your filesystem from the current file's location.
This can also be done by using `:tabe <directory>`, which will open the file explorer with the given directory.
We can get the same effect as `:Explore` by using `:tabe .`, which opens a tab from our current directory.
The file explorer also allows you to rename, move, or even delete other files.

In the following gif, I use both `:Explore` and `:tabe .` to open my `rshell.cpp` file and a `Makefile`.

![Explore] (images/explore.gif)

The following table shows commands to modify files from within the file explorer.

| Command   | Effect                            |
|---------  |-------------------------------    |
| %         | Creates a file.                   |
| D         | Deletes the selected file.        |
| R         | Renames the selected file.        |
| s         | Changes how files are sorted.     |

In the following gif, I use the Explore feature to create a file, rename it, and delete it.

![Explore edit] (images/exploreedit.gif)

### Running shell commands in Vim

You can run shell commands without having to suspend Vim to the background.
Simply go into colon command mode, and then enter a `!` before your command.
This will cause those commands to be executed from your current shell.
This is convenient if you want to compile and immediately execute your program after editing it.

```
:!<command>
:!make
:!make && ./a.out
```

While running shell commands in Vim, the `%` character will be the same as the current filename.
To get the filename without the extension, you can use `%:r`.
This can let you easily make a bindable colon command that compiles and runs your program on success.
For example, if we wanted `F5` to run `make` and then run our program, we could use the following:

```
:nnoremap <F5> !make && ./%:r
```

In the following gif, I write a simple hello world program and create a `Makefile` in a separate viewport.
I then compile and run the program from within Vim with the `:!` colon command.

![Running in Vim] (images/make.gif)

### Saving Vim sessions

Open tabs and viewports will disappear when Vim is closed.
Having to both open and adjust 20-30 files every time can be cumbersome.
If you want to keep the current Vim workspace, you can use the `:mksession` colon command.

```
:mksession current_session.vim
```

To restore it, you use the `:source` colon command.
The colon command `:source` actually just runs all of the colon commands in the given file.
When you execute `:mksession`, Vim turns the current session into a Vimscript file.

```
:source current_session.vim
```

Alternatively, you can load the session on startup by passing Vim the `-S` flag and the session file.

```
$ vim -S current_session.vim
```

In the following gif, I open up many different viewports and tabs and use the `:mksessions` colon command to save my current session.
I then reload the session using both the startup `-S` flag when opening Vim and the `:source` colon command.

![Saving sessions] (images/sessions.gif)
