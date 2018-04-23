#ifndef FUNC

#define FUNC

#include "main.h"


void printArray(long double * array, int length)
{
  int i;
  for(i = 0; i < length; i++)
  {
    printf("%d => %Lf,\n",i,array[i]);
  }
  return;
}

void printArrays(long double * array1, long double * array2, int length)
{
  int i;
  for(i = 0; i < length; i++)
  {
    printf("%d => %-20.2Lf\t%-20.2Lf\n",i,array1[i],array2[i]);
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

void generateArray(int n, long double max_num, long double min_num, long double * array)
{
  int i;
  for(i = 0; i < n; i++)
  {
    array[i] = QUAN * randomSign();
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

int force_calc(int n, long double * x, long double * F)
{
  int i,j;
  long double diff, tmp;
  for(i = 1; i < n; i++)
  {
    for(j = 0; j < i; j++)
    {
      diff = x[i] - x[j];
      tmp = 1.0/(diff * diff * diff);
      F[i] += tmp;
      F[j] -= tmp;
      if(DEBUG_1 && (i == 7 || j == 7)) {
        printf("Sequential: At (%d,%d) tmp = %Lf, diff = %Lf\n",i,j,tmp,diff);
      }
    }
  }
  return 1;
}

#endif
