#Grep

In this tutorial, we will be talking about what the grep command is, how to use it, some examples of when you would want to use it, and different ways you can use it (common options and operators).

###What is grep?

Grep is a useful search command. 
It searches any inputted file(s) for lines that contain a match to a given pattern.

If no files are specified or the file name `-` is given, it searches standard input.
By default, grep prints the matching lines to standard output.
You can, however, use any of its many options to display additional information.
We will be talking about some of grep’s commonly used flags in more detail later.

###How to use grep

It’s pretty easy, really! Grep uses the following format:

```
$ grep ‘pattern’ filename
```

###Searching through a file

Let’s say you want to search through your code and examine the instances where you used `cout`.
You could simply use a `find` command (such as `/` in vim), but this method takes a bit more effort on your part.
It’s easy to accidentally overlook something when you are manually searching through every instance of the word `cout`.
  
This is where the grep bash command comes in.
By using the grep command, you could have every matching line printed to standard out.
Only the lines of code you are focusing on will be filtered out and put in one place for you to analyze.

To search through ex1.cpp, you would use the grep command as follows:

```
$ grep ‘cout’ examples/ex1.cpp
```

This would output the following to standard output:

```
		cout << “Hello, I am a child!” << endl;
		cout << “Hello, I am a parent!” << endl;
	cout << endl;
```

This might not seem like much of an upgrade from using the ‘find’ command within your code, but imagine searching for a pattern that is matched over twenty times.
Even with a `find` command, that is a lot of code to manually look through. 
Grep makes it a bit easier by isolating the important text from everything else.

###Searching through multiple files

The grep command is not limited to only one file.
You could search through multiple files and even directories using the same format we have been using.
Let’s say you want to search for the instances where you used “cout” in both ex1.cpp and ex2.cpp.

You would type in the following command to search through multiple files:

``` 
$ grep ‘cout’ examples/ex1.cpp examples/ex2.cpp
```

You could also save yourself some trouble by recursively searching through the directory instead of typing out each individual file.
We will be talking about grep options in a bit more detail later, but here is just an introduction to one of the many options.
You can recursively search through a directory by including the ‘-r’ option as follows:

```
$ grep -r ‘cout’ examples
```

Both of the above mentioned command lines will search through the same files and print this:

```
examples/ex1.cpp:		 cout << "Hello, I am a child!" << endl;
examples/ex1.cpp:		cout << "Hello, I am a parent!" << endl;
examples/ex1.cpp:	cout << endl;
examples/ex2.cpp:	cout << "goodbye world" << endl;
``` 

###Searching through other texts

Now that you know how to use grep to search through files, you can also use it to search through any other form of text. 
Let’s say you want to search through your history and find all the previous uses of `g++`.


If you don’t already know how the pipe command works, you can read about it HERE.
You could pipe the history command over to your grep search as follows:

```
$ history | grep ‘g++’
```

Your output could look different depending on your history, but the above command line could display something like this:

```
169     g++ main.cpp
172     echo g++
175     g++ -Wall -Werror -ansi -pedantic main.cpp
177     g++ main2.cpp
183     g++ -Wall -Werror -ansi -pedantic main2.cpp
184     history | grep 'g++'
```

###Including options

We have already briefly mentioned the ‘-r’ flag that allows ‘grep’ to recursively search through directories.
Grep has many other options to choose from as well. 
To include options in your command, just follow this format:

```
$ grep [options] ‘pattern’ filename
```

A good example would be the ‘-c’ flag. 
We have been talking about using the grep command to output matching lines.
What if you only cared about how many times a matching line was found?

Easy. 
Just include the `-c` flag as follows:

```
$ grep –c ‘cout’ examples/ex1.cpp
```

This command line will search through ex1.cpp and count how many lines contain the pattern ‘cout’.
You should get this:

```
3
```
You could also use multiple options at once.
Let’s say you want to recursively search through a directory and count how many lines contain a match to your pattern.
You could use both the ‘-c’ and ‘-r’ flags together.
You can add flags to a command in two different ways as follows:

```
$ grep –cr ‘cout’ examples
```
Or
```
$ grep –c –r ‘cout’ examples
```

Both of these command lines will search through the example directory and count the number of matching lines. You will get this:

```
examples/ex1.cpp:3
examples/ex2.cpp:1
```

These are only two of grep’s many options.
You can browse through a complete list of these by visiting the [grep](http://linux.die.net/man/1/grep) man page.

###Using regular expressions

Another neat way to expand your uses of the grep command is with the use of regular expressions (often abbreviated as regex).
Regular expressions are special patterns of letters and symbols that represent a search pattern.

Let’s say you want to search for blank lines in your code. 
Maybe you just want to know how many lines of your code are not being used.
How do you search for a blank line using grep?

The caret symbol `^` is a regular expression that matches at the beginning of a string or line, and the dollar sign `$` is a regular expression that matches at the end.
Putting these two regular expressions together, we have a pattern that represents a blank line.
 
Let’s search for blank lines in our examples/ex1.cpp file:

```
$ grep ‘^$’ examples/ex1.cpp
```

Using this command line, you should get this:

```




```

But wait a minute, that’s a bit silly to be printing blank lines.
That doesn’t mean anything to us.
What we want to know is exactly how many of these lines we have in our code.

We can update our search command to this:

```
$ grep –c ‘^$’ examples/ex1.cpp
```

This command line will output this:

```
4
```

Whoa. 
Grep flags AND regular expressions?
That’s right.
You can use any combination of grep’s options and regular expressions to narrow down your search to exactly what you are looking for.
Think of the endless possibilities!

Visit this [regex](https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) tutorial for a more detailed explanation of how to use regular expressions to accommodate your grep searches.

Happy searching! :]
