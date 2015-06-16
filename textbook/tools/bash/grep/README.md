#Grep

`grep` is a bash command that searches any inputted file(s) for lines that match a given pattern.
By default, it prints the matching lines to standard output.
You can also use it with any of its options and/or other bash commands to display additional information, but we will be going into more detail about this later.

In general, `grep` is pretty easy to use!
Just follow this format:

```
$ grep ‘pattern’ filename
```

###Searching through a file

Let’s say you want to search through your code to find the lines where you used `cout`.
  
This is where the `grep` bash command comes in.
By using the `grep` command, you could have every matching line printed to standard out.
Only the lines of code you are focusing on will be filtered out and put in one place for you to analyze.

To search through ex1.cpp, you would use the `grep` command as follows:

```
$ grep ‘cout’ examples/ex1.cpp
```

This would output the following to standard output:

```
		cout << “Hello, I am a child!” << endl;
		cout << “Hello, I am a parent!” << endl;
	cout << endl;
```

This might not seem like much of an upgrade from using the `find` command within your code, but imagine searching for a pattern that is matched over twenty times.
Even with a `find` command, that is a lot of code to manually look through. 
`grep` makes it a bit easier by isolating the important text from everything else.

###Searching through multiple files

The `grep` command is not limited to only one file.
You could search through multiple files and even directories using the same format we have been using.
Let’s say you want to search for the instances where you used `cout` in both `ex1.cpp` and `ex2.cpp`.

If you pass multiple files as command line parameters, `grep` will search through all of them.
For example:

``` 
$ grep ‘cout’ examples/ex1.cpp examples/ex2.cpp
```

You can also recursively search through a directory by including the `-r` option as follows:

```
$ grep -r ‘cout’ examples
```

Both of these commands have the same output:

```
examples/ex1.cpp:		 cout << "Hello, I am a child!" << endl;
examples/ex1.cpp:		cout << "Hello, I am a parent!" << endl;
examples/ex1.cpp:	cout << endl;
examples/ex2.cpp:	cout << "goodbye world" << endl;
``` 

###Searching through other texts

Now that you know how to use `grep` to search through files, you can practice using it to search through other forms of text.
Note that if no files are specified or the file name `-` is given, `grep` waits for and searches standard input.
This is a quick and easy way to practice using the `grep` command. 

One special use of the `grep` command is with `git log`, which shows your commit logs.
Let’s say you are able to fix a crucial bug in your code one day.
You commit, celebrate, and continue coding.
After spending days on this project, you realize that your code has gone completely wrong, and you want to go back to an old commit.
Perhaps you want to go back to that ‘bug-fixed’ commit.
How are you going to search through over hundreds of commits?

It turns out that `git log` has a `grep` option!
You could use this command to help you search for the right one:

```
$ git log --grep “bug fixed”
```

If you are smart enough with your commit messages and search pattern, you will be able to narrow down your search significantly.
The command will output something like this, depending on your commit log:

```
commit 2ef16dec1d0fc79cc0c01ec02a5c1c17b1e91963
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Tue May 05 15:49:31 2015 -0700

    long user-inputs bug fixed

commit 91b19e03715aa6bbf876a2d3b836de65bbea7daa
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Wed Apr 01 00:18:44 2015 -0700

    infinite loop bug fixed

commit 1e6715e5577ffb11299da2d919a98e097ac3f299
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Tue Mar 31 01:06:24 2015 -0700

    code works but doesn’t end, still needs infinite loop bug fixed
```

This should help you find the right commit a lot faster!

You could also use `grep` with most other bash commands.
Let’s say you want to search through your history and find all previous uses of `g++`.
You could [pipe](https://github.com/mikeizbicki/ucr-cs100/blob/34313e7bcb17e572b7a30adc6b8b600dc4ce265f/videos/syscalls-detailed.md) the history command to your `grep` search as follows

```
$ history | grep ‘g++’
```

The command will output something like this, depending on your history:

```
169     g++ main.cpp
172     echo g++
173     g++ main.cpp 2> errors
175     g++ -Wall -Werror -ansi -pedantic main.cpp
177     cp main.cpp main2.cpp; g++ main2.cpp
183     g++ -Wall -Werror -ansi -pedantic main2.cpp
184     echo g++ main.cpp
190     history | grep 'g++'
```

###Using regular expressions

Another neat way to expand your uses of the `grep` command is with the use of [regex] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex), short for regular expressions.
Regular expressions are special combinations of letters and symbols that represent a search pattern.

In the previous example, we searched through your history for any uses of `g++`.
That search, however, also included lines where `g++` was used as an argument.
Luckily, we can use regular expressions to match only lines that begin with a line number and the `g++` command:

```
$ history | grep ‘^ *[0-9]* *g++’
```

The command will output something like this, depending on your history:

```
169     g++ main.cpp
173     g++ main.cpp 2> errors
175     g++ -Wall -Werror -ansi -pedantic main.cpp
183     g++ -Wall -Werror -ansi -pedantic main2.cpp
```

This should be a bit closer to what we had in mind, but there is still a flaw in this logic.
See if you can find it and solve it.

###Including options

Earlier, we briefly mentioned the `-r` flag that allows `grep` to recursively search through directories.
`grep` has many other options to choose from as well. 
To include these flags in your command, just follow this format:

```
$ grep [options] ‘pattern’ filename
```

A good example would be the `-c` flag. 
We have been talking about using the `grep` command to output matching lines.
What if you only cared about how many times a matching line was found?

Easy. 
Just include the `-c` flag as follows:

```
$ grep –c ‘cout’ examples/ex1.cpp
```

This command line will search through ex1.cpp and count how many lines contain the pattern `cout`.
You should get this:

```
3
```
You could also use multiple options at once.
Let’s say you want to recursively search through a directory and count how many lines contain a match to your pattern.
You could use both the `-c` and `-r` flags together.
You can add flags to a command in two different ways as follows:

```
$ grep –cr ‘cout’ examples
```
or 
```
$ grep –c –r ‘cout’ examples
```

Both of these command lines will search through the same files and output this:

```
examples/ex1.cpp:3
examples/ex2.cpp:1
```

Again, these are only two of `grep`’s many options.
For an official description of `grep` and all of its features, visit the [grep](http://linux.die.net/man/1/grep) man page.

Happy searching! :]
