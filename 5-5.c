/*
	Para la operacion suma el vector a no necesita hacer redondeo se puede trabajar con el punto flotante 
normal, por eso el resultado en ambos casos es

1010.0	 
 
Para Compilar

  gcc -g -Wall -fopenmp -o 5.5 5-5.c

Para Correr

  ./5.5 2	

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main (int argc,char* argv[]) 
{	  


	int i=0;
	int NUM_THREADS= strtol(argv[1],NULL,10);
	float sum=0.0;		  
	float a[]={4.0, 3.0, 3.0, 1000.0};

	printf("Punto A : \n");

	for (i=0;i< 4; i++){ 
	  	sum+=a[i];	
	  } 
	printf("sum = %4.1f\n",sum);
	sum=0.0;

	printf("Punto B : \n");

#pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum) 	
	for (i=0;i< 4; i++){ 
	  	sum+=a[i];	
	  } 
	printf("sum = %4.1f\n",sum);


	  
	return 0;
}
