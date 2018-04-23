#ifndef FUNC

#define FUNC

#include "main.h"

int force_calc_in_parallel(int n, long double * x, long double * F, int world_rank, int world_size)
{
  int i,j, calc_done = 0, flag = 0;
  long double diff, tmp;
  int num_calc = (n * (n - 1)) / 2;
  int segment =  num_calc / world_size;
  int start = segment * world_rank;
  int I = ((sqrt((8 * start) + 1) - 1) * 0.5) + 1;
  int J = start - I * (I - 1)/2;
  if (DEBUG_2) printf("I = %d, J = %d where start = %d on %d\n",I,J,start,world_rank);
  for(i = I; i < n && calc_done < segment; i++)
  {
    for(j = J; j < i && calc_done < segment; j++)
    {
      diff = x[i] - x[j];
      tmp = 1.0/(diff * diff * diff);
      F[i] += tmp;
      F[j] -= tmp;
      calc_done++;
      if (DEBUG_2 && flag == 0) {
        flag = 1;
        printf("i = %d, j = %d on %d\n",i,j,world_rank);
      }
    }
    J = 0;
  }
  return 1;
}

void parallelize_force_array(MPI_Comm mcw, int world_rank, int world_size, int n, long double * F)
{
  int i, j, k, max = getMax(world_size), receiver, sender, tag = 0;
  long double * buffer = (long double *)calloc(n,sizeof(long double));
  MPI_Status status;

  for(i = 1, j = 2; j <= max; i *= 2, j *= 2)
  {
    if((world_rank % j) == i)
    {
      // Send
      receiver = world_rank - i;
      MPI_Send( F,
                n,
                MPI_LONG_DOUBLE,
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
                  MPI_LONG_DOUBLE,
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
