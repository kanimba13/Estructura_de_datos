#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define myInfinite 2147483647
#define MAX 100005

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

int main(){

    int cantidad_galletas, cantidad_consultas, consulta, galletas[MAX + 1], resultado, max_galleta;
    
    while(scanf("%d", &cantidad_galletas) != EOF){

        for(int i = 1; i <= cantidad_galletas; i++){
            scanf("%d", &galletas[i]);
        }

        MergeSort(galletas, 1, cantidad_galletas);

        scanf("%d", &cantidad_consultas);

        for(int i = 1; i <= cantidad_consultas; i++){
            scanf("%d", &consulta);
            max_galleta = BinarySearchLastOccurrence(galletas, 1, cantidad_galletas, consulta);

            if(max_galleta < 0)
                max_galleta = (-1) * max_galleta - 2;

            resultado = max_galleta;
            printf("%d ", resultado);
        }
        printf("\n");
    }
    return 0;
}