#Using Linux command easier

The 10 tricks people should know about Linux command.
Note: these tricks apply to bash, which is the default shell on most Linux systems.

![Image of Yaktocat](https://octodex.github.com/images/yaktocat.png)



## 1. Manage files

![Image of office](http://res.sys-con.com/story/feb12/2153970/ManInMiddleOfPaperStacks_0_0.jpg)

One important and required skill for a Linux user is how efficiently create, copy and delete files and directories.

To create an empty file, type:

	$ touch filename.txt

Is always a good practice to write the extension of your file such as .txt, .c, .cpp or any other you might find useful.

To create a directory, type:

	$ mkdir dirname

The word "mkdir" stands for Make Directory. It is simple as that to use and remember.

Copying files is also an easy and straight forward command. You can copy a source or multiples into a directory, using the 'cp' command:

	$ cp file.txt newfile.txt
	$ cp lion.png my_dir
	$ cp file.txt newfile.txt my_dir
	$ cp -r pics my_dir

In the first example we are simply copying our 'file.txt' into our 'newfile.txt', following the pattern cp SOURCE DEST; The next command places a copy of an image named 'lion.png' into a directory; The third example we have multiple sources being placed inside the directory.

Remember the last parameter should always be our destination.

In the last example we are using the flag -r setting the 'cp' command as recursive. So in the fourth line we are copying the 'pics' directory and everything that has inside and copying it to 'my_dir'.

There are two basic commands to delete that you should know. The 'rm' and 'rmdir' commands, remove and remove directory respectively:

	$ rm file.txt
	$ rmdir my_dir

ATTENTION: The 'rmdir' command will only delete empty directories. In order to delete a whole directory full of useless documents, type:

	$ rm -rf my_dir

Passing -r flag refers to 'remove directories and their contents recursively'.
The -f flag stands for 'force' referring to 'ignore nonexistent files, never prompt'.




## 2. Getting help

![Image of Help](http://buildmoneyonthenet.com/wp-content/uploads/2014/08/YOU-NEED-HELP-MY-FRIEND.jpg)

It is not a shame to ask for help while using linux. Even for those experts using shell, there will always be a flag or maybe a command that causes headaches into their brilliant minds. So one of the best tips we could give you is about getting the help you need.

Let's pretend you want to use the 'mv' command, but you are afraid of losing files. Before you start you could type:

	$ mv --help

	or

	$ mv --h

A lot of information will be displayed in the terminal, and that can be boring for you to go over everything. To simplify your life you could filter the output by piping it and using the 'grep' command. As you are afraid of losing files, let's filter by "overwrite" word:

	$ mv --help | grep overwrite

You probably have only two sentences displayed on your screen. Now, use the commands with the appropriate flags and be happy!


Keeping the 'mv' command as example, another powerful way of getting help is through reading the manual. Often referred to as "man pages". You can find it easily on the internet. But in case some catastrophe happened with the internet and then you are no longer connected the easiest way to do it is typing:

	$ man mv

That would lead you the mv manual which has much more information than --help flag.




## 3. Using History

![Image of GOT](http://www.troll.me/images/boromir/pass-history-exam.jpg)

Shell keeps track of all yours previous typed commands. Accessing and using it can be a very good ally for beginners and also save you some typing time. First, let's use the command:

	$ history

It displays on your screen all your previous commands ordered by a sequential number. You can use this command just to remember something you typed days ago and now you need to run it again. Now, here is the trick. Once you know the number attached in your desired typed command or the position in the list you don't need to type it again. Just run:

	$ !622

In the example above I am running my 622th command which in my case is a 'ls -l'. Notice that shell is now adding 'ls -l' as my last command and not '!622'. Change that number by whatever you need.

Another way of running previous commands without typing it is by position:

	$ !-3

Running that command shell will run whatever you typed three commands ago. Pretend that you used a command but you forgot to run as super user. You could apply our last example adding the word 'sudo' in the beginning:

	$ sudo !-1

So instead of typing the long command all along let bash do it for you. Use that tip to set different flags as well.

#### 3.1 Configure your history

Another thing you should be aware of is that you can actually clean your tracks or make the usage of the 'history' easier for you:

	$ history -c

	$ HISTSIZE=0

These are three simple commands that you use and apply to your history. The first example using the -c flag clears your history.

The next command we are actually changing a variable related to the 'history' command settings.

HISTSIZE is related to how many commands you want to keep track of. Setting it to 0 we are actually disabling the function. If you want to re-enable, type a value different from 0.




## 4. find ( a powerful tool)

![find: powerful tool](http://funnystack.com/wp-content/uploads/2014/04/Funny-Horse-44.jpg)

The `find` command is used to fetch the positions of files you want on a Unix or Linux system.  `find` will search any set of directories you specify for files that match the supplied search criteria.  You can search for files by name, owner, group, type, permissions, date, and other criteria.  The search is recursive in that it will search all subdirectories too (very powerful, right ? ).  The syntax looks like this:

    find where-to-look criteria what-to-do
All arguments to find are optional, and there are defaults for all parts.

    $ find #will display the pathnames of all files in the current directory and all subdirectories
    $ find . -print
    $ find -print
    $ find .
    (we four are same actually...)
Next we will search the whole system for any files named "foo" and display their pathnames.  `‑name` with the argument "foo" to tell `find` to perform a name search for the filename "foo".

    $ find / -name foo  #give us 3 results
    /home/wpollock/foo
    /home/ua02/foo
    /tmp/foo



## 5. Special characters (need to know)

![special: need to know](http://blog.zeronana.info/katsuo/wp-content/uploads/2011/05/facebook_smileys.jpg)

Bash has many special characters such as "* & ; | { ! < [ #" (you see, all are special, don't think you know them).
A commonly used example:


    $ find . -iname '*.conf'

Notice the single quotes around `*.conf`. What would happen without it? Bash would interpret the `*.conf` as a glob expression and expand it to all files ending in `.conf` in the current directory (we don't want this to happen!). This could prevent looking for all `.conf` files in subdirectories. Remember: we should always quote anything that
might contain special characters.

It needs to be known that only single quotes can prevent every character from being interpreted; double quotes still allow bash to interpret some characters. On the other hand, when working with variables, double quotes come in handy to prevent word splitting (it's useful!), which is often used in scripting.

You see, when a filename contains whitespace, bash splits the name on that whitespace when you leave variables unquoted. Suppose you have a file named “spaced name.txt, you put it in a variable `filename= spaced name.txt`, and then you try to move it to “unspacedname.txt” by executing `mv $filename unspacedname.txt`. You’ll get the error “mv: target ’unspacedname.txt‘ is not a directory”. This is because mv gets executed like this: `mv spaced name.txt unspacedname.txt`. In other words, mv will try to move two files, “spaced name.txt” to “unspacedname.txt”,
and fail because moving multiple files to a single destination is only allowed when the destination is a directory.
Putting double quotes around "$filename" solves this issue.

So you see, quoting is a good habit to prevent your commands and scripts from doing unexpected things. Important message: you can’t quote variables using single quotes because the dollar sign loses its special meaning between single quotes, and if you ever need to use a literal single quote in some command, you can do so by putting it between double quotes.





## 6. Process Substitution: save you some time

![efficiency, all I care](http://1funny.com/wp-content/uploads/2009/07/efficient-truck-transport.jpg)

Think of showing differences of two commands quickly? One way is to redirect the output to a temporary file
for both of them, and 'diff' those files, like this:

    $ find /etc | sort > local_etc_files
    $ find /mnt/remote/etc | sort > remote_etc_files
    $ diff local_etc_files remote_etc_files
    $ rm local_etc_files remote_etc_files

This would tell you the differences between which files are in /etc on the local computer and a remote one. It takes
four lines.  However, it wastes time! Using process substitution, we can do this is just a single line. Amazing!

    $ diff<(find /etc | sort)<(find /mnt/remote/etc | sort)

What does `<(…)` do? It means “run the command inside it, connect the output to a temporary pipe file and give
that as an argument”. To understand this more thoroughly, try running this:

    $ echo <(echo test)

Instead of printing “test”, this will print something like “/dev/fd/63″. You see now that the `<(…)` is actually
replaced by a file. This file is a stream from which the output of the command inside `<(…)` can be read, like this:

    $ cat <(echo test)

Now this does print "test"! Bash redirects the output of `echo test` to /dev/fd/<something>, gives the path of that
file to `cat`, and `cat` reads the output of `echo` from that file. The shortened `diff` command above does the same (plus it's much shorter), only for two slightly more complicated commands. This technique can be applied in any place where a temporary file is needed, but it does have a limitation. The temporary file can only be read once before it
disappears.




## 7. Ctrl+U and Ctrl+Y: backup command

![backup always userful](http://www.yoyoshare.com/wp-content/uploads/images/culture/80.jpg)

Do you know that moment when you’re typing a long command

    $ cd 1/2/3/4/5/6/7....(# represents super long names "1 = safjslfjsaflfj")
and then suddenly realize you need to execute something else
first (Oh, what's the next path...). Everyone hates this! Fortunately, there's a way to fix it. Ensure the cursor is at the end of your current command shortcut: `Ctrl+E`, press `Ctrl+U` to get a clean line,

    $ ^E (copy the current command)
    $ ^U (clear the current command)
    $ ls (check the direc you want)
    $ ^Y (paste the older command)
    $ cd 1/2/3/4/5/6/7..... (Yeah, the command is back)
type the other command you need to execute first, execute it, then press `Ctrl+Y` and amazing! Your long command is back on the line. No mouse needed for copying, just quick hotkeys.
Great tricks!!





## 8. A simple calculator

![calculator important sometimes](http://www.mathfunny.com/images/mathpics-mathjoke-mathmeme-pic-joke-math-meme-haha-funny-humor-pun-lol-calculator.jpg)

Sometimes you need to do a calculation that is too much for your brain. When you’re working in a graphic environment,
you might just fire up kcalc or gcalctool, but tools like that may not always be available or easy to find. Fortunately,
you can do basic calculations within bash itself.
For example:

    $ echo $((3*37+12))
    123
    $ echo $((2**16-1)) # Two to the power of sixteen minus one;
    65535
    $ echo $((103/10)) # Outputs 10, as all these operations are integer arithmetic
    10
    $ echo $((103%10)) # Outputs 3, which is the remainder of 103 divided by 10
    3

`$((something))` also allows bitwise operations (what?!), it's actually a syntactic sugar over the `eval` command, and as such it interprets the `^` as a bitwise
operator. That’s why `**` means  “the power of”. The syntax also supports showing the decimal equivalent of a
hexadecimal or octal number.
Here’s an example:

    $ echo $((0xdeadbeef))
    3735928559
    $ echo $((0127))
    87

For more information, read the bash man page (always a good choice, you can do it on either terminal or online) using man bash and search using "/" for “arithmetic evaluation”. If you want to do floating point calculations,
you can use `bc`:

    $ echo ‘scale=12; 2.5*2.5′ | bc
    6.25
    $ echo ‘scale=12; sqrt(14)’ | bc
    3.741657386773

Note the setting of the scale variable. With `bc`, you can perform floating point operations with any precision you like.
The scale variable controls the amount of decimals behind the dot that are calculated. Using 12 here because "kcalc"
uses that amount by default, but you can increase or decrease it as you like. Find out more about what bc can do by
executing `$ man bc`(remember, always a good choice). It even supports more advanced mathematical functions, such as the arctangent or the natural
logarithm!

## 9. Converting

![Image of a priest](http://catholicmemes.com/wp-content/uploads/2012/11/14144_132533646896386_329999885_n.png)

Converting documents and pictures is a very simple task that can be done manually... Now imagine that you need to convert a whole directory with hundreds of pictures.
How would you do that?

Using the 'convert' command is the easiest way to accomplish that. This command is a member of the imagemagick suite of tools so you might have to install it running the command:

	$ sudo apt-get install imagemagick

As a first example let's convert one image named "lion" from .jgp to .png:

	$ convert lion.jpg lion.png

Now, if we put that command inside a loop with the right changes we can actually replace all files inside a directory from one format to another:

	$ for f in *.jpg; do
	 convert ./"$f" ./"${f%.jpg}.pdf"
	 done

It can be done because instead of a name we are setting a variable $f, with a special character \*, to replace it by whatever other sequence of characters ending with .jpg may appear in the directory. Once the variable assumes a file name we use that as the first parameter and then we only replace the extension file to our desired one as a second argument, which would be .pdf.

Another trick you should be aware of is the for loop. In the bash shell it won't run the command when you press enter; it will let you enter more things afterward and only run it when you type 'done', signaling the end of the loop.

Imagemagick has also a lot of others functionalities like resizing, flipping, changing quality or joining images that may help you to play a little bit with image-processing.




## 10. Replacing words

![Image about words](http://commbasics.typepad.com/.a/6a00d83458a0a553ef01b7c6d4e3f1970b-pi)

Pretend that you messed up an important document with a misspelled word and you just realized it was wrong 5 minutes before you actually needed to present it.

Relax, your problems are over now, you can fix it in one line using the 'sed' command!

Sed stands for Stream EDitor and can be very useful when passing the right flags to it. What distinguishes it from others editors is the way it works making only one pass over the input(s) and the ability to filter text through a pipeline. Sed has several commands, but people more commonly use is the substitute command: s.

If you type:

	$ sed 's/hello/goodbye/'

Shell will take your input from keyboard and output that changing the first occurrence of hello to goodbye.

To solve our previous problem about the wrong word in a file we should type:

	$ sed -i 's/wrong/right/g' file.txt

	or:

	$ cat < file.txt | sed 's/wrong/right/g' | cat > newfile.txt

The flag -i will save back to your original file and not output anything.
The g letter stands for global, what will make it replace all occurrences of the 'wrong' word.
file.txt is the name of your actual file, that you want to modify.

In the second example we are using I/O redirection. The 'cat' command will take the content of file.txt as input, send it to 'sed' replace the words and finally sending to another 'cat' which will create a new file with the desired changes.

You also can use regular expressions to match a defined pattern in 'sed' command, what can make your life even easier in a different task. In our next example you need to put all ucr e-mail addresses inside parenthesis. So we would do:

	$ sed 's/[a-z0-9]*@ucr.edu/(&)/' <file.txt >newfile.txt

Remember that you can use the same command with a similar syntax in vim what could help you to write code, change variable names etc.
In vim, type:

	:s/wrong/right/

Or to make it global and replace all the occurrences:

	:%s/wrong/right/g


