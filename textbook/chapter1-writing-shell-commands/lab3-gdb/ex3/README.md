###Exercise 3: debugging a real program

You're a progamming intern at the defense contractor HBHairy.
Your main job is to repackage a bunch of open source software.
HBHairy resells it to the navy for a premium.
But your CEO [managed to upset the hacker group Anonymous](http://www.networkworld.com/article/2183906/malware-cybercrime/anonymous-attack-on-hbgary-federal-didn-t-ruin-us--says-hbgary-ceo.html).
They've hacked into HBHairy's internal company servers and changed the code for the `ls` program!
Your job is to find and fix the changes they've made.

If you had been using version control, then this would be really easy.
You'd just run `git checkout` to go back to the last known good commit.
But your boss is an idiot, so none of the source code was version controlled.
Instead, you must use the `gdb` debugger to track down all of the bad code.

You will find all the source code in the file `hbhairy-utils.tar.xz`.
Lucky for you the hackers left the `INSTALL` file intact.

Known bugs:

* The first thing printed by `ls` is always `(null)`.

* `ls` prints the text `!!!WE ARE LEGION!!!`

* `ls` prints the text `lolololololololololololololololololololololol`

* Running `ls` turns the terminal red.

* Running `ls -a` prints the files separated by commas rather than the default behavior of printing a nice table.

* The `-a` flag no longer prints the `.` and `..` files as it is supposed to.  (HINT: `-a` is behaving like `-A`.)

* Running the command `ls --help` just prints the Anonymous logo mask and doesn't print any help information.

* Running `ls -R` quotes a Monty Python insult at you.

* Running `ls -R` segfaults.

* Running `ls -l` segfaults.

<!--

TA Message:

The original `ls.c` file is now called `omfg.c`.
If you run the command:

```
$ diff ls.c omfg.c
```

You can see where all the changes were made to the source.
The file `system.h` has a few macros added to it as well.

-->
