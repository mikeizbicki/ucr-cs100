CFLAGS = -ansi -pedantic -Wall -Werror
objects = $(patsubst %.c, %.o, $(wildcard *.c))

program: $(objects)
	cc -o $@ $(objects)

%.o:
main.o: file.h

clean:
	rm -f program *.o
