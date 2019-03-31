#include <stdio.h>
#include <stdlib.h>

#define INTERVALS 10000

int main(int argc, char** argv) {
    int i; 
    double a, b, w, sum, x_i;

  
    // Initialize a, b, n
    a = 0.0;
    b = 1.0;

    w = (b-a)/INTERVALS;
    sum = 0.0;
    for (i = 0; i < INTERVALS; i++) { 
      x_i = a + (i-1)*w;
      sum = sum + (w*(x_i*x_i *x_i)); //f(x_i) = (x_i)³
    } 
  
    // Final Estimated Value 
    printf("Valor aproximado de la Integral = %0.15f \n",sum); 
  
}
