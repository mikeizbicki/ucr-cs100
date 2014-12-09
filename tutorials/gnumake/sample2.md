Working on large programs, it is inefficient to recompile everything for every change. The solution is prerequisites.

# first rule
program: main.o file.o
	cc -o program main.o file.o

# second rule
main.o: main.c file.h
	cc -c main.c

# third rule
file.o: file.c
	cc -c file.c

The syntax for rules is updated to:

[targets]: [prerequisites]
	[recipe]

When "make" or "make program" is run, the first rule is processed. Since its prerequisites are targets, they (the rules for main.o and file.o) are executed before the recipe.

If "main.o" does not exist, make executes the recipe for the second rule. Otherwise, make executes the recipe if and only if "main.c" or "file.h" is more recent than "main.o". In this way, needless recompilation is avoided.

After the prerequisites "main.o" and "file.o" are built (the -c option defers linking), if "program" does not exist, the recipe for the first rule is executed and the object files are linked. Otherwise, make executes the recipe if and only if "main.o" or "file.o" is more recent than "program".

If the target of "make [target]" already exists and none if its prerequisites are more recent than it, make will report that the target is already up to date and do nothing.

For the first sample, no prerequisites were used. If a file named "hello" already exists, then even after modifying the "hello.c" file, make will believe that the target is up to date and won't execute the recipe.

Everything from '#' to the end of line will be ignored. If it's in a recipe line, it will be passed to the shell instead.
