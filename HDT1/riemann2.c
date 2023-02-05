/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 */

#include <stdio.h>
#include <stdlib.h>

#define A 1
#define B 40
#define C 20
#define N 10e6

double f(double x);     //La funcion a integrar
double calc(int n,int k, double a, double h, double integral );     //La funcion a integrar
double trapezoides(double a, double b, int n, int c);

int main(int argc, char* argv[]) {
  double integral;
  double a=A, b=B, c=C;
  int n=N;
  double h;

  if(argc > 3) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    c = strtol(argv[3], NULL, 10);
  }

  //---- Aproximacion de la integral
  //h = (b-a)/n;
  integral = trapezoides(a,b,n, c);

  printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
  printf("de la integral de %f a %f es = %.10f\n", a,b,integral);

  return 0;
}/*main*/

//------------------------------------------
// trapezoides
//
// Estimar la integral mediante sumas de Riemann
// Input: a,b,n,h
// Output: integral
//------------------------------------------
double trapezoides(double a, double b, int n, int c) {
  double integral, h, integralCopy;
  int k, k2;

  //---- Ancho de cada trapezoide
  h = (b-a)/n;
  //---- Valor inicial de la integral (valores extremos)
  integral = (f(a) + f(b)) / 2.0;

  #pragma omp parallel num_threads(c)
  integral, k2 = calc(n,k, a, h, integral);
    // printf("%d %d \n", integral, k2);
  #pragma omp atomic
  integralCopy += integral;
  k += k2;

  integralCopy = (integralCopy * h);

  return integral;
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

double calc(int n,int k, double a,double h,double integral) {
  for(k ; k <= n-1; k++) {
    integral += f(a + k*h);
  }

  return integral;
}
// 2 a 3 es 6.33