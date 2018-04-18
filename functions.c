#ifndef FUNC

#define FUNC

#include "main.h"


void printArray(int * array, int length)
{
  int i;
  for(i = 0; i < length; i++)
  {
    printf("%d,",array[i]);
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

#endif
