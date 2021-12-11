#!/bin/bash
#SBATCH -N 1
#SBATCH -p skx-normal
#SBATCH -t 01:00:00
#SBATCH -n 48


for size in 32 128 512 2048 8192; do
for inner1 in 1 2; do
for outer1 in 1 2; do
for loop in 1 2; do
for inner2 in 1 2; do
for outer2 in 1 2; do

gcc -lm -fopenmp -DOUTER1=$outer1 -DINNER1=$inner1  \
-DOUTER2=$outer2 -DINNER2=$inner2 -DLOOP=$loop -DN=$size \
jacobi-omp-nested.c -o jacobi-omp-nested.exe

./jacobi-omp-nested > res-jacobi-$size-$inner1-$outer1-$loop-$inner2-$outer2.txt

done; done; done; done; done; done;