#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    const int count = 10000000;     ///< Number of array elements
    const int threads = omp_get_max_threads();         ///< Number of parallel threads to use
    const int random_seed = 920215; ///< RNG seed

    int* array = 0;                 ///< The array we need to find the max in
    int  max   = -1;                ///< The maximal element

    printf("OpenMP: %d;\n======\n", _OPENMP);

    /* Initialize the RNG */
    srand(random_seed);

    /* Generate the random array */
    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand(); }

    /* Find the maximal element */
#pragma omp parallel num_threads(threads) shared(array, count) reduction(max: max) default(none)
    {
#pragma omp for
        for(int i=0; i<count; i++)
        {
            if(array[i] > max) { max = array[i]; };
        }
        printf("-%d- My max is: %d;\n", omp_get_thread_num(), max);
    }

    printf("======\nMax is: %d;\n", max);
    return(0);
}