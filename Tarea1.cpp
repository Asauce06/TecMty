#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <windows.h>

int main() {
    const int SIZE = 100000;
    int arr1[SIZE], arr2[SIZE], sum[SIZE];

    srand(static_cast<unsigned>(time(0)));

    for(int i = 0; i < SIZE; i++) {
        arr1[i] = rand() % 100;
        arr2[i] = rand() % 100;
    }

    DWORD dwStart = GetTickCount();  // Iniciar el cronómetro

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for(int i = 0; i < SIZE; i += 2) {
                    sum[i] = arr1[i] + arr2[i];
                }
            }

            #pragma omp section
            {
                for(int i = 1; i < SIZE; i += 2) {
                    sum[i] = arr1[i] + arr2[i];
                }
            }
        }
    }

    DWORD dwEnd = GetTickCount();  // Detener el cronómetro

    // Imprimir los primeros 10 elementos de cada arreglo
    for(int i = 0; i < 10; i++) {
        std::cout << "arr1[" << i << "] = " << arr1[i] << ", arr2[" << i << "] = " << arr2[i] << ", sum[" << i << "] = " << sum[i] << std::endl;
    }

    std::cout << "Tiempo de ejecucion: " << (dwEnd - dwStart) << " milisegundos." << std::endl;

    return 0;
}
