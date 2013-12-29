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

  int size = atoi( argv[1] );
  int i;
  int count = 0;

  double *x = (double*) malloc( size * sizeof(double) );
  double *y = (double*) malloc( size * sizeof(double) );

  srand( 161015 );

  for(i=0; i < size; i++){
    x[i] = (double) rand() / (double) RAND_MAX;
    y[i] = (double) rand() / (double) RAND_MAX;
  }

  clock_gettime(CLOCK_MONOTONIC, &start);

  for(i = 0; i < size; i++){
    if( (x[i] * x[i]) + (y[i] * y[i]) <= 1){
      count = count + 1; 
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  double pi_4 = ( (double) count ) / size;

  
  printf("\nsequence \t");
  printf(/*"size : */"%d\t", size);
  printf(/*"count: */"%d\t", count);
  printf(/*"PI   : */"%.8f\t", pi_4 * 4);
  printf(/*"time : */"%.16f\n", timeDiff(&end, &start));


  free(x);
  free(y);

  return 0;
}
