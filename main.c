#include "main.h"

int main(int argc, char ** argv)
{
  // MPI_Init(&argc,&argv);
  // int world_rank;
  // MPI_Comm_rank(MCW, &world_rank);
  // int world_size;
  // MPI_Comm_size(MCW, &world_size);



  int n, i, j, k, seed, max_num, print;

  CommLineArgs(argc,argv,&seed,&max_num,&n,&print);

  srand(seed);

  printf("n = %d, seed = %d, max_num = %d, print = %d\n\n",n,seed,max_num,print);








  // MPI_Finalize();
  return 0;
}
