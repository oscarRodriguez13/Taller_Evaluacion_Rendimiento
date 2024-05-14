/***********************************
Autores:
- Leonardo Velázquez
- Oscar Rodriguez
- Nicolas Sanchez
Fecha: 7 de mayo de 2024
Materia: Sistemas Operativos
Pontificia Universidad Javeriana
Tema: Taller rendimiento
Objetivo: Evaluar el tiempo de ejecución del
algoritmo clásico de multiplicación de matrices.
*************************************/

// Se llaman a las librerias necesarias para el funcionamiento del programa
#include "multi_matriz.h" // Se incluye la interfaz multi_matriz.h
#include <pthread.h> // Se incluye la biblioteca para la manipulación de hilos
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define DATA_SIZE (1024 * 1024 * 64 * 3)
// Se define el tamaño de los datos como una constante.
double MEM_CHUNK[DATA_SIZE]; // Se declara un arreglo de tipo double llamado
														 // MEM_CHUNK con un tamaño de DATA_SIZE.

int main(int argc, char *argv[]) {
	// Se comprueba si se proporcionan suficientes argumentos de línea de comandos
	if (argc < 3) {
		printf("Uso: %s tamaño_matriz num_hilos\n", argv[0]);
		return -1;
	}

	// Se asignan el tamaño de la matriz y el número de hilos, con los valores de
	// los argumentos
	int SZ = atoi(argv[1]);
	int n_threads = atoi(argv[2]);

	// Se crea un arreglo que contenga los identificadores de los hilos
	pthread_t p[n_threads];
	// Se crea una variable para los atributos de hilo
	pthread_attr_t atrMM;

	// Se le asigna memoria a las matrices, con al anterior espacio de memoria
	// reservado
	mA = MEM_CHUNK;
	mB = mA + SZ * SZ;
	mC = mB + SZ * SZ;

	// se llenan las matrices con valores aleatorios
	llenar_matriz(SZ);
	// Se imprimen las matrices con sus valores ya asignados
	print_matrix(SZ, mA);
	print_matrix(SZ, mB);

	// Se inicializa el tiempo de ejecución
	inicial_tiempo();
	// Se inicializa el mutex para la exclusión mutua
	pthread_mutex_init(&MM_mutex, NULL);
	// Se inicializan los atributos del hilo
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

	// Se crean los hilos para la multiplicación de matrices
	for (int j = 0; j < n_threads; j++) {
		// Se asigna memoria a estructura que contiene los datos del hilo
		struct parametros *datos =
				(struct parametros *)malloc(sizeof(struct parametros));
		datos->idH = j;
		datos->nH = n_threads;
		datos->N = SZ;
		pthread_create(&p[j], &atrMM, mult_thread_mm_clasico, (void *)datos);
	}

	// Se espera a que todos los hilos terminen
	for (int j = 0; j < n_threads; j++)
		pthread_join(p[j], NULL);

	// Se finaliza el tiempo de ejecución
	final_tiempo();

	// Se imprime la matriz con el resultado de la multiplicacion
	print_matrix(SZ, mC);

	// Se limpian los atributos del hilo y se destruye el mutex
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit(NULL);
}
