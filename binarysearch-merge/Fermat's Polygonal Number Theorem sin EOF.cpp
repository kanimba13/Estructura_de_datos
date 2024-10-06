#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_N 100000

int binarySearch(int A[], int i, int j, int k)
{
    int m, result = -1;
    while(i <= j)
    {
        m = (i + j)>>1; /* m = (i + j)/2; */
        if(A[m] == k)
        {
            result = m;
            break;
        }
        else
        {
            if(k > A[m])
                i = m + 1;
            else
                j = m - 1;
        }
    }
    if(result == -1)
        result = (-1) * i - 1;

    return result;
}

int main() {
    int numero_consultas;
    scanf("%d", &numero_consultas);

    // Generar numeros triangulares
    int TRIANGULAR[MAX_N + 1];
    int cantidad_triangulares = 0;

    for (int i = 1; ; i++) {
        int triangular = (i * (i + 1)) / 2;
        if (triangular > MAX_N) {
            break;
        }
        TRIANGULAR[cantidad_triangulares++] = triangular; // Almacena los numeros triangulares
    }

    // Crear un arreglo para contar formas de representar cada numero
    int formas[MAX_N + 1] = {0};

    // Contar las formas usando uno, dos y tres numeros triangulares
    // Caso 1: Un numero triangular
    for (int i = 0; i < cantidad_triangulares; i++) {
        if (TRIANGULAR[i] <= MAX_N) {
            formas[TRIANGULAR[i]]++;
        }
    }

    // Caso 2: Suma de dos numeros triangulares
    for (int i = 0; i < cantidad_triangulares; i++) {
        for (int j = i; j < cantidad_triangulares; j++) {
            int suma_dos = TRIANGULAR[i] + TRIANGULAR[j];
            if (suma_dos <= MAX_N) {
                formas[suma_dos]++;
            }
        }
    }

    // Caso 3: Suma de tres numeros triangulares
    for (int i = 0; i < cantidad_triangulares; i++) {
        for (int j = i; j < cantidad_triangulares; j++) {
            for (int k = j; k < cantidad_triangulares; k++) {
                int suma_tres = TRIANGULAR[i] + TRIANGULAR[j] + TRIANGULAR[k];
                if (suma_tres <= MAX_N) {
                    formas[suma_tres]++;
                }
            }
        }
    }

    // Procesar las consultas
    for (int index = 0; index < numero_consultas; index++) {
        int numeros;
        scanf("%d", &numeros);
        printf("%d\n", formas[numeros]);
    }

    return 0;
}