#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

double timeDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  double diff = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
    ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
  return diff / 1000000000;
}

int main(int argc, char **argv){

  struct timespec start2, end2;

  int np, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if(argc < 2){
    if(rank == 0){
      printf("Użycie: ./seqmain #size\n");
    }
    return -1;
  }

  int size = atoi( argv[1] );
  int i;
  int count = 0;
  int local_count = 0;

  double *x = (double*) malloc( size * sizeof(double) );
  double *y = (double*) malloc( size * sizeof(double) );

  if(rank == 0){
    srand( 161015 );
  
    for(i=0; i < size; i++){
      x[i] = (double) rand() / (double) RAND_MAX;
      y[i] = (double) rand() / (double) RAND_MAX;
    }

    clock_gettime(CLOCK_MONOTONIC, &start2);
  }

  MPI_Bcast(x, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(y, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int i_start = (rank * size) / np;
  int i_stop = ((rank + 1) * size) / np;

  for(i = i_start; i < i_stop; i++){
    if( (x[i] * x[i]) + (y[i] * y[i]) <= 1){
      local_count = local_count + 1; 
    }
  }


  MPI_Reduce(&local_count,&count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);


  if(rank == 0){
    clock_gettime(CLOCK_MONOTONIC, &end2);
    double pi_4 = ( (double) count ) / size;

    printf("\nparallel \t");
    printf(/*"size : */"%d\t", size);
    printf(/*"count: */"%d\t", count);
    printf(/*"PI   : */"%.8f\t", pi_4 * 4);
    printf(/*"time : */"%.16f\n", timeDiff(&end2, &start2));
  }
 
  MPI_Finalize();

  free(x);
  free(y);

  return 0;
}
