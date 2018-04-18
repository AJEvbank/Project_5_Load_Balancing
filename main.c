#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);



  int i, n, seed, max_num, print;
  double epsilon, check;

  CommLineArgs(argc,argv,&seed,&max_num,&n,&print,&epsilon);

  srand(seed);

  if (world_rank == 0) printf("n = %d, seed = %d, max_num = %d, print = %d, epsilon = %lf, world_size = %d\n\n",n,seed,max_num,print,epsilon,world_size);

  double * x = (double *)calloc(n,sizeof(double));
  double * F = (double *)calloc(n,sizeof(double));
  double * nF = (double *)calloc(n,sizeof(double));

  generateArray(n,max_num,x);

  force_calc_in_parallel(n,x,F,world_rank,world_size);

  printf("Passed array force calc on %d.\n",world_rank);

  parallelize_force_array(MCW,world_rank,world_size,n,F);

  printf("Passed array parallelization on %d.\n",world_rank);

  if (world_rank == 0 && print)
  {
    printf("\n\nx:\n\n");
    printArray(x,n);
    printf("\n\nF:\n\n");
    printArray(F,n);

    force_calc(n,x,nF);

    printf("\n\nnF:\n\n");
    printArray(nF,n);
    printf("\n\n");

    for(i = 0; i < n; i++)
    {
      check = nF[i] - F[i];
      if(fabs(check) > epsilon)
      {
        printf("Error at %d: %lf != %lf\n",i,nF[i],F[i]);
      }
    }
  }

  MPI_Finalize();
  return 0;
}
