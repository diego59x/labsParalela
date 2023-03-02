#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int N = 10e8;
    unsigned t0, t1;

    t0=clock();

    double factor = 1.0;
    double pi_approx, sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += factor/(2*k+1);
        factor = -factor;
    }
    pi_approx = 4.0*sum;

    t1=clock();
    
    double time = ((double)t1-t0/CLOCKS_PER_SEC);
    printf("Pi: %.20f iterations %d \n SpeedUp: %Lf ", pi_approx, N, time);
    printf("Eficiencia %d\n ", 1);

    return 0;
}