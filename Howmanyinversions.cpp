#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define myInfinite 2147483647
#define MAXT 1000

long long int inv = 0;

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
            inv = inv + n1 - i + 1;
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
    int A[MAXT + 1], n, i, totalCases, idCase;
    scanf("%d", &totalCases);

    for(idCase = 1 ; idCase <= totalCases; idCase++){
        scanf("%d", &n);
        for (i = 1; i <= n; i++){
            scanf("%d", &A[i]);
        }
            inv = 0;
            MergeSort(A, 1, n);
            printf("%lld\n", inv);
    }

    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#define infinito 2147483647
#define maxt 1000000

long long int inv= 0;


void mymerge (int A[], int p, int q, int r){

    int i, j, k, n1= q - p + 1, n2= r - q;
    int L[n1 + 2], R[n2 + 2];

    for(i=1; i<= n1; i++)
        L[i] = A[p + i - 1];

    for(j=1; j<= n2; j++)
        R[j] = A[q + j];

    L[n1 + 1]= infinito;
    R[n2 + 1]= infinito;
    i= 1;
    j= 1;

    for(k= p; k<= r; k++){
        if(L[i] <= R[j]){
            A[k]= L[i];
            i++;
        }
        else{
            A[k]= R[j];
            j++;
            inv= inv + n1 - i + 1;
        }


    }
}

void mergesort(int A[], int p, int r){
int q;
if(p < r){
    q= (p + r)/2;
    mergesort(A, p, q);
    mergesort(A, q + 1, r);
    mymerge(A, p, q, r);
 }
}



int main()
{

   int A[maxt +1], index, n, flag, totalcases, idcase;
   
   scanf("%d", &totalcases);
   for(idcase= 1; idcase<= totalcases; idcase++)
   {
    scanf("%d", &n);

     for(index= 1; index<= n; index++)
        scanf("%d", &A[index]);
         
    inv= 0;
    mergesort(A, 1, n);
    printf("%lld\n", inv);


   }*/