#!/bin/bash
#SBATCH -N 1
#SBATCH -p skx-normal
#SBATCH -t 03:00:00
#SBATCH -n 48

module load tau/2.27.2
export TAU_MAKEFILE=$TAU/Makefile.tau-intelomp-icpc-papi-ompt-pdt-openmp
export TAU_METRICS="PAPI_L1_DCM"

for size in 32 128 512 2048 8192; do
for inner in 1 2 4 8 12; do
for outer in 1 2 4 8 12; do
for loop in 1; do

if [ $inner != 12 -o $outer != 12 ]; then

tau_cc.sh -lm -fopenmp -DOUTER=$outer -DINNER=$inner  \
-DLOOP=$loop -DN=$size \
jacobi-omp-nested.c -o jacobi-omp-nested.exe

./jacobi-omp-nested.exe > results/jacobi-$size-$inner-$outer-$loop.txt

export TAU_METRICS="PAPI_L1_TCM"
pprof > results/jacobi-l1-$size-$inner-$outer-$loop.txt

export TAU_METRICS="PAPI_L2_TCM"
pprof > results/jacobi-l2-$size-$inner-$outer-$loop.txt

export TAU_METRICS="PAPI_L3_TCM"
pprof > results/jacobi-l3-$size-$inner-$outer-$loop.txt

fi

done; done; done; done;