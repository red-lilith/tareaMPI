#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITERATIONS 100
#define ALLERR 1.0e-308

int main(int argc, char** argv) {
    float x0=2; // initial x0
    float x1=0; //iteration result
    float h;
    int i;

    for(i=0; i<ITERATIONS; i++){
        h=(x0*x0*x0)/(3*x0*x0); //f(x)/f'(x) -> x^3/3x^2
        x1=x0-h;
        if(fabs(h)<ALLERR){
            printf("Cero = %lg \n", x1);
            return 0;
        }
        x0=x1;
    }
  
}
