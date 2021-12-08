## HPC project on Jacobi and Gauss-Seidel methods
### Description
Aim of the project is to find out a better way of implementing parallel computing on Jacobi and Gauss-Seidel methods.

### Platfrom 
Cluster: Stampede2 \
Programming language: C/C++ \
Parallel computing: OpenMP 

### Details
Array size: 32 128 512 2048 8192 \
Number of threads: 1 2 4 16 48 96 

### To run:
jacobi-omp-inout.c : gcc -fopenmp -DOUTER1=1 -DINNER1=1 \\
                    -DOUTER2=1 -DINNER2=1 -DLOOP=1 -DN=1000 \\
                    jacobi-omp-inout.c -o jacobi-omp-inout.exe; \\
                    ./jacobi-omp-inout

jacobi-inout.c version has two nested and one simple loops. \
Parameters INNER/OUTER gives control over the nested loops and LOOP over the simple one. \
