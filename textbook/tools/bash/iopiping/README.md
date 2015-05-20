#Piping and IO Redirection Examples
Whats up homie dogs? One line commands using the principles of piping and input/output redirection with explanations of their significance.

##What You Should Already Know
link to io redirection tutorial here
link to piping tutorial here
link to grep tutorial here

##Let;s Begin!
Fun and engaging sentence or rhetorical question here

Input/Output redirection and piping, as you should already know, make life infinitely easier by changing the flow of information between programs. They accomplish this by changing file descriptors.

##Input/Output Examples
Input and Output operators establish communication between a program and a file.
Remember that the input and output operators can only be used on files! See linkhere for more information on input/output operators.
```
cat < inputfile
```
This command simply prints the contents of inputfile to the screen.


```
ls > outputfile
```
This command will print nothig to the screen, but outputfile will contain the name of every file in the current directory on a new line.


```
cat < inputfile > outputfile
```
This command prints nothing to the screen. The contents of inputfile are now also in outputfile.



##Piping
Piping establishes communication between two programs.

In ```left | right```, the output of left acts as the input to right.

For example
```
ls | grep cpp
```
This command takes the ouput of `ls` and feeds it to `grep cpp`. `ls` will list all the files in the current directory and of thsoe files, grep will only display the ones that contain "cpp".

```
output goes here
```
Piping is often used in conjunction with `grep` or `sed` for finding phrases in files. Sentence about regular expressions and link to tutorail.

##Piping and IO Redirection
This is nothing to be scared of. Some sentence here explaining it is simple. IO involves program and file and that program can be used as one side of a pipe commad.

```
cat < inputfile | ls -l > outputfile
```
Probably better to just show output than explain with a giant paragraph. At the end of this command, outputfile looks like this:
```
outputfile contents here
```

##Interesting Stuff
```
sed 's/word1/word2/g' < file1 > file2
```
Places contents of `file1` in `file2` with all instances of `word1` replaced with `word2`. `file1` does not change. Talk about importance of sed command + link to sed tutorial.

```
ls -lR | grep .cpp | vim -
```
This command looks recursively through the current directory and finds any .cpp files. The files and their information will then be presented on vim rather than stdout. The `grep .cpp` portion of the code may be modified for any string in file names. 

```
ps | grep problemprocess | grep -v grep | awk '(print $2)' | xargs kill
```
http://unix.stackexchange.com/questions/30759

This command kills a process based on its name by obtaining its process id. Explanation of each pipe follows.

```
wget -O -http://izbicki.me/ | grep -E -o "\b[a-z A-Z 0-9.-] + @[a-z A-Z 0-9.-] + \.[a-z A-Z 0-9.-] + \b"
```
Link to quiz maybe? Or change it up a bit. Gets email addresses from a webpage. `grep` does most of the work with its powerful regular expression ability, but its input is from the wget command.

##Conclusion
Programs become extremely useful when they can communicate with each other. By themselves, they are already powerful, but piping and i/o redirection give us a way to combine programs to perform otherwise complex tasks.
