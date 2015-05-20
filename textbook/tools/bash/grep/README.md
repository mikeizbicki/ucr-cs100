##Grep

####What is grep?

Grep is a useful search tool. It searches input files for lines that contain a match to whatever patter you specify. When it finds a match in a line, it outputs a copy of that line to standard output or produces whatever other output you have requested using its built-in flags. If it is not able to find any matches, it outputs nothing.

#####How do I use grep?

	It’s pretty easy, really! Grep uses the following format:

```
grep optional_flags pattern input_file_names
```
	
	As mentioned, grep’s flags are optional. You can include anything between zero and all of the flags if you want to.
	Grep can search through one or more input files, separated by spaces. The input file names are technically optional as well. If no input file names are included, grep uses standard input as the input. This is pretty useless for programming and such, but it is an easy way to see how the grep command works.

Let’s look at some examples, shall we?

	```
	$ grep hello file1
	$ grep “hello” file1
	$ grep “hello world” file1
	$ grep “hello world”
	```

It is important to remember that grep separates a command by spaces. If you want to search for a single word, the quotes are optional. Lines 1 and 2 will output the same thing. If you want to search for a pattern that has more than one word, you must include quotes around it, as shown in line 3.

#####Now what happens if I don’t include a file name?

Let’s look at some examples.

	```
	$ grep “hello world”
	> hi
	> hello there
	> hello world
	hello world
	> Hello world my name is Jennifer
	> hello world my name is Jennifer
	hello world my name is Jennifer
	```

If you use the grep command without including an input file, it will wait and check for the pattern in standard input. In the example above, the arrow indicates the user input and everything else is standard output. On line 4, you can see that grep simply echoes the user input if it has a match to the pattern being searched for. It is important to note that grep is case-sensitive. This is why line 6 is not echoed.

#####What are some commonly used flags?

#####What are some features of grep? (flags, using ‘.’, etc. will be mentioned here)

#####When would I use grep?
