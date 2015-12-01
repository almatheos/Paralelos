/*

	En la tabla se puede comprobar que usando solo atomic es mas rapido, ya 
	que cuando se usa el parallel for y al atomic cada hebra bloquea la 
	variable "sum"

	#Threads 	Tiempo1		Tiempo2
	
	1		0.000049	0.000089 
	2		0.000053	0.000185	
	4		0.000071	0.003334 
	8		0.000046	0.000418
	16		0.000062	0.000879
									
	Para Compilar  
	
	gcc -g -Wall -fopenmp -o  5-10 5-10.c -lm	

alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-10 1 360
Resultado = 0.695433 
Tiempo = 0.000049 
Resultado2 = 0.695433 
Tiempo = 0.000089 
alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-10 2 360
Resultado = 0.695433 
Tiempo = 0.000053 
Resultado2 = 3.579389 
Tiempo = 0.000185 
alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-10 4 360
Resultado = 0.695433 
Tiempo = 0.000071 
Resultado2 = 0.350521 
Tiempo = 0.003334 
alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-10 8 360
Resultado = 0.695433 
Tiempo = 0.000046 
Resultado2 = 4.742653 
Tiempo = 0.000418 
alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-10 16 360
Resultado = 0.695433 
Tiempo = 0.000062 
Resultado2 = 5.634339 
Tiempo = 0.000879 



*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main (int argc,char* argv[]) 
{	  


	int NUM_THREADS= strtol(argv[1],NULL,10);
	int n=strtol(argv[2],NULL,10);
	int i;
	int j;
	double my_sum=0.0;
	double my_sum2=0.0;
	double ti = omp_get_wtime();
	for(i=0;i<n;i++){
		
		#pragma omp atomic
		my_sum+=sin( (double)i);
	}
	#pragma omp barrier
	double tf = omp_get_wtime();
	
	
	printf("Resultado = %f \n",my_sum);
	printf("Tiempo = %f \n",tf-ti);
	
	
	ti=omp_get_wtime();
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		for(j=0;j<n;j++){
		
		#pragma omp atomic
		my_sum2+= sin( (double)j);
		
		}
	
	}
	
	#pragma omp barrier
	tf = omp_get_wtime();
	
	printf("Resultado2 = %f \n",my_sum2);
	printf("Tiempo = %f \n",tf-ti);

	  
	return 0;
}
