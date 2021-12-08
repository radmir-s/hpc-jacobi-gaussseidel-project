#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

// Seems like the nested loops of this code cannot be collapsed...

#ifndef LOOP
#define LOOP 1
#endif


#ifndef N
#define N 128
#endif

double A[N][N];
double b[N];

double x[N];
double x0[N];
double x1[N];




void init_arrays()
{
    int i, j, k;
	
	// Matrix A
    for (i = 0; i < N; i++) 
	{
        for (j = 0; j < N; j++) 
		{
			if (i==j) A[i][j] = N;
			else A[i][j] = (i+j)/N;
        }
    }
	
	// Vector x
	for (i = 0; i < N; i++) 
	{
		x[i] = 1;
	}
	
	// Vector b
	for (i = 0; i < N; i++) 
	{
	b[i] = 0.0;
			for (j = 0; j < N; j++) 
			{
					b[i] += A[i][j] * x[j];
			}
	}
	
}

int main() 
{
	int i, j;
	double res, r, sum;
	
	clock_t start, end;
	double cpu_time_used;

	printf("Array size is %d\n", N);
	
	// Initiate arrays
	init_arrays();
	
	// start timer
	start = clock();

	// Initial guess x0 as zero vector
	for (i = 0; i < N; i++) 
	{
		x0[i] = 0;
	}	
	
	int iter = 0;
	do {

		#pragma omp parallel for collapse(2) private(i,j) reduction(+:sum) num_threads(LOOP) 
		for (i = 0; i < N; i++) 
		{
			sum = 0;

			for (j = 0; j < N; j++) 
			{
				if (i != j) 
				{
					sum += A[i][j]*x0[j];
				}
			}
		x1[i] = (b[i]-sum)/A[i][i];
		}
	
	#pragma omp parallel for private(i) num_threads(LOOP) 
	for (i = 0; i < N; i++) 
	{
		x0[i] = x1[i];
	}	
	
	res = 0;

	#pragma omp parallel for private(i,j,r) reduction(+:res) num_threads(LOOP) 
	for (i = 0; i < N; i++) 
	{
			r = b[i];

			#pragma omp parallel for private(j) reduction(-:r) num_threads(INNER) 
			for (j = 0; j< N; j++) 
			{
				r -= A[i][j]*x1[j];
			}
		res += r*r;
	}	

	res = sqrt(res/N);
	iter += 1;
	printf("Iteration number is %d, resudial is %lf\n", iter, res);
	} while(res>1e-6);
	
	// end timer
	end = clock();
	cpu_time_used = 1000*((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time used: %lf ms\nOuter loops: %d\nInner loops: %d", cpu_time_used, OUTER, INNER);
}