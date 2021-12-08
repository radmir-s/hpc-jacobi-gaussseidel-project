#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



void main() {
    int thread, i, j;
    #pragma omp parallel num_threads(2) 
    {
        thread = omp_get_thread_num();
        printf("Thread # %d\n", thread);
    }

    printf("-------------------------------\n");

    #pragma omp parallel for private(i) num_threads(2)
    for (int i=0; i<10; i++)
    {
        thread = omp_get_thread_num();
        printf("Loop # %d, Thread # %d\n", i, thread);
    }
    
    printf("-------------------------------\n");

    int sum = 0;
    #pragma omp parallel for reduction(+:sum) private(i) num_threads(2)
    for (i=0; i<100; i++)
    {
        sum += i;
    }
    
    printf("Sum is %d\n", sum);

    printf("-------------------------------\n");

    #pragma omp parallel for private(i,j) collapse(2) num_threads(2)
    for (i=0; i<10; i++)
    {
        
        for (j=0; j<10; j++)
        {
            thread = omp_get_thread_num();
            printf("%d %d %d\n",thread, i,j);
        }
    }

} 