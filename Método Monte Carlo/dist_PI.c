#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 10000

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int interval, i; 
  double rand_x, rand_y, origin_dist, pi; 
  int circle_points = 0, square_points = 0;

  // Initializing rand() 
  srand(time(NULL)); 
  if (world_rank == 0) {
    for (i = 0; i < (INTERVAL * INTERVAL)/2; i++) { 
    // Randomly generated x and y values 
      rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
      rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
      // Distance between (x, y) from the origin 
      origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
      // Checking if (x, y) lies inside the define 
      // circle with R=1 
      if (origin_dist <= 1) 
          circle_points++;     
    } 
    
    MPI_Send(
      /* data         = */ &circle_points, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* destination  = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
    MPI_Recv(
      /* data         = */ &pi, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* source       = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
      printf("[R] PI recibido en Proceso %d \n", world_rank);
      printf("[R] Estimación Final de PI = %0.15f \n",pi);
  
  } else if (world_rank == 1) {
    MPI_Recv(
      /* data         = */ &circle_points, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* source       = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
    printf("[R] Datos recibidos en Proceso %d \n", world_rank);
    printf("[R] Calculando desde Proceso %d \n", world_rank);
    for (i = (INTERVAL * INTERVAL)/2; i < (INTERVAL * INTERVAL); i++) { 
      // Randomly generated x and y values 
      rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
      rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
      // Distance between (x, y) from the origin 
      origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
      // Checking if (x, y) lies inside the define 
      // circle with R=1 
      if (origin_dist <= 1) 
          circle_points = (circle_points+1); 
  
      // estimated pi after this iteration 
      pi = (double)(4 * circle_points) / (i+1);   
    }

    MPI_Send(
      /* data         = */ &pi, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* destination  = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
  }
  MPI_Finalize();
}

