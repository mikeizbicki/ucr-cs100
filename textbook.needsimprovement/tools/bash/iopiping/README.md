#Piping and IO Redirection Examples
A non-comprehensive explanation of piping and input/output redirection and some useful examples with explanations.

##Input/Output Examples
Input and output operators establish communication **between a program and a file** by changing what the 3 default files read from or write to.
* `stdin` is by default the keyboard. File descriptor `0`
* `stdout` is by default the screen. File descriptor `1`
*  `stderror` is by default error messages output to screen. File descriptor `2`

When other files are opened, they are assigned other file descriptors. Those file descirptors are assigned to `stdin`, `stdout`, or `stderror` when the shell interprets IO and pipe operators.

```
$ program < file
```
Where `<` can be replaced with different IO operators (see [here] (http://www.tldp.org/LDP/abs/html/io-redirection.html)).

####Input Redirection
`<` tells the shell to read input from a file instead of `stdin`.

```
$ sort < inputfile
```
With this input redirection, `sort` will read from `inputfile`, sort the file's contents accordingly, and output to the screen.
We can specify flags for `sort` (see [`man sort`](http://ss64.com/bash/sort.html)) to change how things are sorted.

###Output Redirection
`>` tells the shell to output to a file instead of `stdout`.
* If `outputfile` doesn't exist, it is created and then written to.
* If `outputfile` does exist, its contents are overwritten.

`>>` appends to a file.
* If the file doesn't exist, it is created and written to the end of the file.
* If the file does exist, it is just written to the end of the file.

```
$ ls > outputfile
```
This command will print nothing to the screen, but instead `outputfile` will be erased and contain the name of every file in the current directory on a new line.

&nbsp;

```
$ ls >> outputfile
```
This command will print nothing to the screen, but instead `outputfile` will contain the name of every file in the current directory on a new line, but appended to the end of the file.

&nbsp;

###Input and Output Redirection

```
$ sort < inputfile > outputfile
```
`sort` will read from `inputfile` and sort each line.
This command prints nothing to the screen.
The `outputfile` will be erased and the output of `sort` will be printed into it.

&nbsp;

```
$ sed 's/word1/word2/g' < file1 > file2
```
This places the contents of `file1` in `file2` with all instances of `word1` replaced with `word2`.
`file1` does not change.
`sed` is a particularly interesting and important command for searching and replacing.
It has many features which you can read about [here] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/sed).  

##Piping
Piping establishes communication between two **programs**.

In `left | right`, the output of `left` acts as the input to `right`.
The pipe `|` connects `stdout` of `left` to `stdin` of `right`.

For example:
```
$ ls | grep cpp
```
This command takes the ouput of `ls` and feeds it (technically pipes it) to `grep cpp`.
`ls` lists all the files in the current directory and of those files, grep will print to `stdout` the ones that contain `cpp`.

Piping is often used in conjunction with `grep` (see [here] (http://ss64.com/bash/grep.html)) or `sed` for finding phrases in files.
We can also use [regular expressions] (https://github.com/phung001/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) for specific searching.

##Piping and IO Redirection
Pipe and input/output operators can be used together.

```
$ sort inputfile | grep 'cs100' >> outputfile
```
All the lines in `inputfile` containing `cs100` are appended to `outputfile` in sorted order.

With shell commands, there is never just one way to do things.
There isn't really a best way either.
The best way is a subjective balance of shortness and readability.
This next command does the same thing as the previous command.
```
$ cat inputfile | grep 'cs100' | sort >> outputfile
```
It first prints `inputfile` to `stdout`, searches for `cs100`, and then sorts those lines into `outputfile`.
The previous command sorted `inputfile` first, then selected lines containing `cs100` into `outputfile`.


##Useful/Interesting Commands
The following commands perform practical, complex tasks made possible by piping and IO redirection.

```
$ ls -lR | grep .cpp | vim -
```
This command looks recursively through the current directory and displays only the lines that contain `cpp` in vim (instead of the screen).
The `-` is a parameter specific to `vim` that tells `vim` the file to edit should be read from `stdin`.
The `grep .cpp` portion of the code may be modified for any string in file names. 

&nbsp;

```
$ users | sed s/' '/'\n'/g | uniq 
```
This command prints all the currently logged on users on different lines.
`users` prints all the logged on users seperated by space.
`sed` will search and replace each space with a newline.
`uniq` will remove any duplicates and output each user only once.

&nbsp;

```
$ tr -cs "A-Za-z0-9" "\n" < inputfile | sort | uniq -c | sort -n -r
```
This command prints how many times each word in inputfile is used.
The translate command, `tr`, is very useful (see [`man tr`] (http://ss64.com/bash/tr.html)).
The pattern "A-Za-z0-9" finds every word by making `tr` only grab things in the ranges of capital letters, lowercase letters, and numbers.
Then we insert a `newline` after each of those words.
Since `uniq` only removes duplicates that are next to each other, we must presort the words with `sort`.
`uniq` normally outputs each word only once, but with the `-c` flag, it also prints the number of times the word occurs.
Finally for the second `sort`, `-n` sorts numerically and `-r` reverses the order to go least to greatest.

&nbsp;

```
$ history | awk '{print $2}' | sort | uniq -c | sort -nr | head
```
This command lists your top 10 commands from history and how many times each command has been used.
`awk '{print $2}'` reads from history and only outputs the second word of each line.
Lastly, the `head` command prints only the first 10 lines.

&nbsp;

```
$ ps | grep '.out' | awk '(print $1)' | xargs kill
```

This command kills all processes whose name contains ".out".
We use `awk` to get the process ID's as ps lists the process ID's in the first column.
`xargs` takes in a stream of files or process ID's from `stdin` and applies a bash command to all of them.
In this case, we are applying `kill` to all of them.
For example, if we want to delete all the cpp files in the current directory, instead of  
`rm file1.cpp file2.cpp file3.cpp file4.cpp ...`  
We can use  
`ls | grep 'cpp' | xargs rm`  
Which is much easier than typing everything out.

&nbsp;

```
$ wget --quiet -O - http://google.com/ | grep -oP 'http://[^"]*' | uniq | sort > outfile.txt
```
This command gets all the links from a webpage and prints it to `outfile.txt`. 
`grep` does most of the work with its powerful regular expression ability (read about regex [here] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex)), but its input is from the wget command. 


##Conclusion
Programs become extremely useful when they can communicate with each other.
By themselves, they are already powerful, but by following the Unix philosophy of keeping things very small and flexible, piping and I/O redirection give us a way to combine programs to perform otherwise complex tasks.
This can prove to be a very powerful tool to have and is one reason that makes Unix so popular.


