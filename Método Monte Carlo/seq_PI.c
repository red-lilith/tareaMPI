#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 10000

int main(int argc, char** argv) {
	int interval, i; 
    double rand_x, rand_y, origin_dist, pi; 
    int circle_points = 0, square_points = 0;

    // Initializing rand() 
    srand(time(NULL)); 
  
    // Total Random numbers generated = possible x 
    // values * possible y values 
    for (i = 0; i < (INTERVAL * INTERVAL); i++) { 
  
        // Randomly generated x and y values 
        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
        // Distance between (x, y) from the origin 
        origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
        // Checking if (x, y) lies inside the define 
        // circle with R=1 
        if (origin_dist <= 1) 
            circle_points++; 
  
        // Total number of points generated 
        square_points++; 
  
        // estimated pi after this iteration 
        pi = (double)(4 * circle_points) / square_points; 

    } 
  
    // Final Estimated Value 
    printf("Final Estimation of Pi = %0.15f \n",pi); 
  
}
