#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 500000
#define myInfinite 2147483647

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