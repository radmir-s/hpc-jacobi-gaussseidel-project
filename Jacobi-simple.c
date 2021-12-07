#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef N
#define N 32
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
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = N/((i-j)*(i-j)+1);
        }
    }
	
	// Vector x
	for (i = 0; i < N; i++) {
		x[i] = 1;
	}
	
	// Vector b
	for (i = 0; i < N; i++) {
	b[i] = 0.0;
			for (j = 0; j < N; j++) {
					b[i] += A[i][j] * x[j];
			}
	}
	
}

int main() {
	int i, j;
	double res, r, sum;
	
	// Initiate arrays
	init_arrays();
	
	// Initial guess x0
	for (i = 0; i < N; i++) {
		x0[i] = 0;
	}	
	
	do {
		for (i = 0; i < N; i++) {
			sum = 0;
			for (j = 0; j < N; j++) {
				if (i != j) {
					sum += A[i][j]*x0[j];
				}
			}
		x1[i] = (b[i]-sum)/A[i][i];
		}
	
	for (i = 0; i < N; i++) {
		x0[i] = x1[i];
	}	
	
	res = 0;
	for (i = 0; i < N; i++) {
			r = b[i];
			for (j = 0; j< N; j++) {
				r -= A[i][j]*x1[j];
			}
		res += r*r;
	}	
	res = sqrt(res/N);
	
	} while(res>1e-6);
	
}
