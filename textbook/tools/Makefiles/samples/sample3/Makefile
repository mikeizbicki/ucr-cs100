objects = main.o file.o

# multiline
CFLAGS = -ansi -pedantic \
		 -Wall -Werror

program: $(objects)
	cc -o program $(objects)

main.o: file.h
file.o:

clean:
	rm -f program $(objects)
