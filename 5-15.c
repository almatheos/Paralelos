/*

	La primera opcion es mas rapida, ya que completar el vecor es mas facil
	que tener que copiar de un temporal al vector resultante

	alonso@lasNoches:~/Documents/Paralelos/OpenMP$ ./5-15 8 500	
	tamano original = 500, nuevo tamaño con Padding = 504 
	Tiempo = 0.001027 
	Tiempo2 = 0.002026 


	Para compilar:
		 gcc -g -Wall -fopenmp -o  5-15 5-15.c 



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

	int n2=(8-n%8)+n;
	/*
		nuevo tamaño mas padding tiene que ser multiplo de 8 porque
		una linea de cache soporta 8 doubles.	
	*/
	
	printf("tamano original = %d, nuevo tamaño con Padding = %d \n",n,n2);	
	
	double	M[n2][n2],
		V[n2],
		R[n2],
		R2[n2];
	double r=0.0;	
	
	for(i=0;i<n;i++){
		V[i]=i*1+2;
		R[i]=0.0;
		}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		M[i][j]=i+j;	
		}
	/*
		Padding
	*/	
	for(i=n;i<n2;i++){
		V[i]=0.0;
		R[i]=0.0;
		}
	for(i=n;i<n2;i++){
		for(j=0;j<n;j++)
			M[i][j]=0.0;	
		}
	for(i=0;i<n2;i++){
		for(j=n;j<n2;j++)
			M[i][j]=0.0;	
		}
			
	/*
		Multiplicacion Opcion 1(Padding) 
	*/		
	
	double ti = omp_get_wtime();
	#pragma omp parallel for num_threads(NUM_THREADS) shared (R,M,V) private(i,j,r) 		
	for(i=0;i<n2;i++){
		r=0.0;
		for(j=0;j<n;j++){
			r+=M[i][j]*V[j];
		}
		R[i]=r;
	}
	
	#pragma omp barrier
	double tf = omp_get_wtime();
	printf("Tiempo = %f \n",tf-ti);

	/*
		Opcion 2 Cada Thread tiene un vector temporal para guardar sus valores
		parciales, al terminar el calculo recien se copia de R2(temporal) al
		vector Resultante (R2)
	*/
	
	double	M2[n2][n2],
		V2[n2],
		R_2[n2];
		
	
	for(i=0;i<n;i++){
		V2[i]=i*1+2;
		R_2[i]=0.0;
		}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		M2[i][j]=i+j;	
		}
	

	int k;
	int id;
	
	ti = omp_get_wtime();
	#pragma omp parallel for num_threads(NUM_THREADS) shared(R,M,V) private(R2,i,j,k,r)		
	for(k=0;k<NUM_THREADS;k++){
	  	
	  	id = omp_get_thread_num();
		for(i=id*(n2/NUM_THREADS) ; i< (id+1)*(n2/NUM_THREADS) ;i++){
			r=0.0;
			for(j=0;j<n;j++){
				r+=M2[i][j]*V2[j];
			}
			R2[i]=r;
		}
		for(i=id*(n2/NUM_THREADS) ; i< (id+1)*(n2/NUM_THREADS) ;i++){
		
			R_2[i]=R2[i];
		}
	}
	
	#pragma omp barrier
	tf = omp_get_wtime();
	printf("Tiempo2 = %f \n",tf-ti);

	  
	return 0;
}
