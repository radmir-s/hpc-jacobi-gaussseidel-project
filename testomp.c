#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void main() {
    int thread;
    #pragma omp parallel num_threads(2) 
    {
        thread = omp_get_thread_num();
        printf("Thread # %d\n", thread);
    }

    printf("-------------------------------\n");

    #pragma omp parallel for num_threads(2)
    for (int i=0; i<10; i++)
    {
        thread = omp_get_thread_num();
        printf("Loop # %d, Thread # %d\n", i, thread);
    }
    
    printf("-------------------------------\n");

    int sum = 0;
    #pragma omp parallel for reduction(+:sum) num_threads(2)
    for (int i=0; i<100; i++)
    {
        sum += i;
    }
    
    printf("Sum is %d", sum);

} 