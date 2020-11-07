### INTEGRANTES: 

- Diana M. Garc
- Alexandra López - 1530267
- Alejandro Orobio - 1533627

## IMPLEMENTACIÓN DE ALGORITMOS UTILIZANDO MPI

- **_Método Monte Carlo:_** Calcula el valor de PI simulando variables aleatorias para obtener resultados numéricos. Se simulan dos puntos aleatorios (x,y) en un plano 2D con un dominio dentro de un cuadro de 1x1. Con un circulo imaginario situado dentro del cuadro se calcula la razón entre los puntos que se sitúan dentro del circulo y el número total de puntos generados.

- **_Método del Rectángulo:_** Calcula la integral de una función f(x) teniendo en cuenta que ésta es igual al area debajo del gráfico de f(x). Consiste en dividir la función en n intervalos (a -> b) del mismo tamaño (los cuales se ven como rectángulos) y sumar todas las areas de los rectángulos. Teniendo en cuenta que para cada rectángulo:

	- ancho = (b - a)/n
	- alto = f(a + (i-1) * ancho)

- **_Método de Newton Raphson:_** Calcula el cero de una función f(x) aproximándose a partir de un valor inicial _xo_.

