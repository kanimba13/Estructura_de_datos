#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 100000

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
    long long int consulta, numero_elementos, A[MAX + 1];
    long long int index, primer_posicion, ultima_posicion, suma_acumulada;
    
    // Leer numero de elementos y la suma objetivo
    while (scanf("%lld %lld", &numero_elementos, &consulta) != EOF) {
        // Leer los elementos del arreglo
        for (index = 1; index <= numero_elementos; index++)
            scanf("%lld", &A[index]);

        // Variables para mantener el resultado
        int inicio = 1, fin = 1;
        suma_acumulada = 0;
        int encontrado = 0;

        // Implementar la tecnica de dos punteros con busqueda binaria
        while (fin <= numero_elementos) {
            suma_acumulada += A[fin]; // Aumentamos el rango con el elemento en 'fin'

            // Reducir el rango si la suma es mayor que la buscada
            while (suma_acumulada > consulta && inicio <= fin) {
                suma_acumulada -= A[inicio];
                inicio++;
            }

            // Verificar si la suma acumulada es igual a la buscada
            if (suma_acumulada == consulta) {
                printf("%d %d\n", inicio, fin); // Imprimir el rango 1-indexado
                encontrado = 1;
                break;
            }
            
            fin++;
        }

        // Si no se encontro un rango, imprimir -1
        if (!encontrado) {
            printf("-1\n");
        }
    }

    return 0;
}