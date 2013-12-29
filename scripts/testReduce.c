#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  
  FILE *f;

  f = fopen(argv[1], "r");

  double avrg_time = 0;
  double temp_time = 0;
  double time_sum = 0;

  int n = atoi( argv[2] );
  int i;

  for(i=0; i < n; i++){
    fscanf(f, "%lf\n", &temp_time);
    time_sum += temp_time;
  }

  fclose(f);

  avrg_time = time_sum / (double) n;

  printf(" avrg time = ( %.16f )\n", avrg_time);

  return 0;
}