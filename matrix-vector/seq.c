#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double timeDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  double diff = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
    ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
  return diff / 1000000000;
}

int main(int argc, char **argv){

  if(argc < 2){
    printf("Użycie: ./seqmain #size\n");
    return -1;
  }

  struct timespec start, end;

  int size = atoi(argv[1]);
  int i,j;
  //declare matrix and vectors
  int **M = (int**) malloc( size * sizeof(int*) );
  int *N = (int*) malloc( size * sizeof(int) );
  int *W = (int*) malloc( size * sizeof(int) );

  for(i=0; i < size; i++){
    M[i] = (int*) malloc( size * sizeof(int) );
  }

  srand( 151013 );

  //fillup matrix and vectors with data
  for(i = 0; i < size; i++){
      N[i] = rand() % 10;
      W[i] = 0;
    for(j=0; j < size; j++){
      M[i][j] = rand() % 10;
    }
  }

  //print filled up matrix and vector
  printf("\nMatrix\n");
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      printf("[%d] ", M[i][j]);
    }
    printf("\n");
  }
  printf("\nVector\n");
  for(i=0; i < size; i++){
    printf("[%d] ", N[i]);
  }
  printf("\n\n");

  clock_gettime(CLOCK_MONOTONIC, &start);

  //compute matrix/vector product
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      W[i] += M[i][j] * N[i];
    }
  }

  //print computed matrix/vector product
  for(i = 0; i < size; i++){
      printf("[ (%d)= %d ] ", i,W[i]);
  }
  printf("\n\n");

  clock_gettime(CLOCK_MONOTONIC, &end);

  printf("%.16f\n", timeDiff(&end, &start));

  //free allocated space
  free(M);
  free(N);
  free(W);
 
  return 0;
}
