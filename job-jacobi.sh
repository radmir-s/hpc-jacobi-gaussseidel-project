#!/bin/bash
#SBATCH -N 1
#SBATCH -p skx-normal
#SBATCH -t 01:00:00
#SBATCH -n 48


for size in 32 128 512 2048 8192; do
for inner in 1 2 4 8 12; do
for outer in 1 2 4 8 12; do
for loop in 1; do

if [ $inner != 12 -o $outer != 12 ]; then

gcc -lm -fopenmp -DOUTER=$outer -DINNER=$inner  \
-DLOOP=$loop -DN=$size \
jacobi-omp-nested.c -o jacobi-omp-nested.exe

./jacobi-omp-nested.exe > results/jacobi-$size-$inner-$outer-$loop.txt

fi

done; done; done; done;