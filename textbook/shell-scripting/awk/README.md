
#What is AWK?#
AWK is a programming language that is a very powerful and simple text-processing utlity on Unix.
It focuses on parsing input from a file stream into an output form specified by the user.
For example, AWK can be used to sort through large tables of data, produce formatted reports, and overall is very valuable for data parsing.

#Using AWK#

In this tutorial we will be using an text file `class.txt`, which contains the records of a hypothetical elementary school class.

You can write simple single line commands in the following format:
```
awk '/pattern/ {action}' [filepath]
```
*NOTE: If you do not include a filepath, AWK reads from stdin until you quit via ^C.*

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
We can also specify what is printed using the following format:
```
{print paramA, paramB, paramC}
```
So,
```
awk '{print "hello","world"}' class.txt
```
prints `"hello world\n"` for every line with a match.

You can also use `;` to denote the end of an action. 
This is useful for stringing together multiple actions like so:
```
awk '/pattern/ {action; action}' [filepath]
```
Here's an example:
```
awk '{print; print "-------------"}' class.txt
```
This prints each line, but also adds `"-------------"` after every line:
```
Class #1 taught by Berta Quinney
-------------
        Shery Principe                       Grade: C
-------------
        Marget Creighton                     Grade: A
-------------
        Meggan Rugg                          Grade: A
-------------
        Minna Harmon                         Grade: F
-------------
...
```

Let's take things a bit further.
What if we wanted only to view classes, and omit student information?
Using the pattern field, AWK can function like grep:
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
The `!` in front of the pattern negates, so that AWK will only search lines without `"Class"`.
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
The `$num` notation denotes columns on a line.  By default, columns are divided by whitespace.  So in the previous output's first line, `$1,$2` refer to `Richell Quade`, whereas `$4` refers to `F`.  Therefore our output becomes
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

##Formulas and Expressions##
Within the `{ action }` field you can define a variety of instructions using arithmetic and conditional expressions.

Variable assignment is easy in AWK. You do not need to explicitly declare a variable.  Simply define the variable and AWK will automatically declare it.  For instance, instead of `int i = 1`, simply write `i = 1`.

Arithmetic expressions can be performed very similarly to your programming language of choice.

Operator | Definition
-------- | --------------------------------------------
+        | add
-        | subtract
*        | multiply
/        | divide
%        | modulo

You can also do this: `x+=2` or `x%=2`, which is equivalent to `x=x+2` or `x=x%2`.

AWK can also handle boolean logic.

Operator | Definition
-------- | --------------------------------------------
\|\|     | OR
&&       | AND
!        | NOT
==       | equal
!=       | not equal
>=       | greater or equal
<=       | less or equal

For instance, a conditional like this:
```
($4 == "A" || $4 == "B" || $4 == "C")
```
is true if and only if the fourth column on the line is "A", "B", or "C".

OK great!  Now that we know how to write expressions, we can move on.


###if/else statements###

Let's say we want to check on a particular student's passing status in his/her class.
In this case there are two conditions.
A student is either passing or failing, so we get to use the if statement:
```
if (condition) {action} else {action}

```
Let's put it to practice:
```
awk '/Richelle Quade/ {if ($4 == "A" || $4 == "B" || $4 == "C") {print "pass"} else {print "fail"}}' class.txt
```
Look at the above command.  `/Richelle Quade/` tells awk to only scan lines containing `"Richelle Quade"`.
Then, within the `{}` braces, we have an if/else statement that either prints `"pass"` or `"fail"`.
And viola! Here is our output:
```
fail
```
Now let's look at loops...

###For loops###
Our current class list, though indented, is still rather hard to read.
We can solve this problem by adding large breaks between classes.
We can do this using a for loop:
```
awk '{if ($1=="Class") { for (i=0;i<3;i++) print " "; print} else { print } }' class.txt
```
As you can see, this command checks if the first column matches `"Class"`.
If it does match, then the statement `"for (i=0;i<3;i++) print " "` will cause `" \n"` to be printed three times.
So, our output looks something like this:
```
Class #17 taught by Tilda Gardner
        Richelle Quade                       Grade: F
        Edgardo Persinger                    Grade: B
        Kari Dougan                          Grade: F
        Tawna Braun                          Grade: D
        Danial Billman                       Grade: B
        Rima Fester                          Grade: F



Class #18 taught by Janett Galang
        Sherryl Paschall                     Grade: A
        Jeffery Waldeck                      Grade: A
        Fermin Fitzwater                     Grade: B
        Sade Mose                            Grade: B

...
```

##Extended AWK##
In order to write AWK scripts on multiple lines, simply leave out the closing quote on the action.
Bash will then initiate a multi-line editor.
This will be useful from here on, since the following examples are particularly long.

A useful feature of AWK is the ability to specify a `BEGIN` and/or `END` action.
To do this, use the following format:
```
awk 'BEGIN { action; }
/pattern/ { action; }
END { action; }' [filepath]
```
`BEGIN` and `END` match the beginning and end of the file, respectively, meaning that their actions will occur before and after the main output.
For instance, say we want to label the columns above the class list:
```
awk 'BEGIN {print "\tNAME\t\t\t\t\tGRADE\n";}
{print;}
END { print "\nEnd of class list" }' class.txt
```
So,
```
        Name                                    Grade

Class #1 taught by Berta Quinney
        Shery Principe                       Grade: C
        Marget Creighton                     Grade: A
        Meggan Rugg                          Grade: A
...
        Myron Lorusso                        Grade: F
        Maranda Litten                       Grade: D

End of class list
```
is our output

##Conclusion##
As a parsing tool, AWK is extremely powerful, especially when compared to simpler tools such as grep and cat.
In many cases, you do not even need to pipe output from AWK (although you can), since it is generally self-sufficient.
This means that scripts written in AWK are generally more streamlined and legible than otherwise.
However if you find you would need to write more than a hundred lines of AWK to do a job, perhaps it would be better to use a different programming language.
