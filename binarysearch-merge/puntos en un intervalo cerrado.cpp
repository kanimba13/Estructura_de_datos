#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define myInfinite 2147483647
#define MAX 1000000

void myMerge(int A[], int p, int q, int r){
    int i, j, k, n1 = q - p + 1, n2 = r - q;
    int L[n1 +2], R[n2 + 2];

    for(i = 1; i <= n1; i++){
        L[i] = A[p + i - 1];
    }
    for(j = 1; j <= n2; j++){
        R[j] = A[q + j];
    }

    L[n1 + 1] = myInfinite;
    R[n2 + 1] = myInfinite;
    i = 1;
    j = 1;

    for(k = p; k <= r; k++){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }else{
            A[k] = R[j];
            j++;
        }
    }
}

int MergeSort(int A[], int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
    return 0;
}

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

int main(){

    int numero_consultas, A[MAX + 1], result, numero_elementos, index, primera_ocurrencia, ultima_ocurrencia;
    int primer_limite, segundo_limite;

    while (1) {
        scanf("%d %d", &numero_elementos, &numero_consultas);
        if (numero_elementos == 0 && numero_consultas == 0) break;

        for (index = 1; index <= numero_elementos; index++){
            scanf("%d", &A[index]);
        }

        MergeSort(A, 1, numero_elementos);

        for(index = 1; index <= numero_consultas; index ++){
            scanf("%d %d", &primer_limite, &segundo_limite);
            
            primera_ocurrencia = BinarySearchFirstOccurrence(A, 1, numero_elementos, primer_limite);
            if (primera_ocurrencia < 0){
                primera_ocurrencia = -1 * primera_ocurrencia - 1;
            }

            ultima_ocurrencia = BinarySearchLastOccurrence(A, 1, numero_elementos, segundo_limite);
            if(ultima_ocurrencia < 0){
                ultima_ocurrencia = -1 * ultima_ocurrencia - 2;
            }

            result = ultima_ocurrencia - primera_ocurrencia + 1;
            printf("%d\n", result);
        }
    }

    return 0;
}