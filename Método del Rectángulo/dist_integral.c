#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

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
  int range = INTERVALS/world_size;
  // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int i; 
  double a, b, w, sum, x_i;
  // Initialize a, b, n
  a = 0.0;
  b = 1.0;
  w = (b-a)/INTERVALS;
  sum = 0.0;
  // Initialize x_i in every interval
  for(i=0;i<INTERVALS;i++)
    my_xs[i] = a + (i-1)*w;

  if (world_rank == 0) {
    for (i = 0; i < (INTERVALS/2); i++) { 
      sum = sum + (w*(my_xs[i]*my_xs[i] *my_xs[i])); //f(x_i) = (x_i)³
    } 
    
    MPI_Send(
      /* data         = */ &sum, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* destination  = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
    MPI_Recv(
      /* data         = */ &sum, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* source       = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
      printf("[R] Valor recibido en Proceso %d \n", world_rank);
      printf("Valor aproximado de la Integral = %0.15f \n",sum); 
  
  } else if (world_rank == 1) {
    MPI_Recv(
      /* data         = */ &sum, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* source       = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
    printf("[R] Valor recibido en Proceso %d \n", world_rank);
    printf("[R] Calculando desde Proceso %d \n", world_rank);
    for (i = (INTERVALS/2); i <INTERVALS; i++) { 
      sum = sum + (w*(my_xs[i]*my_xs[i] *my_xs[i])); //f(x_i) = (x_i)³
    }
    MPI_Send(
      /* data         = */ &sum, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* destination  = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
  }
  MPI_Finalize();
}

