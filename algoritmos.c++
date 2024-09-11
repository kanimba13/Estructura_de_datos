#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 2147483647

int binarySearch(int A[], int i, int j, int k){
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

int mergesort(int A[], int p, int r){
    if(p<r){
        int q=(p+r)/2;
        mergesort(A,p,q);
        mergesort(A,q+1,r);
        merge(A,p,q,r);
    }
}

int merge(int A[], int p, int q, int r){
/*el algoritmo primero organiza los primeros elementos del vector o estructura por la PROPIEDAD DE ESTABILIDAD*/
        int n1,n2;
        n1=q-p+1;
        n2=r-q;
        int L[n1+1],R[n2+1];
        for(int i=1;i<=n1;i++){
            L[i]=A[p+i-1];
        }
        for(int j=1;j<=n2;j++){
            R[j]=A[q+j];
        }
        L[n1+1]=1000000;
        R[n2+1]=1000000;
        int i=1;
        int j=1;
        for(int k=p;k<=r;k++){
            if(L[i]<=R[j]){
                A[k]=L[i];
                i=i+1;
            }
            else{
                A[k]=R[j];
                j=j+1;
            }
        }

 }