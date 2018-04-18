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
#include "getopt.h"


#define MCW MPI_COMM_WORLD
#define SEED 1
#define MAX_NUM 100
#define QUAN (int)(((double)rand())/((double)RAND_MAX) * (double)max_num) + 1
#define PRINT 0
#define N 10
#define SOURCE 0
#define CONNECTIVITY 1
#define PART 1
#define INF (int)INFINITY
#define FULL 0

#define DB1 0
#define DB2 0

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
                  int *max_num,
                  int *n,
                  int *connectivity,
                  int *part,
                  int *full,
                  int *print
                 );

int isNumber(const char * str);

void printGraph(int n, int * graph, int print);

void printArray(int * array, int length);

void printValue(int value);

int min(int i, int j);

int isConnected(int connectivity, int part);

void makeGraph(int n, int * edge, int max_num, int connectivity, int part);

void makeGraphTotal(int n, int * edge, int max_num, int connectivity, int part);

int addWithInfinity(int A, int B);

int getMax(int size);

void getkRowAndCol(MPI_Comm mcw, int n, int k, int * kthCol, int * kthRow, int * myOriginMatrix);

int isDiagonalProcess(int world_rank, int world_size);

void loopOperation(int offset, int level, int * receivedArray, int rootP);

void ParallelizeMatrix(MPI_Comm mcw, int * myMatrix, int slice, int n, int rootP, int * recv);

#endif
