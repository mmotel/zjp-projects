#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mpi.h"

double timeDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  double diff = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
    ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
  return diff / 1000000000;
}

double fun(double x){
  return pow(M_E, (-1) * pow(x,2) );
}

int main(int argc, char **argv){

  struct timespec start, end;

  int rank, np;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if(argc < 2){
    if(rank == 0){
      printf("Użycie: ./mpimain #size\n");
    }
    return -1;
  }

  double a = -2, b = 2;
  double n = (double) atoi( argv[1] );

  if(rank == 0){
    clock_gettime(CLOCK_MONOTONIC, &start);
  }
  double h = ( b - a ) / n;
  double x = a;
  double result = 0;
  double total = 0;

  int i;
  int i_start = rank * n / np;
  int i_stop = (rank + 1) * n / np;


  for(i = i_start; i < i_stop; i++){
    result += ( ( fun(x + (i *h)) + fun(x + ((i+1) *h)) ) / 2 ) * h;
  }

  MPI_Reduce(&result,&total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

  if(rank == 0){
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf(/*"Integral(e^(-x^2)) = */"%.16f\t", total);
    printf(/*"Time: */"%.16f\n", timeDiff(&end, &start));
  }

  MPI_Finalize();

  return 0;
}
