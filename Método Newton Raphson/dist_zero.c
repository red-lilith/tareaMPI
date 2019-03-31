#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITERATIONS 100
#define ALLERR 1.0e-308

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  double my_xs[ITERATIONS];
  int range = ITERATIONS/world_size;
  // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int i; 
  float x0=2; // initial x0
  float x1=0; //iteration result
  float h;

  if (world_rank == 0) {
    for (i = 0; i < (ITERATIONS/2); i++){
      h=(x0*x0*x0)/(3*x0*x0); //f(x)/f'(x) -> x^3/3x^2
      x1=x0-h;
      if(fabs(h)<ALLERR){
        printf("[R] Proceso %d encontró Cero => %lg en ite => %d\n",world_rank, x1,i);
        MPI_Finalize();
        return 0;
      }
      x0=x1;
    } 
    MPI_Send(
      /* data         = */ &x0, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_FLOAT, 
      /* destination  = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
  } 
  else if (world_rank == 1) {
    MPI_Recv(
      /* data         = */ &x0, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_FLOAT, 
      /* source       = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
    printf("[R] Valor recibido en Proceso %d -> %lg\n", world_rank,x0);
    printf("[R] Calculando desde Proceso %d \n", world_rank);
    for (i = (ITERATIONS/2); i <ITERATIONS; i++) {
      h=(x0*x0*x0)/(3*x0*x0); //f(x)/f'(x) -> x^3/3x^2
      x1=x0-h;
      if(fabs(h)<ALLERR){
        printf("[R] Proceso %d encontró Cero => %lg  en ite => %d\n",world_rank, x1,i);
        MPI_Finalize();
        return 0;
      }
      x0=x1;
    }
  }
  MPI_Finalize();
}

