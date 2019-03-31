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
  int in_c[world_size];
  int range = ((INTERVAL*INTERVAL)/world_size);
  int my_c[world_size];
  // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int interval, i; 
  int sum = 0;
  double rand_x, rand_y, origin_dist, pi; 
  int circle_points = 0, square_points = 0;
  // Initializing rand() 
  srand(time(NULL)); 
    // We initialize vector
  for (i = 0; i < world_size; i++) in_c[i] = 0;
  MPI_Scatter(
      /* data         = */ &in_c, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT,
         my_c,
         world_size,
         MPI_INT, 
      /* root         = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
    
  if (world_rank == 0) {
    int my_circles = 0;
    printf("[R]Proceso %d: Calculando en el intervalo[0,%d]\n", world_rank,((world_rank*range)+range)-1);
    for(i=0;i<((world_rank*range)+range);i++){
      
      // Randomly generated x and y values 
      rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
      rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
      // Distance between (x, y) from the origin 
      origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
      // Checking if (x, y) lies inside the define 
      // circle with R=1 
      if (origin_dist <= 1) 
          my_circles++; 
    }

    circle_points = circle_points + my_circles;

    for(i=1;i<(world_size);i++){
      MPI_Recv(
      /* data         = */ &in_c, 
      /* count        = */ world_size, 
      /* datatype     = */ MPI_INT, 
      /* source       = */ i, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
       circle_points = circle_points + in_c[i];
    }

    pi = (double)(4 * circle_points) / (((world_size-1)*range)+range);
      
    printf("[R] Estimación Final de PI = %0.15f \n",pi);
  
  }
  else if (world_rank > 0) {
    int my_circles = 0;
    printf("[R] Datos recibidos en Proceso %d \n", world_rank);
    printf("[R]Proceso %d: Calculando en el intervalo[%d,%d]\n", world_rank,(world_rank*range),((world_rank*range)+range)-1);
    for(i=(world_rank*range);i<((world_rank*range)+range);i++){
      // Randomly generated x and y values 
      rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
      rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
      // Distance between (x, y) from the origin 
      origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
      // Checking if (x, y) lies inside the define 
      // circle with R=1 
      if (origin_dist <= 1) 
          my_circles++;  
    }
    in_c[world_rank] = in_c[world_rank] + my_circles;
    MPI_Send(
      /* data         = */ &in_c, 
      /* count        = */ world_size, 
      /* datatype     = */ MPI_INT, 
      /* destination  = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
  }
  MPI_Finalize();
}

