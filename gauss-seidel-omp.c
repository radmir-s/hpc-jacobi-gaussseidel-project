#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#ifndef N
#define N 64
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
	// Enable nested loops
	omp_set_nested(1);

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
	#pragma omp parallel for private(i) num_threads(LOOP) 
	for (i = 0; i < N; i++) 
	{
		x0[i] = 0;
	}	
	
	int iter = 0;
	do {

		for (i = 0; i < N; i++) 
		{
			sum = 0;

			#pragma omp parallel for private(j) reduction(+:sum) num_threads(INNER1)
			for (j = 0; j < N; j++) 
			{
				if (j<i)
				{
					sum += A[i][j]*x1[j];
				}
				else
				{
					sum += A[i][j]*x0[j];
				}

			}

		    x1[i] = (b[i]-sum) / A[i][i];
		}

		#pragma omp parallel for private(i) num_threads(LOOP) 
        for (i = 0; i < N; i++) 
        {
            x0[i] = x1[i];
        }


        //Compute residual	
        res = 0;

		#pragma omp parallel for private(i,j,r) reduction(+:res) num_threads(OUTER2) 
		for (i = 0; i < N; i++) 
		{
			r = b[i];

			#pragma omp parallel for private(j) reduction(-:r) num_threads(INNER2) 
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
	printf("Time = %lf ms\nOuter1 = %d\nInner1 = %d\nLoop = %d\nOuter2 = %d\nInner2 = %d", cpu_time_used, OUTER1, INNER1, LOOP, OUTER2, INNER2);


	for (size_t i = 0; i < N; i++)
	{
		printf("-- %lf", x0[i]);
	}
	
	
}