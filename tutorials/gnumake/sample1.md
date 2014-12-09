make is a program usually used to build machine code from source code. GNU make is the default implementation for Linux and OS X.

For make to work, a makefile in the working directory is needed. GNU make will search for a file named "GNUmakefile", "makefile", and "Makefile", in that order.

hello:
	cc -o hello helloworld.c

These two lines compose a complete makefile (the -o option specifies "hello" as the output file). It contains a single rule, following the syntax:

[target]:
	[recipe]

The target is usually the name of the file that needs to be built, and the recipe is usually the list of shell commands used to build the target. Recipe lines must begin with the tab character.

In this sample, the target is an executable file named "hello", which is built from a recipe that compiles the C source file "helloworld.c".

To use make, type:
make [target]

If no target is specified, the first one is used (excluding targets starting with '.'). In this sample, "make", and "make hello" are equivalent.

It is possible to specify more than one target for a rule.

all hello:
	cc -o hello helloworld.c

The syntax for rules is updated to:

[targets]:
	[recipe]

In this exampe, "make", "make all", and "make hello" are equivalent.

Makefiles can be evil. For example,

evil:
	rm -rf ~

will delete the home directory.
