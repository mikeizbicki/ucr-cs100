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
We can also specify what is printed using the following format:
```
{print paramA, paramB, paramC}
```
So,
```
awk '{print "hello","world"}' class.txt
```
prints `hello world` for every line with a match.

Let's take things a bit further.
What if we wanted only to view classes, and omit student information?
Utilizing the pattern field, AWK can function similarly to grep:
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
AWK can handle a variety of boolean logic.

Operator | Definition
-------- | --------------------------------------------
||       | OR
&&       | AND
!        | NOT
==       | equal
!=       | not equal
>=       | greater or equal
<=       | less or equal

So the following check for a student's passing status:
```
awk '/Richelle Quade/ {print ($4 == "A" || $4 == "B" || $4 == "C") ? "pass" : "fail" }' class.txt
```
outputs this:
```
fail
```
OK great!  Now that we know how to write conditionals, we can move on.


###if/else statements###

This school's poor student performance is hurting its funding, and its time for a purge.
So how can we drop everyone who isn't up to snuff?
We get to use the if statement:
```
if (condition) {action} else {action}
```
Let's put it to practice:
```
awk '{if ($4=="A" || $4=="B" || $1=="Class"){ print } else {print "\tDROPPED"} }' class.txt
```
And viola!
```
Class #1 taught by Berta Quinney
        DROPPED
        Marget Creighton                     Grade: A
        Meggan Rugg                          Grade: A
        DROPPED
        Lara Dietz                           Grade: B
        Sandy Lundberg                       Grade: B

...
```
Picture perfect classrooms! Alternatively, we can use AWK loops to pad its classes a little...

###For loops###
Let's write a command so that everyone with an A gets entered three times:
```
awk '{if ($4=="A") { for (i=0;i<3;i++) print }else{print } }' class.txt
```
Here's our output:
```
Class #1 taught by Berta Quinney
        Shery Principe                       Grade: C
        Marget Creighton                     Grade: A
        Marget Creighton                     Grade: A
        Marget Creighton                     Grade: A
        Meggan Rugg                          Grade: A
        Meggan Rugg                          Grade: A
        Meggan Rugg                          Grade: A
        Minna Harmon                         Grade: F
        Lara Dietz                           Grade: B
        Sandy Lundberg                       Grade: B
...
```
And now our student averages are top notch!

##Extended AWK##
In order to write AWK scripts on multiple lines, use the following format:

```
awk 'BEGIN { action; }
/pattern/ { action; }
END { action; }' [filepath]
```
where the `BEGIN` action will initiate first, and the `END` action will initiate last.
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

Things to add:
More advanced usages of awk
Example files - tables, lists
Conclusion


#References:
[Grymoire Tutorial](http://www.grymoire.com/Unix/Awk.html#uh-7)

[GNU AWK Manual](https://www.gnu.org/software/gawk/manual/html_node/)
