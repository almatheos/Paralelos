#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 




double step; 

int main (int argc,char* argv[]) 
{	  
long num_steps = 100000;    


	  int NUM_THREADS= strtol(argv[1],NULL,10);
	  int i;
	  double x, pi, sum = 0.0; 
	//  step = 1.0/(double) num_steps; 
	  omp_set_num_threads(NUM_THREADS); 
	 printf("Step : %f \n" ,step);

//#pragma omp parallel for reduction(+:sum) private(x) 
#pragma omp parallel for num_threads(NUM_THREADS) reduction (+:sum) private(x)
	

	  for (i=0;i<= num_steps; i++){ 
	  	if(i%2==0)
	  		x=1.0;
	  	else
	  		x=-1.0;
	  	sum= sum + x/(2*i+1);	
/*
		  x = (i-0.5)*step; 
		  sum = sum + 4.0/(1.0+x*x); 
		  printf("i: %d  , x :%f  ,sum : %f \n" ,i,x,sum);
*/
	  } 
	  pi = 4 * sum; 


	 printf("Pi es : %f \n" ,pi);
	return 0;
}
