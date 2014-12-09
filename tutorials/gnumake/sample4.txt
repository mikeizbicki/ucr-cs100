CFLAGS = -ansi -pedantic -Wall -Werror
objects = $(patsubst %.c, %.o, $(wildcard *.c))

program: $(objects)
	cc -o $@ $(objects)

%.o:
main.o: file.h

clean:
	rm -f program *.o

The wildcard function uses the syntax "$(wildcard [pattern])". It returns a list of space-separated files that match the pattern.

The '*' character matches any string. In this sample, $(wildcard *.c) is replaced by all .c files: "file.c main.c".

The patsubst function uses the syntax $(patsubst [pattern], [replacement], [text]). It replaces all whitespace-separated words in [text] that match [pattern] with [replacement].

The '%' character matches any string for all instances of '%' in an expression. In this sample, the pathsubst function is replaced by "file.o main.o".

"$@" is the target of the rule. In this sample, "cc -o $@ $(objects)" is equivalent to "cc -o program $(objects)".

"%.o:" matches all object files. Because "main.o" requires "file.h" in addition to "main.c", that prerequisite is indicated in the next line. The implicit rules handle the rest.

The rule for "clean" has been modified to use the wildcard. It is subtly different from the previous version, which removed all files specified by "objects" – this version removes all files ending in ".o".
