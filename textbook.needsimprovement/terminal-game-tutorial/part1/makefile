bin/main: bin/main.o 
	g++ -g -o bin/main bin/main.o -std=c++11 -Wall -pedantic -lncurses

bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp 
