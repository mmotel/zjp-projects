all: build
	mpirun -np 4 mpimain 10
#	seqmain 8

build: main.c
	mpicc -Wall main.c -o mpimain -lrt
	gcc -Wall seq.c -o seqmain -lrt
	gcc -Wall testReduce.c -o testReduce

clear:
	rm -rf *.o *.out seqmain mpimain time* testReduce

tests: clear build
	test.sh
