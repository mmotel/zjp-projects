#!/bin/bash

for i in {0..500..1}
	do
	./seqmain 512 >> times512.out
	mpirun -np 4 mpimain 512 >> timep512.out
	done

echo 'seq 512' >> test.out
./testReduce "times512.out" 500 >> test.out
echo 'mpi 512' >> test.out
./testReduce "timep512.out" 500 >> test.out

echo '512 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 1024 >> times1024.out
	mpirun -np 4 mpimain 1024 >> timep1024.out
	done

echo 'seq 1024' >> test.out
./testReduce "times1024.out" 500 >> test.out
echo 'mpi 1024' >> test.out
./testReduce "timep1024.out" 500 >> test.out

echo '1024 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 2048 >> times2048.out
	mpirun -np 4 mpimain 2048 >> timep2048.out
	done

echo 'seq 2048' >> test.out
./testReduce "times2048.out" 500 >> test.out
echo 'mpi 2048' >> test.out
./testReduce "timep2048.out" 500 >> test.out

echo '2048 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 4096 >> times4096.out
	mpirun -np 4 mpimain 4096 >> timep4096.out
	done

echo 'seq 4096' >> test.out
./testReduce "times4096.out" 500 >> test.out
echo 'mpi 4096' >> test.out
./testReduce "timep4096.out" 500 >> test.out

echo '4096 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 8192 >> times8192.out
	mpirun -np 4 mpimain 8192 >> timep8192.out
	done

echo 'seq 8192' >> test.out
./testReduce "times8192.out" 500 >> test.out
echo 'mpi 8192' >> test.out
./testReduce "timep8192.out" 500 >> test.out

echo '8192 done'

tail -n 4 test.out

for i in {0..500..1}
	do
	./seqmain 16384 >> times16384.out
	mpirun -np 4 mpimain 16384 >> timep16384.out
	done

echo 'seq 16384' >> test.out
./testReduce "times16384.out" 500 >> test.out
echo 'mpi 16384' >> test.out
./testReduce "timep16384.out" 500 >> test.out

echo '16384 done'

tail -n 4 test.out