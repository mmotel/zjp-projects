all: build
	seqmain 1000000
	mpirun -np 4 mpimain 1000000

build: main.c seq.c
	gcc -Wall seq.c -o seqmain -lrt
	mpicc -Wall main.c -o mpimain -lrt
	gcc -Wall testReduce.c -o testReduce
clear:
	rm -rf *.o *.out mpimain seqmain testReduce time*

tests: clear build
	test.sh
