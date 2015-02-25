#quick reference to ```Makefile```
```Makefile```s are special files which are utilized with the ```make``` [command] (http://unixhelp.ed.ac.uk/CGI/man-cgi?make) to automatically build your projects.

Why are ```Makefile```s so important? Instead of entering a command such as ```g++ main.cpp -o main``` and ```./main``` to run your program, you can just enter ```make``` to run your program. Most importantly in open source projects others can view your project and may want to work with it, however they may not know how to compile and run it. Creating ```Makefile```s will make it easier for others to compile and run your code.

In projects, ```Makefile```s should be placed in the root directory, the files you wish to execute for the ```Makefile``` should be placed in a directory called ```src```. To create a ```Makefile``` enter the following command:
```	$: touch Makefile```
To edit the ```Makefile``` enter:
``` $: [text editor] Makefile```

Let's say we have a program ```shell.cpp``` in our ```src``` directory, this program will take in user commands until ```exit``` is entered by the user. Let's try running our program using a ```Makefile``` instead of the *old* way. Here is the ```Makefile``` in its entirety:

```
CFLAGS=-ansi -pedantic -Wall -Werror

all:
  if [ ! -d bin ]; then mkdir bin; fi
  g++ $(CFLAGS) src/shell.cpp -o bin/shell

shell: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/shell.cpp -o bin/shell
```

Now let's figure out what's going on.
```
CFLAGS=-ansi -pedantic -Wall -Werror
```
Here we are setting a variable ```CFLAGS``` to the flags we want to run our program with.
We have two targets in this ```Makefile```. The first target is ```all``` and the second target is ```shell```. We will get into the specifics of targets later in this tutorial.

```
all:
  if [ ! -d bin ]; then mkdir bin; fi
  g++ $(CFLAGS) src/shell.cpp -o bin/shell
```
The first line of the ```all``` target is a simple if-else statement. If there is not a directory called ```bin```, then make a directory called ```bin```. 
The second line is compiling our program with ```g++``` using the flags we specified in line 1. It specifies the target is in the ```src``` directory and the file is ```shell.cpp```. ```-o bin/shell``` creates an executable ```shell``` in the ```bin``` directory. 

Note the spaces in ```[ ! -d bin ]``` ```bash``` syntax requires there to be spaces for ```[]``` brackets in order to correctly identify variables. If the Makefile instead contained ```if [! -d bin ]; then mkdir bin; fi``` you would see this:

```
	$: make
	if [! -d bin  ]; then mkdir bin; fi
	/bin/sh: [!: command not found
```

Now we have our ```Makefile``` lets run our shell program! From the root directory enter the ```make``` command.

```	
	$ make
```

At this point you should see the following:

```
	if [ ! -d bin ]; then mkdir bin; fi
	g++ -ansi -pedantic -Wall - Werror src/shell.cpp -o bin/shell
```

Our program has successfully compiled. That means we now have a directory ```bin``` which contains our ```shell``` executable. Let's run the executable by entering the following:

```
	$ bin/shell
	We are now in our program. 
	Now we will exit the program.
	exit
	~/cs100HW4
	$ 
```

#adding to your ```Makefile```
We have our ```Makefile``` up and running! Now let's add a program ```ls.cpp``` which list all files in our current directory. How do we change our ```Makefile``` to allow our ```ls.cpp``` program to run? The fix is very simple. Our ```Makefile``` after adding ```ls.cpp``` now looks like this: 

```
CFLAGS=-ansi -pedantic -Wall -Werror

all:
  if [ ! -d bin ]; then mkdir bin; fi
  g++ $(CFLAGS) src/shell.cpp -o bin/shell
  g++ $(CFLAGS) src/ls.cpp -o bin/ls

shell: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/shell.cpp -o bin/shell

ls: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/ls.cpp -o bin/ls
```

Recall at the beginning of the tutorial when I said we had 2 targets. ```all``` and ```shell```. What we have done is added ```ls.cpp``` to our ```all``` target and created a third target ```ls```.

The ```all``` target creates executables for all files listed under ```all:``` in the ```Makefile```. When you run ```make``` you will get the following output.

```
	$ make
	if [ ! -d bin ]; then mkdir bin; fi
	g++ -ansi -pedantic -Wall - Werror src/shell.cpp -o bin/shell
	g++ -ansi -pedantic -Wall - Werror src/ls.cpp -o bin/ls
```

By running ```make``` you utilize the ```all``` flag and have now created an executable ```shell``` and ```ls``` in the ```bin``` directory. In larger projects you may only want to create one specific executable. This is what the targets ```shell``` and ```ls``` are for.  

Let's run only our ```ls``` program:

```
	$ make ls
	if [ ! -d bin ]; then mkdir bin; fi
	g++ -ansi -pedantic -Wall - Werror src/ls.cpp -o bin/ls
```

As you can see, we've made only one executable ```ls``` in the bin folder. Now to run the executable:
```
	$ bin/ls
	.
	..
	.git
	README.md
	Makefile
	src
	bin
	~/cs100HW4
	$
```

TODO: mention ```clean``` and add it to ```Makefile```
