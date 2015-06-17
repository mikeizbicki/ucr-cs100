CFLAGS = -std=c++11 -Wall -pedantic

bin/main: bin/main.o bin/game.o
	g++ -g -o bin/main bin/main.o bin/game.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS) 

bin/game.o: src/game.cpp src/game.h
	mkdir -p bin	
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)
