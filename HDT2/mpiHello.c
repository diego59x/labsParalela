#include <mpi.h>     //bibloteca básica para MPI
#include <string.h>
#include <stdio.h>
#define MESSTAG 0
#define MAXLEN 100
int
main (int argc, char **argv)
{
  //----(1) INICIO DEL ENTORNO----//
  MPI_Init (&argc, &argv);

  //----(2) CAPTURA DE DATOS DEL COMUNICADOR----//
  int rank, num, i;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num);
  
  //----(3) DISTRIBUCION DEL TRABAJO----//
  printf ("Hello from process %i of %i\n", rank, num);

  //----(4) FINALIZACION DEL ENTORNO----//
  MPI_Finalize ();
  return 0;
}
