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


//Se llaman a las librerias necesarias para el funcionamiento del programa
#include <stdio.h>         
#include <stdlib.h>      
#include <sys/time.h>      
#include <time.h>        
#include <pthread.h>        // Se incluye la biblioteca para la manipulación de hilos
#include "multi_matriz.h"  // Se incluye la interfaz multi_matriz.h

pthread_mutex_t MM_mutex; // Mutex para garantizar la exclusión mutua
double *mA, *mB, *mC;     // Punteros a las matrices de entrada y salida
struct timeval start, stop; // Variables para medir el tiempo

// Función para llenar las matrices con valores aleatorios
void llenar_matriz(int SZ) {
  srand48(time(NULL)); // Inicialización de la semilla para la generación de números aleatorios
  for (int i = 0; i < SZ * SZ; i++) {
    mA[i] = 1.1 * i; // Se asignan valores predeterminados (comentado: debería ser drand48();)
    mB[i] = 2.2 * i; // Se asignan valores predeterminados (comentado: debería ser drand48();)
    mC[i] = 0;       // Se inicializa la matriz de salida con ceros
  }
}

// Función para imprimir una matriz
void print_matrix(int sz, double *matriz) {
  if (sz < 12) { // Si el tamaño de la matriz es menor que 12x12
    for (int i = 0; i < sz * sz; i++) {
      if (i % sz == 0)
        printf("\n"); // Nueva línea para cada fila
      printf(" %.3f ", matriz[i]); // Se imprime cada elemento con 3 decimales de precisión
    }
    printf("\n>-------------------->\n"); // Separador al final de la matriz
  }
}

// Función para iniciar la medición del tiempo
void inicial_tiempo() {
  gettimeofday(&start, NULL); // Se obtiene el tiempo actual
}

// Función para finalizar la medición del tiempo
void final_tiempo() {
  gettimeofday(&stop, NULL); // Se obtiene el tiempo actual nuevamente
  stop.tv_sec -= start.tv_sec; // Se calcula la diferencia en segundos
  printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec)); // Se imprime el tiempo transcurrido en microsegundos
}

// Función para la multiplicación de matrices (Traspuesta)
void *mult_thread_mm_traspuesta(void *variables) {
  struct parametros *data = (struct parametros *)variables; // Se obtienen los datos del hilo

  int idH = data->idH; // ID del hilo
  int nH = data->nH;   // Número total de hilos
  int N = data->N;     // Tamaño de la matriz
  int ini = (N / nH) * idH; // Índice inicial
  int fin = (N / nH) * (idH + 1); // Índice final

  
  // Multiplicación de matrices con acceso por filas
  for (int i = ini; i < fin; i++) { // Se itera sobre las filas asignadas al hilo actual
      for (int j = 0; j < N; j++) { // Se itera sobre cada columna de la matriz resultado
          double *pA, *pB, sumaTemp = 0.0; // Se declaran punteros para las matrices y una variable temporal para la suma
          pA = mA + (i * N); // Se inicializa pA para que apunte al inicio de la fila i de mA
          pB = mB + (j * N); // Se inicializa pB para que apunte al inicio de la columna j de mB
          for (int k = 0; k < N; k++, pA++, pB++) { // Se realiza el producto punto de la fila i de mA y la columna j de mB
              sumaTemp += (*pA * *pB); // Se acumula el resultado del producto de los elementos correspondientes
          }
          mC[i * N + j] = sumaTemp; // Se asigna el valor calculado a la posición correspondiente en mC
      }
  }

  pthread_mutex_lock(&MM_mutex); // Bloquea el mutex para la exclusión mutua
  pthread_mutex_unlock(&MM_mutex); // Desbloquea el mutex
  pthread_exit(NULL); // Finaliza el hilo
}

// Función para la multiplicación de matrices (Clasico)
void *mult_thread_mm_clasico(void *variables) {
  struct parametros *data = (struct parametros *)variables; // Se obtienen los datos del hilo

  int idH = data->idH; // ID del hilo
  int nH = data->nH;   // Número total de hilos
  int N = data->N;     // Tamaño de la matriz
  int ini = (N / nH) * idH; // Índice inicial
  int fin = (N / nH) * (idH + 1); // Índice final
   // Se realiza la multiplicación de dos matrices y almacena el resultado en una tercera matriz. Se utilizan tres bucles anidados para recorrer las filas y columnas de las matrices,
  

  for (int i = ini; i < fin; i++) { 
      // Se itera sobre las filas asignadas al hilo actual
      for (int j = 0; j < N; j++) {
          // Se itera sobre cada columna de la matriz resultado
          double *pA, *pB, sumaTemp = 0.0;
          pA = mA + (i * N); // Se inicializa pA para que apunte al inicio de la fila i de mA
          pB = mB + j;       // Se inicializa pB para que apunte al inicio de la columna j de mB
          // Se realiza el producto punto de la fila i de mA y la columna j de mB
          for (int k = 0; k < N; k++, pA++, pB += N) {
              // Se multiplica y suma el producto al acumulador sumaTemp
              sumaTemp += (*pA * *pB);
          }
          mC[i * N + j] = sumaTemp; // Se asigna el resultado a la posición correspondiente en mC
      }
  }

  pthread_mutex_lock(&MM_mutex); // Bloquea el mutex para la exclusión mutua
  pthread_mutex_unlock(&MM_mutex); // Desbloquea el mutex
  pthread_exit(NULL); // Finaliza el hilo
}

// Función para la multiplicación de matrices (Fuente de Evaluacion)
void *mult_thread_fuente_evaluacion(void *variables) {
  struct parametros *data = (struct parametros *)variables; // Se obtienen los datos del hilo

  int idH = data->idH; // ID del hilo
  int nH = data->nH;   // Número total de hilos
  int N = data->N;     // Tamaño de la matriz
  int ini = (N / nH) * idH; // Índice inicial
  int fin = (N / nH) * (idH + 1); // Índice final

  // Se realiza la multiplicación de dos matrices y almacena el resultado en una tercera matriz. Se utilizan tres bucles anidados para recorrer las filas y columnas de las matrices,
 
  for (int i = ini; i < fin; i++) { 
      // Se itera sobre las filas asignadas al hilo actual
      for (int j = 0; j < N; j++) {
          // Se itera sobre cada columna de la matriz resultado
          double *pA, *pB, sumaTemp = 0.0;
          pA = mA + (i * N); // Se inicializa pA para que apunte al inicio de la fila i de mA
          pB = mB + j;       // Se inicializa pB para que apunte al inicio de la columna j de mB
          // Se realiza el producto punto de la fila i de mA y la columna j de mB
          for (int k = 0; k < N; k++, pA++, pB += N) {
              // Se multiplica y suma el producto al acumulador sumaTemp
              sumaTemp += (*pA * *pB);
          }
          mC[i * N + j] = sumaTemp; // Se asigna el resultado a la posición correspondiente en mC
      }
  }

  
  pthread_mutex_lock(&MM_mutex); // Bloquea el mutex para la exclusión mutua
  pthread_mutex_unlock(&MM_mutex); // Desbloquea el mutex
  pthread_exit(NULL); // Finaliza el hilo
}
