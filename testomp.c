#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>


void main() {

    omp_set_nested(1);
    int thread, i, j;
    /*
    printf("----------------PARALLEL---------------\n");

    #pragma omp parallel num_threads(2) 
    {
        thread = omp_get_thread_num();
        printf("Thread # %d\n", thread);
    }

    printf("----------------LOOP---------------\n");

    #pragma omp parallel for private(i) num_threads(2)
    for (int i=0; i<10; i++)
    {
        thread = omp_get_thread_num();
        printf("Loop # %d, Thread # %d\n", i, thread);
    }
    
    printf("----------------REDUCTION---------------\n");

    int sum = 0;
    #pragma omp parallel for reduction(+:sum) private(i) num_threads(2)
    for (i=0; i<100; i++)
    {
        sum += i;
    }
    
    printf("Sum is %d\n", sum);

    

    printf("----------------COLLAPSE---------------\n");

    #pragma omp parallel for private(i,j) collapse(2) num_threads(2)
    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            thread = omp_get_thread_num();
            sleep(1);
            printf("%d -> %d %d\n",thread, i,j);
        }
    }

    */

    printf("----------------NESTED---------------\n");

    #pragma omp parallel for private(i,j) num_threads(2) schedule(dynamic)
    for (i=0; i<4; i++)
    {   
        #pragma omp parallel for private(j) num_threads(2)
        for (j=0; j<4; j++)
        {
            thread = omp_get_thread_num();
            sleep(1.5);
            printf("%d -> %d %d\n",thread, i,j);
        }
    }



} 