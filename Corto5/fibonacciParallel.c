#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int fibonacci(int num);

int main()
{
    int r;
    unsigned t0, t1;

    t0=clock();

    // Clasic for loop on parallel
    #pragma omp parallel for
    for (int value = 0; value < 20; value++)
    {
    // A single task would call fibonacci()
    #pragma omp single
        r = fibonacci(value);
        printf(" %d ", r);
    }

    t1=clock();

    double time = ((double)t1-t0/CLOCKS_PER_SEC);
    printf("\nSpeed Up %.10Lf ", time);
    printf("Eficiencia %.10Lf\n ", (double)time/20);

    return 0;
}

int fibonacci (int num)
{
    int num1, num2, total;
    if ((num == 0) || (num == -1)) 
        return 1;
    else {
        // Shared due each task created needs
        // num1 and num2 to be modify and access
        #pragma omp task shared(num1)
            num1 = fibonacci(num - 1);
        #pragma omp task shared(num2)
            num2 = fibonacci(num - 2);
        
        total = num1+num2;
    }
    return total;
}
