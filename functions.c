#ifndef FUNC

#define FUNC

#include "main.h"


void printArray(double * array, int length)
{
  int i;
  for(i = 0; i < length; i++)
  {
    printf("%d => %lf,\n",i,array[i]);
  }
  return;
}

int min(int i, int j)
{
  if (i < j)
  {
    return i;
  }
  return j;
}

int getMax(int size)
{
  int max = 2;
  while (max < size)
  {
    max *= 2;
  }
  return max;
}

void generateArray(int n, double max_num, double * array)
{
  int i;
  for(i = 0; i < n; i++)
  {
    array[i] = QUAN2 * randomSign();
  }
  return;
}

double randomSign()
{
  int rdn = rand();
  if((rdn % 2) == 0)
  {
    return 1.0;
  }
  else
  {
    return -1.0;
  }
}

int force_calc(int n, double * x, double * F)
{
  int i,j;
  double diff, tmp;
  for(i = 1; i < n; i++)
  {
    for(j = 0; j < i; j++)
    {
      diff = x[i] - x[j];
      tmp = 1.0/(diff * diff * diff);
      F[i] += tmp;
      F[j] -= tmp;
      if(DEBUG_1 && (i == 7 || j == 7)) {
        printf("Sequential: At (%d,%d) tmp = %lf, diff = %lf\n",i,j,tmp,diff);
      }
    }
  }
  return 1;
}

#endif
