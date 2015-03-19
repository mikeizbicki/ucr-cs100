#Tutorial: Simple Syntaxes For Bash Script

##All begin with a simple example

Let us begin with a "hello world" shell script example to expound how to write a script:

```
#!/bin/bash
#our first script
echo 'Hello world!!!'
```

There are three lines of code in the above script:

* The last line is an echo command to show `Hello world!!!`. It also works on the command line in the terminal:

```
$ echo 'Hello world!!!'
Hello world!!!
```

* The second line is a comment, because it begins with `#`. Everything after `#` in the current command line will be ignored:

```
$ echo 'Hello world!!!' #Our first script!!!
Hello world!!!
```

* We can see that every shell script includes the first line. It looks like a comment since it starts with `#`. However, it is created on purpose because it tells the system which interpreter (such as bash, ruby, python, and others) should be used to execute the followed script. For this script, it runs in the bash shell. And `#!` is a special character construct called shebang.

A shell script is a file containing a sequence of commands for a UNIX-based operating system. We also can consider each line of code of the script as a line of command in the terminal.

The following tutorial has two parts: 

##Part 1: How to make your script become executable

To successfully run our shell script, we need to make our script become executable. For the above "hello world" example, I save it as `hello.sh`. For a shell script file, try to use the file extension as `.sh`. So it can be easily identified by us as shell script.

There are two ways to execute a shell script:

```
$ bash hello.sh
$ ./hello.sh
```

Here, I use the second way to run my script. However, the system is very picky about not treating any text files as a program. Then each time we create a shell script we may meet a problem about permission: 

```
$ ./hello.sh
bash: ./hello.sh: Permission denied
```

Here, if we want to check the permission of the file, we can use `ls -l` command to check the details of the file:

```
$ ls -l hello.sh
-rw------- 1 user group 35 Dec  4 04:40 hello.sh
```

We can see that we only have `rw`, which means a reading and writing permission for the user. How do we add executing permission for the user? Luckily, we have the `chmod` command to change the permission of the files:

```
$ chmod u+x hello.sh
$ ls -l hello.sh
-rwx------ 1 user group 35 Dec  4 04:40 hello.sh
```

Now we have `x` added, which means executing permission has been given to the user. Let us execute this shell script again:

```
$ ./hello.sh
Hello world!!!
```

Tip: there is an alternative way to change permission. If you want to learn more about it, you can go to this link: http://linuxcommand.org/lts0070.php 

##Part 2: More syntax about shell scripts

###Variables

The following line of command shows how to define a variable:

```
x="Hello"
```

Bash does not allow us to leave a space on either side of `=` sign. The following will gives an error message:

```
x = "Hello"
```

And we can access it as follows:

```
$x
```

We can also access our argument variables by using `$0`, `$1`, `$2`,... The following script will show the value for those variables:

```
#!/bin/bash
echo $0
echo $1
echo $2
echo $#
```

we save our script as `showargv.sh` and change the permission for it, then we run the script:

```
$ ./showargv.sh first second
./showargv.sh
first
second
3
$ ./showargv.sh a b c d
./showargv
a
b
c
d
5
```

`$#` represents the number of the total arguments. `$0` represents the first argument which is script itself. `$1` represents your first provided argument. Likewise, `$2` represents the second provided argument, `$3` represents the third provided argument, and etc.

There are also some preset variables in Unix, and you can use those variables in any other programs:

```
BASH                #shell name
BASH_VERSION        #shell version
HOME                #home directory
PATH                #path settings
SHELL               #shell name
LOGNAME             #our logging name
USERNAME            #our user name
PWD                 #current working directory
PS1                 #prompt settings
OSTYPE              #os type
and more...
```

###Math operation

The following are some examples to perform math operations:

```
$ expr 1 + 1
$ expr 4 - 1
$ expr 3 * 4
$ expr 15 / 3
$ expr 30 % 7
$ echo `expr 30 % 7`
```

Do not use single or double quotes, it only works in the back quote. If you want to perform mathematic operations to assign value to a variable, you can look at the following example:

```
#!/bin/bash
x=0             #assign 0 into x
x=$((x+1))      #add 1 to x
```

###Exit status

After a shell script is executed, it returns two types of exit statuses:

* If the command is successful, it returns value zero(0)

* If the command is not successful, it returns a nonzero value in the range between 1 and 255;

We can examine the exit status of your last command by using parameter `$?`:

```
$ true; echo $?
0
$ false; echo $?
1
$ echo hello; echo $?
hello
0
$ dasadafada; echo $?
bash: dasadafada: command not found
127
$ rm cs100/; echo $?
rm: cannot remove 'cs100': Is a directory
1
``` 

We can see that only the first command is successful and it returns zero(0).

###read

The read statement can get a line from standard input and store it into a variable, the following is an example script:

```
#!/bin/bash
echo "please enter your name: "
read myname
echo "Hello $myname"
```

For more details, you can check this link: http://www.lehman.cuny.edu/cgi-bin/man-cgi?read+1

###convert

`convert` between image formats as well as resize an image, blur, crop, despeckle, dither, draw on, flip, join, re-sample, and much more. For example:

```
$ convert image.jpg image.png
```

The above line changed the format of the image from `.jpg` to `.png`.

For more details, please check this link: http://linux.die.net/man/1/convert

###test

Before I introduce the `if` statement, I want to introduce the `test` statement first, because it is often used with the 'if' statement to perform true/false decisions. The following example tests whether there are arguments provided:

```
#!/bin/bash
if test $# -eq 0; then 
echo "$0 : No argument provided"
exit 1
fi
```

or you can just use `[ $# -eq 0 ]` instead of `test $# -eq 0`:

```
#!/bin/bash
if [ $# -eq 0 ]; then 
echo "$0 : No argument provided"
exit 1
fi
```

`-eq` is a test operator which means equal to. There is a summary for test operators in the man page, here is the link: http://linux.die.net/man/1/test

###if

Based on the exit status of the commands in the `if` condition, the system can decide which commands to run. For example:

```
#!/bin/bash
if [ $# -eq 0 ]; then
echo "$0 : No argument provided"
exit 1
fi

if [ $1 -gt 0 ]; then
echo "$1 is positive"
elif [ $1 -eq 0 ]; then
echo "$1 is 0"
else
echo "$1 is negative"
fi
```

For the first `if`, I already introduced that it decides whether there are provided arguments. For the second `if`, the condition is: if the first provided argument is greater than 0, then the command is echo "$1 is positive". Then `elif` represents `else if`. Finally, we use `fi` to end this `if/else` statement.

For more details, please check this link: http://ss64.com/bash/if.html

###Loops

There are three types of loops: `while`, `until`, and `for`.

####while

Example:

```
#!/bin/bash
x=0
while [ $x -le 10 ]; do
    echo $x
    x=$((x+1))
done
```

At first, I set variable `X` equal to 0; the condition of the `while` loop is $X if it is less than or equal to 10. Then `do` the commands. We use `done` to finish the loop.

For more details, please check this link: http://linux.die.net/man/1/while

####until

In order to do the same work as `while`, the condition of `until` is the reverse condition of `while`. For example:

```
#!/bin/bash
x=0
until [ $x -g 10 ]; do
    echo $x
    x=$((x+1))
done
```

For more details, please check this link: http://bash.cyberciti.biz/guide/Until_loop

####for

I will give an example for converting the format of images in the current directory from `.jpg` to `.png`:

```
#!/bin/bash
for i in *.jpg; do
    convert "$i" "${i%.*}.png"
done
```

For more details, please check this link: http://www.cyberciti.biz/faq/bash-for-loop/

##Part 3 Functions

###Function Declarations

Declaring Bash functions is very simple. Both function `func_1 {echo “hello”;}` and `Func_2 () {echo “hello”;}` are valid function declarations. 
To call a function, simply invoke its name.

```
Fun_1 () { echo “hello”;}
Fun_2 ()
{
	echo “world”
}
Fun_1 #calls Fun_1()
Fun_2 #calls Fun_2()
```

We cannot call a function before it is declared, and there are no forward declarations bash like there are in c++. So the following code will give an error message.

```
fun
fun () { echo “hello”;}
```

Luckily there are no rules against multiple function declarations. The following code will output `hello world`.

```
Fun () { echo “hello ”; }
Fun
Fun () { echo “world”; }
Fun
```

Functions can be declared inside conditions and inside other functions. Once declared functions do not go out of scope. Therefore the following code is perfectly valid and will only output for user `Bro`.

```
if [ "$USER" =  Bro ]
then
	F1 () 
	{
		Sup_Bro () { echo “Sup Bro”; }
	}
	F1
Fi
Sup_Bro
```

###Function Parameters

Bash functions can take parameters in the same way that the bash script takes arguments. Simply by using `$1`, `$2`, and `$3` to reference the first, second, and third parameters accordingly.

```
Func_1 ()
{
	until [ -z "$1" ]  # Until no more parameters
	do
	 	echo -n "$1 "
	 	shift
	done
	echo “$1” #doesn’t output anything
}
Func_1 I Want Four Arguments
```
This code outputs: `I Want Four Arguments `. The `shift` command shifts the arguments to the left, deleting argument 1. Eventually the loop runs out of arguments and exits. The function then tries to print argument 1 but it has been removed and `echo “$1”` doesn’t output anything.

###Function Return

Functions can return integers. But it is not necessary as any variable created in the function does not go out of scope and can be accessed afterwards. 

```
Fun () { var1=1; var2=2; return 3; }
Fun
ret_var=$?
echo “$var1 ”
echo “$var2 “
echo “$ret_var”
```

This code outputs: `1 2 3`

##Part 4 Let’s talk About POSIX

####So what is Posix?

POSIX(Portable Operating System Interface) is “a family of standards specified by the IEEE to define the application programming interface (API), along with shell and utilities interfaces for software compatible with variants of the Unix operating system” … bla bla bla.

####Come again?

Basically POSIX is a bunch of rules that try to ensure that your program will run on all systems i.e.(non-GNO non-BSD systems like AIX or Solaris). This group of people, “IEEE”, gets together and figures out standards to make programs compatible on different version of UNIX. Then people making various programs, in this case BASH, and attempt to conform to these standards.

POSIX compliance is not a hard and fast rule. Bash has features that do not comply with POSIX standards. One common example is local variables.

```
func(){var="hello";}
func
echo "$var"
```

This code declares a var inside `func` then accesses it outside its scope. This is allowed in Bash but might not be something we want in our program. To change this so that var exists only in scope Bash uses the keyword `local`.

```
func(){local var=”hello”;}
func
echo ”$var”
```

Now our variable var exists in scope and our code no longer prints `hello`. POSIX however does not allow for the use of `local` and this code would not work on all variants of UNIX. I’m look at you Solaris 10, you done goofed things up for everybody. 

##Part 5 Cool Kids Use Bash

###Cool Case 1: Variables and Functions same name

Remember when I said that Bash doesn’t allow us to put spaces on either side of the `=` sign? Well I lied. Bash does allow for that syntax it just doesn’t do what you might expect. Let’s look at an example:

``` 
num(){echo ”$1”;  echo “$2”;} #creates function num that prints its first two parameters
num=3 #creates a variable num and assigns it value 3
num = 4 #calls function num and passes in = and 4 as parameters
num num num # calls function num and passes in variable num as a parameter twice
```

The following code outputs `=433`. OMG what is going on?

When we put a space after a name bash assumes that the name is a function and whatever follows the space are function parameters. Therefore when we enter `num = 4` it assumes we want to call function `num` and pass in parameters `=` and `4`. Similarly when we call `num num num` bash assumes that the first `num` is a function because it has a space after it and that the following `num`s are variable being passed into the function

####Pro Tip: 
If you want to see exactly what bash is executing add `–x` to the first line of your script i.e. `#!/bin/bash –x`. If you only want this for a particular part use commands `set –x` to start tracing, and `set +x` to stop tracing.


###Cool Case 2: Case Expressions

One of the cool features in Bash is pattern matching. Using functions `case` and `esac` we can do some very interesting things.
The general format for case conditionals is:

```
case [expression] in
[pattern]) [command] ;; 
[pattern]) [command] ;;
…
Esac
```

The following code takes asks the user to enter something and executes commands accordingly regardless of caps.

```
echo "Neo, take Red pill to wake up or blue pill to see how deep the rabbit hole goes? (red/blue)"
read ans
case $ans in
[Rr][Ee][Dd]) exit ;;
[Bb][Ll][Uu][Ee]) echo “the rabbit hole is 8.5 centimeters” 
                  echo “trololololololololol maaaatrix”;;
esac
```

####Bonus Tip: 
You could use case `date |cut -d" " -f1` to have your program do something different based on what day it is.

###Cool Case 3: Custom Linux commands with Aliases and Functions

One of the most useful hidden features in Bash is the ability to create custom commands.
Aliases are by far the easier, yet more limited method, so we will go over them first. Simply enter `alias open_it=cd /home/user/Desktop/folder/like_a_boss/never_again` and all we will have to do to execute this long command again is enter `open_it`. However, at the end of the session the alias will be gone.
To save our alias we open `~/.bashrc` file and add the line `alias open_it=cd /home/user/Desktop/folder/like_a_boss/never_again`. Then save and close. Now whenever we open bash, open_it will be a default alias.

#####What if I want to add arguments to my custom command?
Well this is where our newfound knowledge about bash scripts comes in. For this example we are going to create a simple command `mk2` that:

1. creates directories whose names we choose (arguments 2-n)
2. creates a text file in each of those directories, with a name of our choosing (argument 1)

```
#!/bin/bash
make_folder_with_file ()
{
	mkdir $2; #make directory
	cd $2; #enter directory
	touch $1; #create file
	cd ..; #exit directory
}
nm=$1 #save file name
shift #remove first argument
for var in “$@”; #for each remaining argument
do
	dirnm=$var
	make_folder_with_file $nm $dirnm
done
```

1. Save this file
2. `chmod +x mk2`
3. `cp mk2 /usr/bin/`

Now all you have to do to run your newly created command is enter `mk2` [file] [directory 1] [directory 2]...

##Conclusion
By writing shell scripts and gaining more knowledge about shell scripts, it helps us to have a better understanding about cs100 and the Unix system. If you want to learn more advanced skills and more details about shell script, here is the link: http://linux.die.net/man/1/bash or http://linuxcommand.org/lc3_writing_shell_scripts.php

Thank you for reading and have fun in cs100! :)

