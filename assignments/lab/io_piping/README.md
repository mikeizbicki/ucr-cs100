# I/O Redirection and Piping Lab

In this lab you will learn the basics and essentials to understand and implement I/O Redirection and piping using Unix.
There are three exercises, one at the end of the Input Redirection Tutorial, one at the end of the Output Redirection Tutorial, and one at the end of the Piping tutorial.
You will need to demonstrate that all three programs work to your TA.

##Output Redirection

Using I/O Redirection can make programming for a beginner level programmer, even an expert level programmer, much faster and simplier.
You can use I/O Redirection to simply manipulate files within the command line or to check thousands of lines of output from a program.
Once you know the ins and outs of I/O Redirection, programming will be a breeze!

For example open a terminal and try running:

```c++
$ ls src > ls.txt
```

Notice the output from 'ls src' was sent to ls.txt instead of directly to the terminal.
We can also see that the file ls.txt did not exist before we ran this command.

No, it is not magic! 
But it is pretty useful to help keep track of testing your programs.

To understand how this works, we will first learn the Unix system calls required to build I/O Redirection: `open()`, `close()`, `dup()`, and `dup2()`.

Refer to the dup/dup2 man page for more detailed information here:
[`dup()` man page](https://man7.org/linux/man-pages/man2/dup.2.html "man")

Or refer to the textbook from the UCR software construction course Github:
[Textbook](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/textbook/assignment-help/syscalls/io.md)

###But how does `dup()` and `dup2()` work with input redirection?

By default, we have 3 file descriptors represented as integers.
* 0 for standard input or messages to the terminal
* 1 for standard output or messages you type to the terminal
* 2 for standard error

Note: From now on, we will refer to standard input, standard output, and standard error as stdin, stdout and stderr, respectively.

When unspecified, programs will take input from 0(by default stdin) and output from 1(by default stdout).
Now let us say we instead wanted to send all output to a file.
Well, since `dup()` takes the LOWEST free number for a file descriptor, we need to free up file descriptor 1.
After freeing it, we can now use `dup()` to set out file as output.

But how do we free up a file descriptor you ask? By using the syscalls `open()` and `close()` of course!

Refer to the man pages for all the detailed information needed to understand`open()` and `close()` here:

* [`open()` man page](http://linux.die.net/man/2/open "man")

* [`close()` man page](http://linux.die.net/man/2/close "man")

`dup()` and `dup2()` pair with these system calls to make functioning i/o Redirection.

For example:

```c++
//close file descriptor 1 so we can use it for output
if(-1 == close(1))
{
	perror("Error: close()");
}
//open the file we want the output going to
int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
if(-1 == fd)
{
	perror("Error: open()");
}
```

Notice: We error check every system call we make.
ALWAYS REMEMBER TO ERROR CHECK!
You can find the return value of `dup()`, `dup2()`, `open()`, and `close()` on the man pages.

What this block of code does is it:
1. Uses the `close()` system call to close standard out which is still in file desciptor 1.
2. Calls `open()` on fd so that we can open standard output to write to the new file named "outfile".
The flags located in the second parameter of open indicate that it will have only write permission, a new file will be created if it does not exist already or it deletes the contents of "outfile" and adds the new output if it already exists.

Equivalently, we can avoid the use of `close()` by using the `dup2()` system call.

`dup2()` works similarly to `dup()` except that it will close whatever the second parameter is, if it isn’t closed already.
In other words, we don’t necessarily have to call `close()` before we call `dup2()`.

So in the example above, we can achieve the same results by doing this:

```c++
	int fd = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 00664);
	if(-1 == fd){
		perror("Error: open()");
	}
	if(dup2(fd, 1) == -1){
		perror("Error: dup");
	}
```

We do the same as above using open to take up the lowest open file descriptor, but instead of using `dup()`, we use `dup2()`.
Now we do not have to use the `close()` system call. 

Here is an example to illustrate the output redirection process:

![output](https://github.com/lboyd002/ucr-cs100/raw/2015spring/assignments/lab/io_piping/images/output2.png)


###Output Redirection Exercise:

The program io.cpp, located in the src folder, contains code that uses the fstream library to handle output redirection.
If you have forgotten how fstreams work, you can review it briefly.

Compile and run the provided io.cpp file.
Look over the output section of the code to understand what it is trying to do.
The program should do the following:
* It prints a line to an output file called "outfile.txt".
* If the file does not exist, it will be created.
* If the file already exists, it will be overwritten.

Now instead of using the fstream library to accomplish this, use the syscalls `open()`, `dup()`, and `dup2()` to do the same thing.

##Input Redirection

Another handy tool computer hackers use to make programming easier is input redirection.
This tool redirects standard input of a file and places it into standard input of a program.

Now make a file with this command:
```c++
$ touch outfile2.txt
```

and add "This is the contents of outfile." into the file with the vim editor.
Now try running the commands:

```c++
$ cat < outfile.txt
This is the contents of outfile.
```

You should see the text we added into outfile onto the terminal.
We redirected the text from outfile to output to the screen using input redirection.

Let's walk through another example of input redirection.

There is a file in this repository named "names.txt".
By running this command in the termial, we get:

```c++
$ sort < src/names.txt
50 Cent
Ann
Beyonce
Dan
Daniel
Diane
Donna
Eminem
Jessica
Julia
Lauren
Leon
Maroon 5
Megan
Michelle
```

Notice the output is sorted!
But when we run:

```c++
$ cat src/names.txt
Donna
Ann
Dan
Lauren
Daniel
Leon
Beyonce
Eminem
50 Cent
Maroon 5
Julia
Jessica
Diane
Megan
Michelle
```
The contents of our file are still out of order!
This is because we directed ONLY the output of the "names.txt" file into the sort program.

We can implement input redirection similarly to output redirection.

1. First we use the system call `open()` to open our file that we want to read from.
2. Then `close()` and `dup()` or `dup2()` are used to change the input redirection.

Here is an illistration to better understand input redirection:
![input](https://github.com/lboyd002/ucr-cs100/raw/2015spring/assignments/lab/io_piping/images/input.png)

###Input Redirection Exercise:

src/io.cpp also contains code that uses the fstreams library to handle input redirection.
Now look over the input section of the code to understand what it is trying to do.
The program should do the following:
* Prints the contents of an input file called infile.txt to standard out.

Now instead of using the fstream library to accomplish this, use the syscalls `open`, `dup`, and `dup2` to print input from a file to standard out.
You may use `execvp` and pass in `cat` to print to the screen.

##Piping

What exactly is a pipe?
Understanding what pipes are and how the system call pipe works is a bit confusing, so put down your phone and pay attention!

Using pipes makes navigating your terminal and using shortcuts SO much easier!
You can use pipes to run more that one command at once and pipes also connect the aspects of each command together!
With pipes, you can become an amazing hacker, maybe even unstoppable..
(Okay, maybe we will not go that far...)

In the terminal, we symbolize pipes with the pipe command: '|'.

The awesome thing about piping is that you can use more than one pipe to make programming super helpful and a lot more efficient!

Here is a quick example to walk through:

Run the cat command to output the names of the file src/names.txt:

```c++
$ cat src/names.txt
Donna
Ann
Dan
Lauren
Daniel
Leon
Beyonce
Eminem
50 Cent
Maroon 5
Julia
Jessica
Diane
Megan
Michelle
```
We can see the names are out of order.
If we want to sort the names, we can use the bash command `sort` to do so using a pipe.
Running the command:

```c++
$ cat src/names.txt | sort
50 Cent
Ann
Beyonce
Dan
Daniel
Diane
Donna
Eminem
Jessica
Julia
Lauren
Leon
Maroon 5
Megan
Michelle
```

Now the names from the file are sorted!
What this command did was it connected the output of the cat process to the input of the sort process.
So it outputs the content of names.txt AFTER it sorts the contents of the file.

For a different example, we will search through our terminal history.
First we run this command in our terminal:

```c++
$ history
```

Whoa, this prints out ALL the terminal history to stdout.
To shorten this output a little, or search for a specific command, in this case `g++`, we will use the grep command:

```c++
$ history | grep 'g++'
```

BOOM!!!
There is now a lot less history than before!
This command searches through your history and prints out instances where g++ was typed into the terminal.

###How do pipes work with `dup()`, `open()`, and `close()`?

Pipes have two ends, one for writing and one for reading.
The write end of the pipe connects to the read end of the pipe, connecting two processes that will run at the same time.
So what happens is, input from the first process is written into the write end of the pipe.
Then the information is read from the read end of the pipe, which runs the next process with the output from the first.

###Using the `pipe()` System Call

Refer to the `pipe()` man page for more detailed information here:
[`pipe()` man page](https://man7.org/linux/man-pages/man2/dup.2.html "man")

Using the system call `pipe()` creates a pipe, a one-way data channel that can be used for communication between two or more processes.
It takes stdout from the first process and links/pipes/channels/ it to the stdin to the other end of the pipe where the second process waits.

The pipe system call can be a little confusing to understand.
First, we create an array of integers of size 2 called fd.
The pipe syscall takes fd and assigns fd[0] to be the read end of the pipe and fd[1] is assigned the write end of the pipe.

This is how we create a pipe using the `pipe()` system call:

```c++
int fd[2];
pid_t pid;
int result;

//Creating a pipe
result = pipe (fd);
if (result == -1) {
    //failure in creating a pipe
    perror("There was an error creating the pipe");
    exit (1);
}
```

In this code example, first we create the array of new file descriptors that is needed for the `pipe()` system call.

#### Using `pipe()` with `fork()`, `wait()`, and `execvp()`
In your first assignment, you had to use the system calls `execvp()` and `fork()` to run programs in rshell.
We will now expand upon your knowlegde of these system calls with piping.

We need to make sure that the pipe system call is called before the the `fork()` system call.
This is because we need the pipe to be accessable in both processes.
If we were to call `pipe()` after we call `fork()` the pipe would only be accessable in the first child and not the others.

Every time `fork()` is called, we need to make sure to also call `wait()` the same amount of times. 
 
Here is an illistration to better understand pipe:

![piping](https://github.com/lboyd002/ucr-cs100/raw/2015spring/assignments/lab/io_piping/images/piping.jpg)

###Piping Exercise: 

Write a program that takes the output from one command and pipes it to the input of a second command.
You will be using the syscalls: pipe, fork, dup or dup2, open, close, execvp, and wait to accomplish this.

Specifically you will handle the case of `ls | grep 'a.out'`.
Here, the output of ls is take in one end of the pipe and sent out the other pipe to grep.

