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
Fichero: Interfaz de multiplicación de matrices NxN por hilos.
*************************************/

#ifndef MULTI__MATRIZ_H
#define MULTI__MATRIZ_H


//Se llaman a las librerias necesarias para el funcionamiento del programa 
#include <sys/time.h>      
#include <time.h>        
#include <pthread.h>        // Se incluye la biblioteca para la manipulación de hilos

// Se decralan las variablea externas como los mutex, las matrices y las estructuras de tiempo
extern pthread_mutex_t MM_mutex;
extern double *mA, *mB, *mC;
extern struct timeval start, stop;

// Se define una estructura que contiene los parámetros para la multiplicación de matrices.
struct parametros {
    int nH;   //Numero de hilos
    int idH;  // ID del hilo
    int N;    // tamaño de la matriz cuadrada
};

// Función para llenar las matrices con valores aleatorios
void llenar_matriz(int SZ);

// Función para imprimir una matriz
void print_matrix(int sz, double *matriz);

// Función para iniciar la medición del tiempo
void inicial_tiempo();

// Función para finalizar la medición del tiempo
void final_tiempo();

// Función para multiplicación de matrices (Fuente de evaluación)
void *mult_thread_fuente_evaluacion(void *variables);

// Función para multiplicación de matrices (Traspuesta)
void *mult_thread_mm_traspuesta(void *variables);

// Función para multiplicación de matrices (Clasico)
void *mult_thread_mm_clasico(void *variables);

#endif /* MULTI_MATRIZ_H */
