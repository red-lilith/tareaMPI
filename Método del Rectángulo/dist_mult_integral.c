#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVALS 10000

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  double my_xs[INTERVALS];
  int range = (INTERVALS/world_size);
  double buf_xs[range];
  

  // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int i; 
  double a, b, w, integral, x_i;
  // Initialize a, b, n
  a = 0.0;
  b = 1.0;
  w = (b-a)/INTERVALS;
  integral = 0.0;
  // Initialize x_i in every interval
  for(i=0;i<INTERVALS;i++)
    my_xs[i] = a + (i-1)*w;

 MPI_Scatter(&my_xs,range,MPI_DOUBLE,buf_xs,range,MPI_DOUBLE,0,MPI_COMM_WORLD);
 printf("[R] Datos recibidos en Proceso %d \n", world_rank);
 printf("[R]Proceso %d: Calculando en el intervalo[%d,%d]\n", world_rank,(world_rank*range),((world_rank*range)+range)-1);
 double sum_i =0;
 for(i=(world_rank*range);i<((world_rank*range)+range);i++){
   sum_i = sum_i  + (w*(my_xs[i]*my_xs[i] *my_xs[i])); //f(x_i) = (x_i)³
 }

 double my_sums[world_size];
MPI_Gather( &sum_i, 1, MPI_DOUBLE, my_sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
if (world_rank == 0) {
  for(i=0;i<world_size;i++){
    integral = integral + my_sums[i];
  }
  printf("Valor aproximado de la Integral = %0.15f \n", integral); 
 }

 MPI_Finalize();
}

