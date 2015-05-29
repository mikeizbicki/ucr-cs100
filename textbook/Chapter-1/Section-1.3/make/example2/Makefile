# first rule
all program: main.o file.o
	cc -o program main.o file.o

# second rule
main.o: main.c file.h
	cc -c main.c

# third rule
file.o: file.c
	cc -c file.c
