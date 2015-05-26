CFLAGS=-Wall -Werror
STD=-std=c++11

all:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ src/hello.cpp -o bin/hello
	g++ $(STD) $(CFLAGS) src/iterator.cpp -o bin/iterator

hello:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ src/hello.cpp -o bin/hello

iterator:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(STD) $(CFLAGS) src/iterator.cpp -o bin/iterator

clean:
	rm -rf bin
