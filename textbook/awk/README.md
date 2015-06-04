#AWK Tutorial#
============

#What is AWK?#
-----------
AWK is text-based programming language and a very powerful and simple text-processing utlity on GNU/Linux.
It focuses on the interpretation of streams, which makes it ideal for such tasks as filestream manipulation or piping.
In particular, AWK can be used to sort through large tables of data, produce formatted reports, and a variety of other things.

#Using AWK#
-------------

In this tutorial we will be using an text file "class.txt", which contains teh records of a hypothetical elementary school class.
Try it yourself! Clone this repo and launch `make`.

##Basic AWK Commands##
Simple single line commands can be made in the following format:
```
awk '/pattern/ {action}' [filepath]
```
Let's try printing our class.txt file:
```
awk '{print}' class.txt
```
We get
```
Class #1 taught by Berta Quinney
        Shery Principe                       Grade: C
        Marget Creighton                     Grade: A
        Meggan Rugg                          Grade: A
        
...

Class #19 taught by Lynelle Katzman
        Carina Balzer                        Grade: F
        Malcolm Mayhew                       Grade: A
        Shavon Lafever                       Grade: A
        Ralph Higgs                          Grade: C
        Myron Lorusso                        Grade: F
        Maranda Litten                       Grade: D
```
As we did not specify a pattern, the above command will simply print the entire file.
Obviously this is not very useful (we could have used `cat` for that).

Let's take things a bit further.
What if we wanted only to view classes, and omit student information?
AWK can function similarly to grep:
```
awk '/Class/' class.txt
```
And the output...
```
Class #1 taught by Berta Quinney
Class #2 taught by Verena Griffie
Class #3 taught by Trey Yearby
Class #4 taught by Arianna Unrein
Class #5 taught by Arianne Siegrist

...
```
Or if we wanted only student info,
```
awk '!/Class/' class.txt
```
The '!' in front of the pattern negates, so that AWK will only search lines without "Class".
```
...
	Richelle Quade                       Grade: F
        Edgardo Persinger                    Grade: B
        Kari Dougan                          Grade: F
        Tawna Braun                          Grade: D
        Danial Billman                       Grade: B
        Rima Fester                          Grade: F
        Sherryl Paschall                     Grade: A
...
```
But wait!  Those grades are strictly confidential!  We can't have them appearing there.
There's an AWK for that:
```
awk '!/Class/ {print $1,$2}' class.txt
```
The `$num` notation denotes columns on a line.  So in the previous output's first line, `$1,$2` refer to `Richell Quade`, whereas `$4` refers to `F`.  Therefore our output becomes
```
...
Richelle Quade
Edgardo Persinger
Kari Dougan
Tawna Braun
Danial Billman
Rima Fester  
Sherryl Paschall   
...
```
As a side note, you can use `$0` to refer to all columns, or the entire line.

##AWK Logic##
```
awk '/Richelle Quade/ {print ($4 == "A" || $4 == "B" || $4 == "C") ? "pass" : "fail" }' class.txt
```
Output
```
fail
```

##Extended AWK##




















#Rough Draft Below#
-------------------

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

##Arithmetic##
AWK utilizes a variety of unary/binary operators, which function quite similarly to those found in the C programming language.
Note that order of operations is considered, just as it would in C.

###Unary Operators###
Positive/negative

One example which DOES actually work in AWK:
``
var = 4;
print = -var;
``

###Assignment Operators###
``
[variable] = [expression]
``
For example:
``
myVar = 5 * x + 4;
``

####Shortcuts####
++ and --

+=, -+, etc.

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
