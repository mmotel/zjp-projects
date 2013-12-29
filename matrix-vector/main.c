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

  struct timespec start, end;

  int np, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if(argc < 2){
    if(rank == 0){
      printf("Użycie: ./mpimain #size\n");
    }
    return -1;
  }

  int size = atoi(argv[1]);
  int rest = (np - (size % np)) % np;
  int n_size = size + rest;
  int part = n_size / np;

  int i,j;
  //declare matrix and vectors
  int *M = (int*) malloc( n_size * n_size * sizeof(int) );
  int *N = (int*) malloc( n_size * sizeof(int) );
  int *W = (int*) malloc( n_size * sizeof(int) );
  //fill up matrix and vectors with data
  for(i =0; i < n_size; i++){
    W[i] = 0;
  }
  //rest only on process with rank 0
  if(rank == 0){

    srand( 151013 );
    for(i = 0; i < n_size; i++){
      if(i >= size){
        N[i] = 0;
      } else {
        N[i] = rand() % 10;
      }
      for(j=0; j < n_size; j++){
        if(j >= size || i >= size){
          M[(i*n_size) +j] = 0; 
        } else {  
          M[(i*n_size) +j] = rand() % 10;
        }
      }
    }
  // //print filled up matrix and vector
    printf("\nMatrix\n");
    for(i = 0; i < n_size; i++){
      for(j = 0; j < n_size; j++){
        printf("[%d] ", M[(i*n_size) +j]);
      }
      printf("\n");
    }
    printf("\nVector\n");
    for(i=0; i < n_size; i++){
      printf("[%d] ", N[i]);
    }
    printf("\n\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
  }

  //local matrix and vectors
  int *local_M = (int*) malloc( sizeof(int) * part * n_size );
  int *local_N = (int*) malloc( sizeof(int) * part );
  int *local_W = (int*) malloc( sizeof(int) * part );

  for(i =0; i < part; i++){
    local_W[i] = 0;
  }

  //broadcast matrix and vector
  MPI_Scatter(M, part * n_size, MPI_INT, local_M, part * n_size, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(N, part, MPI_INT, local_N, part, MPI_INT, 0, MPI_COMM_WORLD);

  //compute matrix/vector product
  for(i = 0; i < part; i++){
    for(j = 0; j < n_size; j++){
      local_W[i] += local_M[(i*n_size) + j] * local_N[i];
    }
  }

  //gather matrix/vector product
  MPI_Gather(local_W, part, MPI_INT, W, part, MPI_INT, 0, MPI_COMM_WORLD);

  //print computed matrix/vector product
  if(rank == 0){
    clock_gettime(CLOCK_MONOTONIC, &end);
    for(i = 0; i < size; i++){
        printf("[ (%d)= %d ] ", i, W[i]);
    }
    printf("\n\n");
    printf("%.16f\n", timeDiff(&end, &start));
  }

  //free allocated space
  free(M);
  free(N);
  free(W);
  free(local_M);
  free(local_N);
  free(local_W);

  MPI_Finalize();
 
  return 0;
}
