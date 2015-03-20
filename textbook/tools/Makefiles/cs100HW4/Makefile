CFLAGS=-Wall -Werror
STD=-std=c++11

all:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(CFLAGS) src/hello.cpp -o bin/hello

iterator:
	if [ ! -d bin  ]; then mkdir bin; fi
	g++ $(STD) $(CFLAGS) src/iterator.cpp -o bin/iterator

clean:
	rm -rf bin
