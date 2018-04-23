#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);



  int i, n, seed, print;
  long double epsilon, check, max_num, min_num;

  CommLineArgs(argc,argv,&seed,&max_num,&n,&print,&epsilon,&min_num);

  srand(seed);

  if (world_rank == 0)
  {
    printf("n = %d, seed = %d, max_num = %Lf, print = %d, epsilon = %Lf, min_num = %Lf, world_size = %d\n\n",n,seed,max_num,print,epsilon,min_num,world_size);
    printf("LDBL_MAX = %Lf\n",(long double)LDBL_MAX);
    printf("LDBL_MAX = %Lf\n",(long double)1.0/(long double)LDBL_MAX);
  }

  long double * x = (long double *)calloc(n,sizeof(long double));
  long double * F = (long double *)calloc(n,sizeof(long double));
  long double * nF = (long double *)calloc(n,sizeof(long double));

  generateArray(n,max_num,min_num,x);

  force_calc_in_parallel(n,x,F,world_rank,world_size);

  if (DEBUG_1) printf("Passed array force calc on %d.\n",world_rank);

  parallelize_force_array(MCW,world_rank,world_size,n,F);

  if (DEBUG_1) printf("Passed array parallelization on %d.\n",world_rank);

  if (world_rank == 0 && print)
  {
    printf("\n\nx:\n\n");
    printArray(x,n);

    force_calc(n,x,nF);

    printf("\n\n     %-20s\t%-20s\n\n","F","nF");
    printArrays(F,nF,n);
    printf("\n\n");

    for(i = 0; i < n; i++)
    {
      check = nF[i] - F[i];
      if(fabs(check) > epsilon)
      {
        printf("Error at %d: %Lf != %Lf, check = %Lf\n",i,nF[i],F[i],check);
      }
    }
  }

  MPI_Finalize();
  return 0;
}
