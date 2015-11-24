/* 

	5-3.c

   Con una thread se demora 0.012789 segundos
   Con dos thread se demora 0.006439 segundos
 
   Esto demuestra que se esta paralelizando bien porque el trabajo se
   repartio entre dos threads lo que produjo que el tiempo sea la mitad.	

  Compile: gcc -g -Wall -fopenmp -o omp_trap1 omp_trap1.c
  Usage:   ./omp_trap1 <number of threads>


 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n);

int main(int argc, char* argv[]) {
   double  integral = 0;  /* Store result in integral      */
   double  a, b;          /* Left and right endpoints      */
   int     n;             /* Total number of trapezoids    */
   int     thread_count;

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   
   double TI=omp_get_wtime();
# pragma omp parallel num_threads(thread_count) reduction(+: integral) 
   integral += Trap(a, b, n);   /* Can also do += */
#pragma omp barrier
   double TF=omp_get_wtime();

 	
   printf("Tiempo que se demora :%f\n", TF-TI);

   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %.15e\n",
      a, b, integral);

   return 0;
}  /* main */


void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
} 
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  /* f */


double Trap(double a, double b, int n) {
   double  h, x, integral;
   double  local_a, local_b;
   int  i, local_n;
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n;
   local_n = n/thread_count;
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   integral = (f(local_a) + f(local_b))/2.0;
   for (i = 1; i <= local_n-1; i++) {
     x = local_a + i*h;
     integral += f(x);
   }
   integral = integral*h;

#  ifdef DEBUG
   printf("Thread %d:  integral = %e\n", my_rank, integral);
   fflush(stdout);
#  endif

   return integral;
}  

