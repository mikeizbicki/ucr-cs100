CFLAGS = -ansi -pedantic -Wall -Werror -std=c++11

all:
	touch class.txt
	g++ $(CFLAGS) maketxt.cpp -o maketxt
	maketxt
	sed -e "s///" class.txt > class2.txt
	cp class2.txt class.txt
	rm class2.txt

