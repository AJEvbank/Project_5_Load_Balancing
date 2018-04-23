#ifndef MAIN_H

#define MAIN_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include "getopt.h"


#define MCW MPI_COMM_WORLD
#define SEED 1
#define MAX_NUM 100.00
#define QUAN ((((long double)rand())/((long double)RAND_MAX) * (long double)max_num) + min_num)
#define QUAN2 (((long double)((int)(QUAN * 100))/(long double)100) + 0.5)
#define PRINT 0
#define N 10
#define SOURCE 0
#define CONNECTIVITY 1
#define PART 1
#define INF (int)INFINITY
#define FULL 0
#define EPSILON 0.0001
#define MIN_NUM 1.00000

#define DEBUG_1 0
#define DEBUG_2 0

// (int)(((double)rand())/((double)RAND_MAX) * 32)
// u++
// Note: max size of int = +2147483647
// Note: min size of int = -2147483648
// Because of this, rows * cols cannot exceed 2147483647, so for a square
// matrix rows = cols = 46340.

enum isNumStates {
	INITIAL,
	PLUSORMINUS,
	ZERO,
	NUMBER,
	DECIMAL,
	ERROR
};
void CommLineArgs(int argc,
                  char ** argv,
                  int *seed,
                  long double *max_num,
                  int *n,
                  int *print,
                  long double *epsilon,
									long double *min_num
                 );

int isNumber(const char * str);

void printArray(long double * array, int length);

void printArrays(long double * array1, long double * array2, int length);

int getMax(int size);

void generateArray(int n, long double max_num, long double min_num, long double * array);

double randomSign();

int force_calc(int n, long double * x, long double * F);

int force_calc_in_parallel(int n, long double * x, long double * F, int world_rank, int world_size);

void parallelize_force_array(MPI_Comm mcw, int world_rank, int world_size, int n, long double * F);

#endif
