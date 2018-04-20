# Project_5_Load_Balancing

Names: Nick Alvarez, Caleb Bellando, Austin Eubank

Command Line Arguments:

seed: The randomization seed used on all the processes.

max_num: The largest value of any location generated randomly.

n: The length of the position and force arrays.

print: No argument required. If set, the arrays and results will be displayed.

epsilon: This is the difference value used when comparing two doubles. If the
        difference is greater than epsilon, the two values are considered to be
        unequal.


Our program runs both the parallelized version and the sequential version and
compares the results. We have found it to be sensitive to overflow with higher
values of n. To counter this, max_num may be lowered. The script go_A.sh will
demonstrate an example of this behavior.

All processes have the position array (x) stored. The x arrays are all generated
from the same random seed and are therefore the equivalent.

The parallelized algorithm runs a load balanced number of calculations on each
process. The total number of calculations is T = n(n-1)/2. Therefore, T is
assumed to be divisible by p, the number of processes.

The force_calc_in_parallel function runs the same loop as the sequential version
but tracks the number of inner iterations with two counters. Each process knows
where it should begin running calculations and how many to run. When the process
has finished running its quota of calculations, it completes the loop and then
proceeds to the parallelize_force_array function.

This function runs ceiling of log p iterations to gather the force arrays from
all the processes to process zero where the result is then compared to the
sequential result. Each process that receives a force array must then add the
values to its own force array before sending it on.
