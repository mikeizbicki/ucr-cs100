CFLAGS=-ansi -pedantic -Wall -Werror

all:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(CFLAGS) src/shell.cpp -o bin/shell
	g++ $(CFLAGS) src/ls.cpp -o bin/ls

shell:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(CFLAGS) src/shell.cpp -o bin/shell

ls:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(CFLAGS) src/ls.cpp -o bin/ls
