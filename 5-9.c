/* 

	Solo descomentar para ver el tipo schedule(guided) linea 64

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int thread_count;

double Trap(double a, double b, int n);
double f(double x);    /* Function we're integrating */

int main(int argc, char* argv[]) {
   double  integral;   /* Store result in integral   */
   double  a, b;       /* Left and right endpoints   */
   int     n;          /* Number of trapezoids       */

   if (argc != 2) {
      fprintf(stderr, "usage: %s <number of threads>\n", argv[0]);
      exit(0);
   }
   thread_count = strtol(argv[1], NULL, 10);

   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   
   integral = Trap(a, b, n);

   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %19.15e\n",
      a, b, integral);

   return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Use trapezoidal rule to compute definite integral
 * Input args:  
 *    a: left endpoint
 *    b: right endpoint
 *    n: number of trapezoids
 * Return value:  Estimate of Integral from a to b of f(x)
 */
double Trap(double a, double b, int n) {
   double  h, x, integral = 0.0;
   int  i,k; 

   h = (b-a)/n;
   integral += (f(a) + f(b))/2.0;
   
   int NUM_THREADS=thread_count;
   int iteraciones=n;
   int B[NUM_THREADS+1][iteraciones/NUM_THREADS+1];
	for(i=0;i<NUM_THREADS+1;i++)
		for( k=0;k<(iteraciones/NUM_THREADS +1);k++)
			B[i][k]=-1;
   
   
#  pragma omp parallel for schedule(static,1) default(none)   shared(B,a, h, n,thread_count) private(i, x)       reduction(+: integral) num_threads(thread_count)
/*
#  pragma omp parallel for schedule(guided) default(none)   shared(B,a, h, n,thread_count) private(i, x)       reduction(+: integral) num_threads(thread_count)

*/


   for (i = 1; i < n; i++) {
    
  	B[omp_get_thread_num()][i%thread_count ]=i;
         x = a + i*h;
         integral += f(x);
   
   }
for(i=0;i<NUM_THREADS;i++){
	
		printf("\nThread %d = ", i );

		for( k=0;k<(iteraciones/NUM_THREADS + 1);k++)
			if(B[i][k]>-1)// Para evitar que imprima basura del vector
			printf(" %d", B[i][k]);

	}
			printf("\n" );
   integral = integral*h;

   return integral;
}  /* Trap */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input arg:   x
 * Return val:  f(x)
 */
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  /* f */

