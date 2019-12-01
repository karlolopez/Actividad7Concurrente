/******************************************************************************
Compilado en línea:

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.


- Karlo Alejandro López Mayén
- Programación Concurrente - UVM online



Multiplicadora de matrices concurrente

El siguiente programa multiplica 2 matrices (de diferente orden, siempre y cuando 
el número de columnas de la primera matriz coincida con el número de filas de la
segunda).

Las matrices estan representadas por las variables globales A y B, C es el resultado.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define K 2
#define N 3
#define NUM_HILOS M * N

/* Variables que comparten los hilos ;) */
int A[M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B[K][N] = {{8, 7, 6}, {5, 4, 3}};
int C[M][N];

/* Estructura para pasar datos al hilo */
struct v
{
	int i; /* fila */
	int j; /* columna */
};

void *elHilo(void *ptr); /* el hilo */

int main(int argc, char **argv)
{
	int i, j;
	int contador_hilos = 0;
	
	pthread_t workers[NUM_HILOS];
	
	/*HAbrá que crear M * N trabajadores de hilos */
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			/* Creamos el hilo y pasamos su información como parámetro */
			pthread_create(&workers[contador_hilos], NULL, elHilo, data);
			pthread_join(workers[contador_hilos], NULL);
			contador_hilos++;
		}
	}
	
	/* Esperamos a que los hilos terminen */
	for (i = 0; i < NUM_HILOS; i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
	for(i = 0; i < M; i++)
	{ 
		for(j = 0; j < N; j++)
		{ 
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void *elHilo(void *ptr)
{	
	/* Castear al struct v */
	struct v *data = ptr;
	int i, sum = 0;
	
	for(i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	C[data->i][data->j] = sum;
	pthread_exit(0);
}
