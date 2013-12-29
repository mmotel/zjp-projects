#!/bin/bash

for i in {0..500..1}
	do
	./seqmain 1000 >> times1000.out
	mpirun -np 4 mpimain 1000 >> timep1000.out
	done

echo 'seq 1000' >> test.out
./testReduce "times1000.out" 500 >> test.out
echo 'mpi 1000' >> test.out
./testReduce "timep1000.out" 500 >> test.out

echo '1000 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 10000 >> times10000.out
	mpirun -np 4 mpimain 10000 >> timep10000.out
	done

echo 'seq 10000' >> test.out
./testReduce "times10000.out" 500 >> test.out
echo 'mpi 10000' >> test.out
./testReduce "timep10000.out" 500 >> test.out

echo '10000 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 100000 >> times100000.out
	mpirun -np 4 mpimain 100000 >> timep100000.out
	done

echo 'seq 100000' >> test.out
./testReduce "times100000.out" 500 >> test.out
echo 'mpi 100000' >> test.out
./testReduce "timep100000.out" 500 >> test.out

echo '100000 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 1000000 >> times1000000.out
	mpirun -np 4 mpimain 1000000 >> timep1000000.out
	done

echo 'seq 1000000' >> test.out
./testReduce "times1000000.out" 500 >> test.out
echo 'mpi 1000000' >> test.out
./testReduce "timep1000000.out" 500 >> test.out

echo '1000000 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 10000000 >> times10000000.out
	mpirun -np 4 mpimain 10000000 >> timep10000000.out
	done

echo 'seq 10000000' >> test.out
./testReduce "times10000000.out" 500 >> test.out
echo 'mpi 10000000' >> test.out
./testReduce "timep10000000.out" 500 >> test.out

echo '10000000 done'

tail -n 4 test.out
