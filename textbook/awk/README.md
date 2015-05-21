#AWK Tutorial#
============

#What is AWK?#
-----------
AWK is text-based programming language and a very powerful and simple text-processing utlity on GNU/Linux.
It focuses on the interpretation of streams, which makes it ideal for such tasks as filestream manipulation or piping.
In particular, AWK can be used to sort through large tables of data, produce formatted reports, and a variety of other things.

#Using AWK#
-------------
##Searching for a Specific String##
To print the lines containing a certain string, type:

```
	awk '/string/ { print $0 } ' fileName
```
string is the text you wish to search for and fileName is the file you are searching through.

###Example###
Let's say we are presented with the problem of searching a text file called 'inventoryList' for the string 'apple'.
In order to find all lines containing the string apple, we type:

```
	awk '/apple/ { print $0 } ' inventoryList
```
The print $0 in the code above means print the line that is currently being scanned if apple is found.

##Searching by Line Length##
To print every line with a length greater than x characters:
```
	awk 'length($0) > x' fileName
```

##Conditional Statements##
AWK supports conditional statements similar to most other programming languages.
You are allowed to declare your own variables, use for loops, if statements, and so on.

###Examples###

for loop
```
for (i=1;i<=10;i++) {
	
}
```

if statements
```
if (myVar < 0) {
	
}
```


Things to add:
More advanced usages of awk
Example files - tables, lists
Conclusion


#References:
[Grymoire Tutorial](http://www.grymoire.com/Unix/Awk.html#uh-7)
[GNU AWK Manual](https://www.gnu.org/software/gawk/manual/html_node/)
