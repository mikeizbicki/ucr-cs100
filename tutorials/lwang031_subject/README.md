#Using Linux command easier

The 5 tricks people should know about linux command.
Note: these tricks apply to bash, which is the default shell on most Linux systems.

![Image of Yaktocat](https://octodex.github.com/images/yaktocat.png)




## 1. Special characters (need to know)

![special: need to know](http://blog.zeronana.info/katsuo/wp-content/uploads/2011/05/facebook_smileys.jpg)

Bash has many special characters such as `* & ; | { ! < [ #` (you see, all are special, don't think you know them). 
A commonly used example:

    find . -iname '*.conf'

Notice the single quotes around `*.conf`. What would happen without it? Bash would interpret the `*.conf` as a glob expression and expand it to all files ending in `.conf` in the current directory. (we don't want this to happen!) This could prevent from looking for all `.conf` files in subdirectories. Remember: we should always quote anything that 
might contain special characters.

It need to be known that only single quotes can prevent every character from being interpreted; double quotes still allow bash to interpret some characters. On the other hand, when working with variables, double quotes come in handy to prevent word splitting(it's useful!), which is often used in scripting. 
An example:

    #!/bin/bash
    # This script renames a file to lowercase
    newname="$(echo -n "$1" | tr '[A-Z]‘ ‘[a-z]‘)”
    mv -i “$1″ “$newname”

You can see quite a lot of double quotes in this script, and all of them are necessary to prevent trouble with certain 
filenames. You see, when a filename contains whitespace, bash splits the name on that whitespace when you leave 
variables unquoted. Suppose you have a file named `spaced name.txt`, you put it in a variable `filename=’spaced 
name.txt`, and then you try to move it to `unspacedname.txt` by executing `mv $filename unspacedname.txt`. You’ll get 
the error `mv: target `unspacedname.txt’ is not a directory`. This is because mv gets executed like this: `mv spaced 
name.txt unspacedname.txt`. In other words, mv will try to move two files, `spaced` and `name.txt` to `unspacedname.txt`, 
and fail because moving multiple files to a single destination is only allowed when the destination is a directory. 
Putting double quotes around “$filename” solves this issue.

So you see, quoting is a good habit to prevent your commands and scripts from doing unexpected things. Important message: you can’t quote variables using single quotes, because the dollar sign loses its special meaning between single quotes, and if you ever need to use a literal single quote in some command, you can do so by putting it between double quotes. 





## 2. Process Substitution: efficiency

![efficiency, all I care](http://1funny.com/wp-content/uploads/2009/07/efficient-truck-transport.jpg)

Think of showing differences of two commands quickly? One way is to redirect the output to a temporary file 
for both of them, and diff those files, like this:

    find /etc | sort > local_etc_files
    find /mnt/remote/etc | sort > remote_etc_files
    diff local_etc_files remote_etc_files
    rm local_etc_files remote_etc_files

This would tell you the differences between which files are in /etc on the local computer and a remote one. It takes
four lines.  However, it's not efficient! Using process substitution, we can do this is just a single line. Amazing!

    diff <(find /etc | sort) <(find /mnt/remote/etc | sort)

What does `<(…)` do? It means “run the command inside it, connect the output to a temporary pipe file and give
that as an argument”. To understand this more thoroughly, try running this:

    echo <(echo test)

Instead of printing “test”, this will print something like “/dev/fd/63″. You see now that the `<(…)` is actually 
replaced by a file. This file is a stream from which the output of the command inside `<(…)` can be read, like this:

    cat <(echo test)

Now this does print `test`! Bash redirects the output of `echo test` to /dev/fd/<something>, gives the path of that
file to cat, and cat reads the output of echo from that file. The shortened diff command above does the same (plus it's 
much shorter), only for two slightly more complicated commands. This technique can be applied in any place where a 
temporary file is needed, but it does have a limitation. The temporary file can only be read once before it 
disappears. 




## 3. The xargs command: | pipe

![pipe](http://s2.quickmeme.com/img/22/22ef8cbb2e7a7f12e74e84410d45cc4472f53326606bfb04fc06a6a139ad2bba.jpg)

![pipe2](http://s2.quickmeme.com/img/3a/3a9d6b1156b541478db586f6b0b2843bd4da082a8f26b399e5b658ea8811b7f4.jpg)

Whenever you want to execute a command on multiple files, or for every line of a certain file, xargs is the first tool 
to look at. Here’s an example:

    find . -iname ‘*.php’ -print0 | xargs -0 svn add
A version control system like svn probably annoys of having to add every newly created code file after a few hours of editing. This command does it for you in an instant. How does it work?

`find . -iname *.php -print0` prints all files in the current directory `.` or its subdirectories that end in `.php` 
and separates them by null characters `-print0`. The null character is never used in filenames, while a newline may be
, so it is safer to separate by null characters.

`xargs -0 svn add` receives the output of find on its standard input through the pipe `|`, separates it by null 
characters `-0` and feeds the filenames as arguments to svn, after the `add` argument. It minds the limits the system 
imposes on the amount and size of command line arguments, and will run svn multiple times as necessary while still 
invoking it as few times as possible.

To find out more about xargs, read the man page by executing `man xargs`. Using xargs is safer and more versatile than 
using the `-exec` option of find. 




## 4. Ctrl+U and Ctrl+Y: backup command

![backup always userful](http://www.yoyoshare.com/wp-content/uploads/images/culture/80.jpg)

Do you know that moment when you’re typing a long command.

    cd 1/2/3/4/5/6/7....(# represents super long names "1 = safjslfjsaflfj") 
and then suddenly realize you need to execute something else 
first (Oh, what's the next path...). Everyone hate this! Fortunately, there's a way to fix it. Ensure cursor is at the end of your current command `shortcut: Ctrl+E`, press `Ctrl+U` to get a clean line,

    ^E (copy the current command)
    ^U (clear the current command)
    ls (check the direc you want)
    ^Y (paste the older command)
    $: cd 1/2/3/4/5/6/7..... (Yeah, the command is back)
type the other command you need to execute first, execute it, then press `Ctrl+Y` and amazing! Your long command is back on the line. No mouse needed for copying, just quick hotkeys.
Great tricks!!





## 5. A simple calculator

![calculator important sometimes](http://s8.postimg.org/i68lvk1b9/4840184_700b_v1.jpg)

Sometimes you need to do a calculation that is too much for your brain. When you’re working in a graphic environment, 
you might just fire up kcalc or gcalctool, but tools like that may not always be available or easy to find. Fortunately,
you can do basic calculations within bash itself. 
For example:

    echo $((3*37+12)) # Outputs 123
    echo $((2**16-1)) # Two to the power of sixteen minus one; outputs 65535
    echo $((103/10)) # Outputs 10, as all these operations are integer arithmetic
    echo $((103%10)) # Outputs 3, which is the remainder of 103 divided by 10

`$((something))` also allows bitwise operations (what?!), and as such it interprets the `^` as a bitwise 
operator. That’s why `**` means  “the power of”. The syntax also supports showing the decimal equivalent of a 
hexadecimal or octal number. 
Here’s an example:

    echo $((0xdeadbeef)) # Outputs 3735928559
    echo $((0127)) # Outputs 87

For more information, read the bash man page (always a good choice, you can do it on both terminal or online) using `man bash` and search using `/` for “arithmetic evaluation”. If you want to do floating point calculations, 
you can use `bc`:

    echo ‘scale=12; 2.5*2.5′ | bc # Outputs 6.25
    echo ‘scale=12; sqrt(14)’ | bc # Outputs 3.741657386773

Note the setting of the scale variable. with bc, you can perform floating point operations with any precision you like.
The scale variable controls the amount of decimals behind the dot that are calculated. Using 12 here because `kcalc` 
uses that amount by default, but you can increase or decrease it as you like. Find out more about what bc can do by 
executing `man bc`(remember, always a good choice). It even supports more advanced mathematical functions, such as the arctangent or the natural 
logarithm!

![Make life easier](http://www.chronic-illness.org/images/making_life_easier.jpg)

