#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void main() {
    int thread;
    #pragma omp parallel num_threads(8) 
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
    


} 