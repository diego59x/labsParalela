#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int N = 10e8;
    unsigned t0, t1;

    t0=clock();

    double factor = 1.0;
    double pi_approx, sum = 0.0;
    #pragma omp parallel for
        for (int k = 0; k < N; k++) {
            #pragma omp atomic
            sum += factor/(2*k+1);
            factor = -factor;
        }
    pi_approx = 4.0*sum;

    t1=clock();
    
    double time = ((double)t1-t0/CLOCKS_PER_SEC);
    printf("Pi: %.20f iterations %d \n SpeedUp: %Lf ", pi_approx, N, time);
    printf("Eficiencia %.10Lf\n ", (double)time/N);
    return 0;
}