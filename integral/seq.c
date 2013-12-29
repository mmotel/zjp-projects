#include <stdlib.h>
#include <time.h>
#include <math.h>

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

  if(argc < 2){
    printf("Użycie: ./seqmain #size\n");
    return -1;
  }

  struct timespec start, end;

  double a = -2, b = 2;
  double n = (double) atoi( argv[1] );

  clock_gettime(CLOCK_MONOTONIC, &start);

  double h = ( b - a ) / n;
  double x = a;
  double result = 0;
  int i;

  for(i=0; i < n; i++){
    result += ( ( fun(x) + fun(x+h) ) / 2 ) * h;
    x += h;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  printf(/*"Integral(e^(-x^2)) = */"%.16f\t", result);
  printf(/*"Time: */"%.16f\n", timeDiff(&end, &start));

  return 0;
}
