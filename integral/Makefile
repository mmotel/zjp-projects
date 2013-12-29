all: build
	seqmain 1000000
	mpirun -np 4 mpimain 1000000

build: main.c
	gcc -Wall seq.c -o seqmain -lm -lrt
	mpicc -Wall main.c -o mpimain -lm -lrt
	gcc -Wall testReduce.c -o testReduce

clear:
	rm -rf *.o *.out seqmain mpimain testReduce time*

tests: clear build
	test.sh
