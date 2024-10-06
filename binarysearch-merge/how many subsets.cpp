#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 500000
#define myInfinite 2147483647

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

int main (){
    int cantidad_elementos, cantidad_de_consultas, consultas, elemento, index;
    int elementos[MAX + 1];
    long long int resultado;

    scanf("%d %d", &cantidad_elementos, &cantidad_de_consultas);
    
    for (int i = 1; i <= cantidad_elementos; i++)
    {
        scanf("%d", &elementos[i]);
    }

    MergeSort(elementos, 1, cantidad_elementos);

    for(int idQuery = 1; idQuery <= cantidad_de_consultas; idQuery++)
    {
        scanf("%d", &consultas);
        resultado = 0;
        
        for(int j = 1; j < cantidad_elementos; j++)
        {
            elemento = consultas - elementos[j];
            if(elemento > elementos[j])
            {
                index = binarySearch(elementos, j + 1, cantidad_elementos, elemento);
                if (index < 0)
                index= (-1) * index - 2;
                resultado += index - j;
            }
            else
                break;   
        }
        printf("%lld\n", resultado);
    }
    return 0;
}