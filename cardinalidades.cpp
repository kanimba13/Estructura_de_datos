#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005
#define myInfinite 2147483647

// Funcion de Binary Search
int binarySearch(int A[], int i, int j, int k) {
    int m, result = -1;
    while (i <= j) {
        m = (i + j) / 2; // Equivalente a (i + j) >> 1
        if (A[m] == k) {
            result = m;
            break;
        } else if (k > A[m]) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }
    return result;
}

// Funcion para fusionar (Merge) dos partes de un array
void myMerge(int A[], int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q;
    int L[n1 + 1], R[n2 + 1];
    
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];
    
    L[n1] = myInfinite;
    R[n2] = myInfinite;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

// Funcion de MergeSort
void mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

// Funcion principal
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int A[MAX], B[MAX];
    for (int i = 0; i < m; i++)
        scanf("%d", &A[i]);
    
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);

    // Ordenamos ambos conjuntos
    mergeSort(A, 0, m - 1);
    mergeSort(B, 0, n - 1);
    
    // Usamos dos punteros para calcular los conjuntos solicitados
    int i = 0, j = 0;
    int A_B = 0, B_A = 0, A_inter_B = 0, A_union_B = 0;
    
    while (i < m || j < n) {
        if (i < m && (j >= n || A[i] < B[j])) {
            // A[i] esta en A pero no en B (A - B)
            A_B++;
            A_union_B++;
            i++;
        } else if (j < n && (i >= m || A[i] > B[j])) {
            // B[j] esta en B pero no en A (B - A)
            B_A++;
            A_union_B++;
            j++;
        } else { // A[i] == B[j], entonces esta en la interseccion (A ∩ B)
            A_inter_B++;
            A_union_B++;
            i++;
            j++;
        }
    }
    
    // Imprimir las cardinalidades de los conjuntos
    printf("%d %d %d %d\n", A_B, A_inter_B, B_A, A_union_B);
    
    return 0;
}
