/*

	Para Compilar 
gcc -g -Wall -fopenmp -o 5-6 5-6.c
	Para Correr
	./5-6 5(Threads) 20(Iteraciones)




*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (int argc,char* argv[]) 
{	  


	int i=0;

	int k=0;
	int NUM_THREADS= strtol(argv[1],NULL,10);
	int iteraciones= strtol(argv[2],NULL,10);


	int b[NUM_THREADS+1][iteraciones/NUM_THREADS+1];
	for(i=0;i<NUM_THREADS+1;i++)
		for( k=0;k<(iteraciones/NUM_THREADS +1);k++)
			b[i][k]=-1;
	
	
#pragma omp parallel for num_threads(NUM_THREADS) 	
	for (i=0;i< iteraciones; i++){ 
	

		b[omp_get_thread_num()][i%NUM_THREADS ]=i;
	  } 

	for(i=0;i<NUM_THREADS;i++){
	
		printf("\nrank %d = ", i );

		for( k=0;k<(iteraciones/NUM_THREADS + 1);k++)
			if(b[i][k]>-1)// Para evitar que imprima basura del vector
			printf(" %d", b[i][k]);

	}

	printf("\n ");
	return 0;
}
