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
