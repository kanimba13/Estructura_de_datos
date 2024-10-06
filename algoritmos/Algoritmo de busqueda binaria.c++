#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/****************************************************************************************/
/* El valor devuelto por la funcion es un entero correspondiente al indice del elemento */
/* que coincide con el valor buscado. Si el valor buscado no se encuentra, entonces el  */
/* valor devuelto es: - (punto de insercion) - 1. El valor del punto de insercion es el */
/* indice del elemento del arreglo donde deberia encontrarse el valor buscado.          */
/* La expresion: "- (punto de insercion) - 1" garantiza que el indice devuelto sera     */
/* mayor o igual que cero solo si el valor buscado es encontrado.                       */
/****************************************************************************************/

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

int main()
{
    int A[100], index, n, queries, idQuery, k, position;

    scanf("%d", &n);
    for(index = 1; index <= n; index++)
        scanf("%d", &A[index]);

    scanf("%d", &queries);
    for(idQuery = 1; idQuery <= queries; idQuery++)
    {
        scanf("%d", &k);
        position = binarySearch(A, 1, n, k);
        if(position >= 0)
            printf("The element %d is in the array, position: %d\n", k, position);
        else
            printf("The element %d is not in the array, insertion point: %d\n",
                   k, -1 * position - 1);
    }

    return 0;
}
