/*

	posicion	0	1	2	3	4	5 
	valor		0	1	3	6	10	15	
	el valor de f(i)=sumatoria de 0 a i			
	=>a[i]=i*(i+1)/2

	Para Compilar 
		gcc -g -Wall -fopenmp -o 5-8 5-8.c
		
	Para Correr
		./5-8 5(Threads) 20(tamano)

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (int argc,char* argv[]) 
{	  


	int i=0;


	int NUM_THREADS= strtol(argv[1],NULL,10);
	int n= strtol(argv[2],NULL,10);
	int a[n];
	a[0]=0;
	
	
#pragma omp parallel for num_threads(NUM_THREADS) 	
	for (i=0;i< n; i++){ 
		a[i]=i*(i+1)/2;		
	  } 

	for (i=0;i< n; i++){ 
		printf(" %d ,",a[i]);
		}


	printf("\n ");
	return 0;
}
