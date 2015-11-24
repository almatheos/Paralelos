#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 


double step; 

int main (int argc,char* argv[]) 
{	  


	int i=0;
        int NUM_THREADS= strtol(argv[1],NULL,10);

	double sum=0.0;		  
//#pragma omp parallel for reduction(+:sum) private(x) 
#pragma omp parallel for num_threads(NUM_THREADS) reduction (+:sum) private(x)
	for (i=0;i<= 2; i++){ 
	int x;
	  	printf("%d \n", x);
	  	sum= sum + 1;	
	  } 
	bool flag=1;
	bool result=1;
#pragma omp parallel for num_threads(NUM_THREADS) reduction (&&:result) private(x)
	for (i=0;i<= 2; i++){ 
		int x;
	  	if(x%10 == 1)
	  	flag= flag && 1;	
	  }

	flag=1;
	result=1;
#pragma omp parallel for num_threads(NUM_THREADS) reduction (||:result) private(x)
	for (i=0;i<= 2; i++){ 
		int x;
	  	if(x%10 == 1)
	  	flag= flag || 1;	
	  }
	  
	  
	flag=1;
	result=1;
#pragma omp parallel for num_threads(NUM_THREADS) reduction (&:result) private(x)

	for (i=0;i<= 2; i++){ 
		int x;
	  	flag= flag & 1;	
	  }  
	  
	flag=1;
	result=1;
#pragma omp parallel for num_threads(NUM_THREADS) reduction (|:result) private(x)
	for (i=0;i<= 2; i++){ 
		int x;
	  	flag= flag | 1;	
	  }
	   


	
  
	return 0;
}
