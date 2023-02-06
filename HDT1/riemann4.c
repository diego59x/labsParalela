/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A 1
#define B 40
#define T 40
#define N 10e6

double f(double x);     //La funcion a integrar
double trapezoides(double a, double b, int n, double* global_result);

int main(int argc, char* argv[]) {
  double integral, global_result;
  double a=A, b=B;
  int n=N, t=T;
  double h;

  if(argc > 3) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    t = strtol(argv[3], NULL, 10);
  }

  //---- Aproximacion de la integral
  //h = (b-a)/n;
  #pragma omp parallel num_threads(t)
  trapezoides(a,b,n, &global_result);

  printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
  printf("de la integral de %f a %f es = %.10f\n", a,b,global_result);

  return 0;
}/*main*/

//------------------------------------------
// trapezoides
//
// Estimar la integral mediante sumas de Riemann
// Input: a,b,n,h
// Output: integral
//------------------------------------------
double trapezoides(double a, double b, int n, double* global_result) {
  double integral, h, local_sum;
  double local_a, local_b;
  int thread_ID = omp_get_thread_num();
  int thread_count = omp_get_num_threads();
  int k, local_n;

  //---- Ancho de cada trapezoide
  h = (b-a)/n;
  //---- Valor inicial de la integral (valores extremos)

  local_n = n/thread_count;
  local_a = a + thread_ID*local_n*h;
  local_b = local_a + local_n*h;

  local_sum = (f(local_a) + f(local_b)) / 2.0;

  for(k = 1; k <= local_n-1; k++) {
    local_sum += f(local_a + k*h);
  }
  local_sum = local_sum * h;

  #pragma omp critical
  *global_result += local_sum;
}/*trapezoides*/

//------------------------------------------
// f
//
// Funcion a ser integrada
// Input: x
//------------------------------------------
double f(double x) {
  double return_val;

  return_val = x*x;

  return return_val;
}/*f*/
