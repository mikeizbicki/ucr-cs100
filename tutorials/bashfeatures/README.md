
1. I/O redirection
---
An important feature of Bash is I/O redirection.I/O Redirection allows the user to manipulate the standard stream of bash commands.To do this redirection must make use of the standard file handles.These file handles are stdin,stdout, and stderr which are standard input,standard output and standard error respectively.Each of these file handles have a number associated with them.These numbers range from 0,1 and 2 to with each of them belong to stdin,stout and stderr respectively.One last thing to note about file handles is that stdin is associated with the keyboard,stdout to the screen and lastly stderr to error messages.

You can also open other file descriptors to have additional streams to redirect to which become useful with piping which will be covered later.

descriptor | name | meaning
------ | ------- | -----
0 | stdin  |  Standard Input
1 | stdout | Standard Output
2 | stderr | Standard Error


Every command in bash has a default location to where it read and write to and from.What redirection allows the user to do is change the  default read and write direction stream .These file descriptor can be represented  in the way

As can be seen  each command automatically  defaults to a similar setup with each file descriptor being assigned to the default stdin ,stderr and stdout.

Redirection has few different command outputs to switch the stream

1.`<` for standard input redirection

2.`>` for standard output redirection

3.`>>` is also standard output redirection but instead of overwriting it appends to  the file

4.`<<<` for stdin of a string

Another feature is the ability to pre-append or append these commands  with a file descriptor which affects the redirection of the command such as

1.1

2.2

3.& (this redirects to both stdout and stderr)

Redirection is written in the form of a bash command followed by the redirection symbol and lastly followed the file that is getting read or written from.In a form similar to    

```
ls > newFile
cat < newFile
pwd >> newFile
cat <<< "hello"
ls 2> errors

```

If one were to use the `>` redirection  in a command such as ` ls > newFile ` the output would switch from being outputted to the screen to the newFile the was created
so the output of  just

```
ls
```
Would print out

```
OUTPUT:
C:\nppdf32Log\debuglog.txt  Documents  Music     Public     Videos
Desktop                     Downloads  Pictures  Templates
```
as opposed to

```
ls > newFile
```
which will print out
```
OUTPUT:
```
which displays nothing to the screen since it was redirected to the file

As way to confirm that the this process actually took place one can just use
```
cat  newFile

```
which will print out
```
OUTPUT:
C:\nppdf32Log\debuglog.txt
Desktop
Documents
Downloads
Music
newFile
Pictures
Public
Templates
Videos
~
```
Lastly redirection is able to mix and match the various input and output redirection
```
cat < newFile >newFile2

```
2.Pipes
---
Pipes are a useful tool available in bash. What the pipe essentially does is redirect the output of the  left command to the input of the right command which in turn if no other     pipes follow prints the result to the screen.The pipe is command follows the general layout
```
left command | right command
```
With "|" being the bash character for piping.


A more technical explanation of piping is that the pipes create a temporary file which the output of the left hand  command is written to the temporary file.This is done by bash by using redirection to  redirect the left hand commands regular  output of stdout to the stdin of the temporary file.  After this the right hand command reads from  this temporary file created by the pipe allowing the right hand pipe to use the output of the left hand command.The process for the right hand command works in a simmilar fashion but instead swapping stdin from keyboard to stdin from the file.This is represented visually.



An example of the pipe command is
```
ls | cat
```
which takes the output of the ls command and puts it into a temporary file and is read as input by the cat command.

The completed output of this example should show
```
:\nppdf32Log\debuglog.txt
Desktop
Documents
Downloads
Music
newFile
Pictures
Public
Templates
Videos
~

```
This process is repeated no matter how many pipes are used in the command line
```
ls| grep d | cat
```
```
OUTPUT:
C:\nppdf32Log\debuglog.txt
Downloads
Videos
~
```

3.Variables
---
Variables are feature of bash scripting.It is similar to variables in most programming languages.As such variables can be global or local.
Global variable as the name implies is variable that has universal scope.It can be used from anywhere in the code.
To assign a global variable  on a new line give the variable a name  immediately followed by  = then assign some type of information to the variable.

```
#! /bin/bash
globalvar="my var"
```
Following this if you want to use this variable you need to pre-append the $ character to the name of your variable so bash knows what to look for.

A local variable on the other hand is one the is limited in scope.A local variable can only be used in the block of code it was created in.

For example a variable created inside of a function would be limited in its scope and cannot be accessed by other function or commands outside of said function.
Variables created globally can be used inside of functions .


```
#! /bin/bash
func(){
    local var="local"
}
```
As the example shows to declare a local variable one needs put local before the variable name

Some general rules of variables are

1.Can not  begin with a number must start with  letter

2.No spaces in variable name

3.No punctuation marks


4.Workflow Statements
---

When using bash you may come to need a way to let your command change its workflow
The way to accomplish this is with condition such, if, else and else if
These features are similar in usage to other programming languages

The general layout  of an if conditional is
```
if [ cmd ];then
fi
```
or you can make  it with the `test` command 
```
if test cmd;then
fi
```
Following the then command is where you add whatever code is needed

A unique feature of the bash conditional is that it comes with built-in checks and comparisons
Some checks for files would be
* -ge is the equivalent >=
* -r checks file existence and read permission
* -eq is equivalent of ==

The [ and test command have checks specific depending on if it is numeric, string , or a file.

For a complete list of checks and comparisons check the [man](http://linux.die.net/man/1/test) page

Like regular conditionals bash also has the `else` which just comes after the `then` statement
```
if [ cmd ];then
  echo true
else 
  echo false
fi
```
If you want to check more conditions if the first one fails but before it gets to the final else then
using the if/elif/else statement would be preferable

The elif conditional gives you the choice of adding second block of code to run if it passes the conditional.You can also add as many elif in between the first if and final else or not else at all.

```
if [cmd];then
    echo "if"
elif [cmd]
    echo first
else
    echo final
fi
```
