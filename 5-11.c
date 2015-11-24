#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


typedef struct{
	float * x;
} point;

int main (int argc,char* argv[])
{
	int i=0;
	int j=0;
	int k=0;
	int NUM_THREADS= strtol(argv[1],NULL,10);
	int tam= strtol(argv[2],NULL,10);
	point matriz[tam];
	point result[tam];
	float Factor[tam];
        for(i=0;i<tam;i++){
	
		float tmp[tam];		
		Factor[i]=i;
		for(j=0;j<tam;j++){
			
			tmp[j]= rand()%50;
			printf("%f ", tmp[j]);		
		
		}
		point A={tmp};
		matriz[i]=A;		
	}
	printf("Imprimo mi Matriz \n");
	for(i=0;i<tam;i++){
	
		printf("\n");
		for(j=0;j<tam;j++){
			
			printf("%f\t", (matriz[i].x )[j]);		
		}
	}
	printf("\nImprimo mi Vector \n");

	for(j=0;j<tam;j++){
			
			printf("%f\t", Factor[i]);		
	}
		printf("\n");
	
			
	printf("%d", NUM_THREADS);
	
	#pragma omp parallel for num_threads(NUM_THREADS)
	
	for(i=0;i<tam;i++){
	
		float tmp[tam];	

		for(j=0;j<tam;j++){

			float parcial=0.0;			
			for(k=0;k<tmp;k++){
				parcial+=Factor[k]*( matriz[j].x[k] );			
			}
			float tmp[j]=parcial;		
		
		}
		point A={tmp};
		result[i]=A;		
	}
	printf("Imprimo mi nueva Matriz \n");
	for(i=0;i<tam;i++){
	
		printf("\n");
		for(j=0;j<tam;j++){
			
			printf("%f\t", (result[i].x )[j]);		
		}
	}


	return 0;
}
