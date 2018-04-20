#ifndef FUNC

#define FUNC

#include "main.h"

int force_calc_in_parallel(int n, double * x, double * F, int world_rank, int world_size)
{
  int i,j, calc_done = 0, counter = 0;
  double diff, tmp;
  int num_calc = (n * (n - 1)) / 2;
  int segment =  num_calc / world_size;
  int start = segment * world_rank;
  for(i = 1; i < n; i++)
  {
    for(j = 0; j < i; j++)
    {
      if(counter >= start && calc_done < segment)
      {
        diff = x[i] - x[j];
        tmp = 1.0/(diff * diff * diff);
        F[i] += tmp;
        F[j] -= tmp;
        calc_done++;
        if(DEBUG_2 && (i == 7 || j == 7)) {
          printf("Parallel: At (%d,%d) tmp = %lf, diff = %lf\n",i,j,tmp,diff);
        }
      }
      counter++;
    }
  }
  return 1;
}

void parallelize_force_array(MPI_Comm mcw, int world_rank, int world_size, int n, double * F)
{
  int i, j, k, max = getMax(world_size), receiver, sender, tag = 0;
  double * buffer = (double *)calloc(n,sizeof(double));
  MPI_Status status;

  for(i = 1, j = 2; j <= max; i *= 2, j *= 2)
  {
    if((world_rank % j) == i)
    {
      // Send
      receiver = world_rank - i;
      MPI_Send( F,
                n,
                MPI_DOUBLE,
                receiver,
                tag,
                mcw);

    }
    else if ((world_rank % j) == 0)
    {
      // Receive
      sender = world_rank + i;
      if(sender < world_size)
      {
        MPI_Recv( buffer,
                  n,
                  MPI_DOUBLE,
                  sender,
                  MPI_ANY_TAG,
                  mcw,
                  &status);
        for (k = 0; k < n; k++)
        {
          F[k] += buffer[k];
        }
      }
    }
  }
  return;
}

#endif
