VPATH = src
CFLAGS = -ansi -pedantic -Wall -Werror
objects = $(addprefix obj/, main.o file.o)

bin/program: $(objects) | bin
	cc -o $@ $(objects)

obj/%.o: %.c
	cc $(CFLAGS) -c -o $@ $<
obj/main.o: file.h

$(objects): | obj

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	rm -rf obj bin

VPATH is a variable that tells make which directories to search for target and prerequisite files in addition to the working directory. In this sample, make will search "src/" in addition to "./".

Multiple directories are delimited by ':'. For example, "VPATH = src1:src2:../src3" tells make to search "src1/", "src2/", and "../src3" in addition to the working directory.

The addprefix function uses the syntax (addprefix [prefix], [names...]). It prepends [prefix] to each name in the whitespace-separated [names...] and returns the result. In this sample, the addprefix function is replaced by "obj/main.o obj/file.o".

Order-only prerequisites are listed after '|'. Unlike normal prerequisites, make does not check whether it is more recent than the target.

The syntax for rules is updated to:

[targets]: [normal prerequisites] | [order-only prerequisites]
	[recipe]

Whenever a file is added to, removed from, or renamed in a directory, the timestamp of the directory is updated. It is inefficient to rebuild a target just because the timestamp of its prerequisite directory was updated. That is why it is an order-only prerequisite.

"$<" is the first prerequisite of the rule. In this sample, it would be the C source file corresponding to the target object file.
