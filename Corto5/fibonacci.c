#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fibonacci(int num);

int main()
{
    int r;
    unsigned t0, t1;

    t0=clock();
  
    for (int value = 0; value < 20; value++)
    {
        r = fibonacci(value);
        printf(" %d ", r);
    }
    t1=clock();

    double time = ((double)t1-t0/CLOCKS_PER_SEC);
    printf("\nSpeed Up %.10Lf ", time);
    printf("Eficiencia %d\n ", 1);

    return 0;
}

int fibonacci (int num)
{
    int num1, num2, total;
    if ((num == 0) || (num == -1)) 
        return 1;
    else {
        num1 = fibonacci(num - 1);
        num2 = fibonacci(num - 2);
        
        total = num1+num2;
    }
    return total;
}
