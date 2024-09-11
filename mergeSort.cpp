#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define myInfinite 2147483647
#define MAXT 1000

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



int main() {
    int A[MAXT + 1], n, i, flag;
    while(scanf("%d", &n) != EOF){
        for (i = 1; i <= n; i++){
            scanf("%d", &A[i]);
        }
        flag = 0;
        printf("\n");
        for (i = 1; i <= n; i++){
            if(flag == 1){
                printf(" ");
            }
            printf("%d", A[i]);
            flag = 1;
        }
        printf("\n\n");
        MergeSort(A, 1, n);
        flag = 0;
        printf("\n");
        for(i = 1; i <= n; i++){
            if(flag == 1){
                printf(" ");
            }
            printf("%d", A[i]);
            flag = 1;
        }
    }
    return 0;
}