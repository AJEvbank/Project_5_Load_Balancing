#! /bin/bash
clear
make
echo "**************************************************************************************************************************************"



# time mpirun -np 5 ./main -n 15 -max_num 5 -connectivity 2 -seed 69 -source 7
./main -n 8 -max_num 5 -connectivity 999 -part 333 -seed 76037 -print -full

echo "**************************************************************************************************************************************"

echo Done


# git update-index --assume-unchanged <file>
