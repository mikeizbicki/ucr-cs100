#quick reference for ```Makefile```s
`Makefile`s are a powerful tool which makes it easier for others to compile and run your code.
`Makefile`s are special files which are utilized with the `make` [command] (http://unixhelp.ed.ac.uk/CGI/man-cgi?make) to automatically build your projects.  

In projects, `Makefile`s should be placed in the root directory, the files you wish to execute for the `Makefile` should be placed in a directory called `src`. 
The executables you create from your `Makefile` should be stored in a directory called `bin`.

##syntax
Before we compile and run our code with a `Makefile` we need to familiarize ourselves with some `bash` syntax. 
```
if [ ! -d bin ]; then mkdir bin; fi
```
This is a simple if-else statement which we will include in our `Makefile`. 
If there is not a directory called `bin`, then make a directory called `bin`. 
Note the spaces in `[ ! -d bin ]`, `bash` syntax requires there to be spaces for `[]` brackets in order to correctly identify variables. 
If the `Makefile` instead contained `if [! -d bin ]; then mkdir bin; fi` there would be error thrown. 

Setting [variables] (http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-5.html) is also good practice for `Makefile`s.
```
FLAGS=-ansi -pedantic -Wall -Werror
```
Here we have a variable `FLAGS` and are setting `FLAGS` to the `g++` flags we want to compile our source code with.
Note that there are no spaces after the `=`.

##example
We have source code `hello.cpp` in our `src` directory which outputs `Hello World!`.
Let's compile and run our code.
Here are the contents of the `Makefile`: 
```
FLAGS=-Wall -Werror
```
Here we are setting variable `FLAGS` to `-Wall -Werror`. 
Although this may seem redundant for such a small project, in larger projects you can just change the value of `FLAGS` instead of changing every occurrence of `-Wall -Werror`.  

```
all:
```
The first 'target' in our `Makefile` is `all`.
Because `all` is the first target declared in the `Makefile`, it is the default target for the `Makefile`. 
The `make` command will execute this target if no other is specified.
```
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(FLAGS) src/hello.cpp -o bin/hello
```

Here we are using an if-else statement to make sure we have a directory `bin` which will store our executables.
The next line compiles `hello.cpp` with the flags we specified and stores the executable `hello` in our `bin` directory.
We now have our `Makefile` let's test it out!
From the root directory enter the `make` command:

```
$ make
```
You should see the following:
```
if [ ! -d bin ]; then mkdir bin; fi
g++ -Wall -Werror src/hello.cpp -o bin/hello
```
Our source code compiled successfully. 
Now enter the following to run the executable:
```
$ bin/hello
Hello World!	
```
We have our `Makefile` up and running! 
Now we can add other targets to our project.

###targets
In smaller projects we may only have one default target, however in large projects you may not want to compile the entire contents of the `src` directory, only specified source code.  
All source code under the default target will compile when you enter the `$ make` command from the terminal. 
If you have `foo.cpp` in your `src` directory and want to only compile and run the `foo` executable your `Makefile` would look similar to this:

```
all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/file1.cpp -o bin/file1
	g++ src/foo.cpp -o bin/foo

foo:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/foo.cpp -o bin/foo
```

What's going on?
We have two targets the default target `all` and `foo`.
For both targets, we are using our if-else statement from earlier to make sure that we store our executables in the `bin` directory.
In this example `Makefile`, when you enter `$ make`, `file1.cpp` and `foo.cpp` will compile and executables `file1` and `foo` will be created and placed in the `bin` directory.
If you instead entered `$ make foo` then only `foo.cpp` would compile and the executable `foo` will be created in the `bin` directory.

##adding to our example
Let's add a new target to our `Makefile`.
In our `src` directory, we've added `iterator.cpp` which uses the `auto` feature of `c++11` to output the contents of a vector. 
We're going to add a new target `iterator` to our `Makefile`, the `iterator` target will compile `iterator.cpp` with the `c++11` standard and create an executable `iterator` and place it in our `bin` directory.
Let's make the following additions to our `Makefile`.

```
FLAGS=-Wall -Werror
STD=-std=c++11
```
We have just added a new variable to our `Makefile`, `STD` which will allow us to compile any source code we specify with the `c++11` standard.

```
all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(FLAGS) src/hello.cpp -o bin/hello
	g++ $(STD) $(FLAGS) src/iterator.cpp -o bin/iterator
```
We add `iterator.cpp` to the `all` target, compile it with the `c++11` standard and store executable `iterator` in the `bin` directory.

```
iterator:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(STD) $(FLAGS) src/iterator.cpp -o bin/iterator
```
This creates our second target in our `Makefile`, `iterator` and unlike the `all` target this target will only compile `iterator.cpp`.
Let's test our updated `Makefile`, compiling and running only the `iterator` target.

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
We should now feel confident in adding new targets to our `Makefile` to compile and run our code.
There is another special target called `clean` which should be included in `Makefile`s. 
The	`clean` target does not compile and run a specific file, rather it is used in `Makefile`s to remove the executables created by the `make` command.
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
