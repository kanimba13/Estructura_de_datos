#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#define myInfinite 2147483647
#define MAX 1000000

int merge(int A[], int p, int q, int r) {
    int i, j, k, n1 = q - p + 1, n2 = r - q;
    int L[n1 + 2], R[n2 + 2];

    for (i = 1; i <= n1; i++) {
        L[i] = A[p + i - 1];
    }
    for (j = 1; j <= n2; j++) {
        R[j] = A[q + j];
    }

    L[n1 + 1] = myInfinite;
    R[n2 + 1] = myInfinite;
    i = 1;
    j = 1;

    for (k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
    return 0;
}

int mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
    return 0;
}

int binarySearch(int A[], int i, int j, int k) {
    int m, result = -1;
    while (i <= j) {
        m = (i + j) >> 1; /* m = (i + j)/2; */
        if (A[m] == k) {
            result = m;
            break;
        } else {
            if (k > A[m])
                i = m + 1;
            else
                j = m - 1;
        }
    }
    if (result == -1)
        result = (-1) * i - 1;

    return result;
}

int BinarySearchFirstOccurrence ( int A[] , int i, int j, int k)
{
    int result , result2 ;
    
    result = binarySearch(A, i, j, k);

    if( result >= 0)
    {
        result2 = binarySearch (A, i, result - 1, k) ;

        while ( result2 >= 0)
        {
            result = result2 ;
            result2 = binarySearch(A, i, result - 1, k) ;
        }

    }

    return result ;
}

int BinarySearchLastOccurrence ( int A[] , int i, int j, int k)
{
    int result , result2 ;
    result = binarySearch (A, i, j, k);
    
    if( result >= 0)
    {
        result2 = binarySearch(A, result + 1 , j, k) ;
        
        while ( result2 >= 0)
        {

        result = result2 ;
        result2 = binarySearch(A, result + 1 , j, k) ;

        }
    }

    return result ;
}


int main() {
    int A[MAX + 1],cantidad_elementos, index, total_operaciones, tipo, a, b, k, resultado_binary_search, numeros_entre_a_y_b;

    scanf("%d %d", &cantidad_elementos, &total_operaciones);

    for(index = 1; index <= cantidad_elementos; index++)
        scanf("%d", &A[index]);

    mergeSort(A, 1, cantidad_elementos);

    while (total_operaciones--) {

        scanf("%d", &tipo);

        if (tipo == 1) {

            scanf("%d", &k);
            resultado_binary_search = binarySearch(A, 1, cantidad_elementos, k);
            if ( resultado_binary_search >= 0)
                continue;

            else{

                if(resultado_binary_search < (-1) * cantidad_elementos){
                    cantidad_elementos++;
                }
                    
                resultado_binary_search = (-1) * resultado_binary_search - 1;
                A[resultado_binary_search] = k;

            }
        }

        else if (tipo == 2) {

            numeros_entre_a_y_b = 0;
            scanf("%d %d", &a, &b);

            // Encontrar el ndice del primer nmero mayor o igual a 'a'
            int posA = BinarySearchFirstOccurrence(A, 1, cantidad_elementos, a);

            if (posA < 0) 
                posA = (-1) * posA - 1; // Ajuste en caso de que no se encuentre exactamente 'a'

            // Encontrar el ndice del ltimo nmero menor o igual a 'b'
            int posB = BinarySearchLastOccurrence(A, 1, cantidad_elementos, b);

            if (posB < 0) 
                posB = (-1) * posB - 2; // Ajuste en caso de que no se encuentre exactamente 'b'

           numeros_entre_a_y_b = posB - posA + 1;//restar 1 para obtener la cantidad de nmeros entre 'a' y 'b'

            printf("%d\n", numeros_entre_a_y_b);
        }
          
    }
    return 0;
}