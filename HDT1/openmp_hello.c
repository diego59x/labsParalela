#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello_world(int N);

int main(int argc, char* argv[]){
  int countThreadsToUse = omp_get_max_threads();
  printf("Total threads %d\n", countThreadsToUse);

  int thread_count = 10;
  if(argc>1)
    thread_count = strtol(argv[1], NULL, 10);

  #pragma omp parallel num_threads(thread_count)
  hello_world(countThreadsToUse);

  return 0;
}

void hello_world(int N){
  int idThread = omp_get_thread_num();

  if (idThread % 2 == 0) {
    printf("Saludos del hilo %d \n" , idThread);
  } else {
    printf("Feliz cumpleanos numero: %d! \n" , N);
  }
}
