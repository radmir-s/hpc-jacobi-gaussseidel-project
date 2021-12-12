#!/bin/bash
#SBATCH -N 1
#SBATCH -p skx-normal
#SBATCH -t 03:00:00
#SBATCH -n 48


for size in 32 128 512 2048 8192; do
for inner1 in 1 2 4 8 16 48 96; do
for inner2 in 1 2 4 8 12; do
for outer2 in 1 2 4 8 12; do
for loop in 1; do

if [ $inner2 != 12 -o $outer2 != 12 ]; then

gcc -lm -fopenmp -DOUTER2=$outer2 -DINNER2=$inner2 -DINNER1=$inner1  \
-DLOOP=$loop -DN=$size \
gauss-seidel-omp.c -o gauss-seidel-omp.exe

./gauss-seidel-omp.exe > results/gs-$size-$inner1-$inner2-$outer2-$loop.txt

fi

done; done; done; done; done;

