all: simple

simple: simple_model.cxx
	g++ simple_model.cxx -Werror -ansi -pedantic -fopenmp -Wall -g -O3 -lm -o simple

clean:
	-rm cellType* waveInput STDIN.* simple
	#be careful of links
	if [ -e simul ]; then if ! [ -L simul ]; then rm simple; fi ; fi

run:	simple
	./simple
