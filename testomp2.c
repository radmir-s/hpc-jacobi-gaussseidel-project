#include <omp.h>
#include <stdio.h>
void report_num_threads(int level, int i, int j)
{
    #pragma omp single
    {
        printf("Level: %d, Threads in team: %d, Loop:%d %d\n", level, omp_get_num_threads(), i, j);
    }
}


void main()
{   
    int i, j;
    omp_set_nested(1);
    #pragma omp parallel for private(j) num_threads(2)
    for (i = 0; i < 4; i++)
    {
        report_num_threads(1,i,j);
        #pragma omp parallel for num_threads(4)
            for (j = 0; j < 4; j++)
            {
                report_num_threads(2,i,j);

            }
    }
    
}