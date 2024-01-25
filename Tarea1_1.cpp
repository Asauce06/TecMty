#include <cstdlib>                                  // Para usar srand() y rand()
#include <ctime>                                    // Para usar time()                         
#include <iostream>                                 // Para usar cout                        
#include <omp.h>                                    // Para usar OpenMP     
#include <windows.h>                                // Para usar GetTickCount()

int main() {                                        // Programa principal
    const int SIZE = 100000;                        // Tamaño de los arreglos
    int arr1[SIZE], arr2[SIZE], sum[SIZE];          // Declarar los arreglos

    srand(static_cast<unsigned>(time(0)));          // Inicializar la semilla de rand()

    // Llenar los arreglos con valores aleatorios
    for(int i = 0; i < SIZE; i++) {                 
        arr1[i] = rand() % 100;                     // Se asigna un valor aleatorio entre 0 y 99
        arr2[i] = rand() % 100;                     // Se asigna un valor aleatorio entre 0 y 99
    }
    
    DWORD dwStart = GetTickCount();                 // Iniciar el cronómetro|

    #pragma omp parallel                            // Iniciar el bloque paralelo
    {
        #pragma omp sections                        // Iniciar el bloque de secciones
        {
            #pragma omp section                     // Iniciar la primera sección
            {
                // Inicializamos el ciclo for para que empiece en 0 hasta la mitad del arreglo.
                for(int i = 0; i < SIZE / 2; i++) {
                    sum[i] = arr1[i] + arr2[i];     // Sumar los elementos del arreglo 1
                }
            }

            #pragma omp section                     // Iniciar la segunda sección
            {
                // Inicializamos el ciclo for para que empiece en la mitad del arreglo hasta el final.
                for(int i = SIZE / 2; i < SIZE; i++) {
                    sum[i] = arr1[i] + arr2[i];     // Sumar los elementos del arreglo 2
                }
            }
        }
    }

    DWORD dwEnd = GetTickCount();                   // Detener el cronómetro

    // Imprimir algunos elementos para verificar
    for(int i = 0; i < 10; i++) {
        // Imprimir los primeros 10 elementos de cada arreglo
        std::cout << "arr1[" << i << "] = " << arr1[i] << ", arr2[" << i << "] = " << arr2[i] << ", sum[" << i << "] = " << sum[i] << std::endl;
    }

    // Imprimir el tiempo de ejecución
    std::cout << "Tiempo de ejecucion: " << (dwEnd - dwStart) << " milisegundos." << std::endl;

    return 0;                                       // Terminar el programa                
}
