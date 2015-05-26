#quick reference for `Makefile`s
`Makefile`s are a powerful tool which makes it easier for others to compile and run your code.
`Makefile`s are special files which are used with the `make` [command] (http://unixhelp.ed.ac.uk/CGI/man-cgi?make) to automatically build your projects.  

##compiling without `Makefile`s
We are already know how to compile our source code in the following manner:
```
$ g++ main.cpp -o main
```
The following command will compile `main.cpp` and create an executable `main` in the current working directory.
To run the executable we enter:
```
$ ./main
```
Let's see how we compile our source code with a `Makefile`.

##example - Hello World!
Let's say in our current working directory we have source code `hello.cpp` which will output `Hello World!`.
Let's look at a `Makefile` that will compile `hello.cpp` and create an executable `hello` in our current working directory.
The `Makefile` would look like this:
```
all:
	g++ hello.cpp -o hello
```
`all` is the default target, meaning the `make` command will execute this target if no other target is specified.
The second line will compile `hello.cpp` and create an executable `hello` in our current working directory.
We have our source code `hello.cpp` and our `Makefile`, let's test it out!
From the current working directory enter:
```
$ make
```
Then you should see the following:
```
g++ hello.cpp -o hello
```
This means that our source code successfully compiled and there is now an executable `hello` in the current working directory.
To run the executable enter the following:
```
$ ./hello
Hello World!
```
Our source code successfully compiled and we ran the executable `hello`. 
If we updated `hello.cpp` to output `Hello World! Great weather today!`, we make the necessary changes to the source code and enter `make`:
```
$ make
g++ hello.cpp -o hello
$ ./hello
Hello World! Great weather today!
```
We enter `make` after changing `hello.cpp` by doing so, we recompile `hello.cpp` and update the executable `hello`.
Whenever you update your source code, you can just enter the `make` command instead of the `(compiler) (source code) -o (executable name)` format of compiling source code.

##directories
In projects, `Makefile`s should be placed in the root directory, all source code should be placed in a directory called `src`. 
The executables you create from your `Makefile` should be stored in a directory called `bin`.
In our previous example we did not have our source code in a directory `src` and our executables in directory `bin`.
If we were to use the `ls` command in our previous example, the current working directory would look similar to this:
```
$ ls
hello   hello.cpp   Makefile   README.md
```
Instead, when you enter the `ls` command you should see something similar to this:
```
$ ls
Makefile   README.md    src
```
Note that we do not have the `bin` directory to store our executables.
We will make our `bin` directory and manage it in our `Makefile`.

##syntax
Before we move onto our next example we need to familiarize ourselves with some `bash` syntax. 
```
if [ ! -d bin ]; then mkdir bin; fi
```
This is a simple if-else statement which we will include in our `Makefile`. 
If there is not a directory called `bin`, then make a directory called `bin`. 
Note the spaces in `[ ! -d bin ]`, `bash` syntax requires there to be spaces for `[]` brackets in order to correctly identify variables. 
If the `Makefile` instead contained `if [! -d bin ]; then mkdir bin; fi` there would be error thrown. 

##example - directories
In our `src` directory, we have `hello.cpp` which will output `Hello World!`.
Here are the contents of the `Makefile`: 

```
all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/hello.cpp -o bin/hello
```

Here we are using an if-else statement to make sure we have a directory `bin` which will store our executables.
The next line compiles `hello.cpp` and stores the executable `hello` in our `bin` directory.
We now have our `Makefile` let's test it out!
From the root directory enter the `make` command:

```
$ make
```
You should see the following:
```
if [ ! -d bin ]; then mkdir bin; fi
g++ src/hello.cpp -o bin/hello
```
Our source code compiled successfully and the `bin` directory was made if it did not already exist. 
Now enter the following to run the executable:
```
$ bin/hello
Hello World!	
```
You are free to call `make` multiple times after this. 
Every time you call `make` the if statement checks if there is a directory called `bin`.
Then the executable in the `bin` directory will be updated.
The if statement used in this `Makefile` is very important since it ensures we have our `bin` directory. 
If we comment out the if statement in the `Makefile` and if we do not have a `bin` directory, calling `$ make` would throw the following error:
```
$ make
g++ src/hello.cpp -o bin/hello
/opt/rh/devtoolset-2/root/usr/libexec/gcc/x86_64-redhat-linux/4.8.2/ld: cannot open output file bin/hello: No such file or directory
collect2: error: ld returned 1 exit status
make: *** [all] Error 1
```
This occurred because we have this statement in our `Makefile` `g++ src/hello.cpp -o bin/hello`. 
We want to store our executable `hello` in a directory `bin` which does not exist.
To avoid this error, make sure in your targets there is an if-then statement checking for a `bin` directory and making the directory if necessary.
However when we call `$ make` and there is already a `bin` directory, there would be no errors and the executable would be created even if the if-then statement was commented out.
It is never safe to assume that everyone knows that the `bin` directory should be included, which is why we place the if-then statement in all targets.

We have our `Makefile` up and running! 
Now we can add other targets to our project.

###targets
In smaller projects our `Makefile` may only use the default target, however in large projects you may not want to compile the entire contents of the `src` directory, only specified source code.  
All source code under the default target will compile when you enter the `$ make` command from the terminal. 
If you have `foo.cpp` in your `src` directory and want to only compile and run the `foo` executable, your `Makefile` would look similar to this:

```
all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/file1.cpp -o bin/file1
	g++ src/foo.cpp -o bin/foo

file1:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/file1.cpp -o bin/file1

foo:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/foo.cpp -o bin/foo
```

##example - targets and variables
Let's add a new target to our `Makefile`.
In our `src` directory, we've added `iterator.cpp` which uses the `auto` feature of `c++11` to output the contents of a vector. 
We also would like to compile `iterator.cpp` with the following flags: `-Wall -Werror`.
For this we will use variables.
Variable syntax is as follows:
```
variable name = expression
```
To use a variable, we surround it with `$(` and `)`.
We're going to add a new target `iterator` to our `Makefile`, the `iterator` target will compile `iterator.cpp` with the `c++11` standard and the specified flags.
Let's make the following additions to our `Makefile`.

```
FLAGS=-Wall -Werror
STD=-std=c++11

all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/hello.cpp -o bin/hello
	g++ $(STD) $(FLAGS) src/iterator.cpp -o bin/iterator

hello:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/hello.cpp -o bin/hello

iterator:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(STD) $(FLAGS) src/iterator.cpp -o bin/iterator
```
We have just added two variables in our `Makefile`.
The first variable is `FLAGS`, which is set to the flags we want to compile specified source code with, `-Wall -Werror`.
The second variable is `STD`, which allows us to compile our source code with the `c++11` standard.
Although setting variables may seem redundant for such a simple example, in larger projects you can change the values of your variables once instead of changing every single occurrence throughout the `Makefile`.
We add `iterator.cpp` to the `all` target, and compile it with the `c++11` standard and specified flags by using the variables we declared.
We have now created two new targets, `hello` and `iterator`. 
Let's test our updated `Makefile`, compiling only the `iterator` target.

```
$ make iterator	
```
Entering `make iterator` specifies that we only want to compile the contents under the `iterator` target.
At this point we should see the following:

```
if [ ! -d bin ]; then mkdir bin; fi
g++ -std=c++11 -Wall -Werror src/iterator.cpp -o bin/iterator
```
The source code has successfully compiled. Let's run the executable.
```
$ bin/iterator
Contents of vector: 10 20 30
```
We've successfully added our new target `iterator` and compiled our code!

###clean
We should now feel confident in adding new targets to our `Makefile` to compile our code.
There is another special target called `clean` which should be included in `Makefile`s. 
The	`clean` target does not compile a specific file, rather it is used in `Makefile`s to remove the executables created by the `make` command.
The `clean` target in our case would look like this:

```
clean:
	rm -rf bin
```
When the user enters the following:
```
$ make clean
```
The directory which we used to store our executables, `bin` is forcefully removed by the `make clean` command.

With this knowledge you should now feel confident in starting your own projects and compiling your code with `Makefile`s.
