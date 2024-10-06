#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1000000
#define MAX_QUERIES 500000
#define MAX_LEN 11

char words[MAX_WORDS + 1][MAX_LEN]; // Indices iniciados en 1

// Funcion de merge para Merge Sort
void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Arreglos temporales
    char L[n1 + 1][MAX_LEN], R[n2 + 1][MAX_LEN];

    for (int i = 0; i < n1; i++) strcpy(L[i], words[left + i]);
    for (int i = 0; i < n2; i++) strcpy(R[i], words[mid + 1 + i]);

    int i = 0, j = 0, k = left;

    // Unir los dos sub-arreglos
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(words[k], L[i]);
            i++;
        } else {
            strcpy(words[k], R[j]);
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1) {
        strcpy(words[k], L[i]);
        i++;
        k++;
    }
    while (j < n2) {
        strcpy(words[k], R[j]);
        j++;
        k++;
    }
}

// Funcion de Merge Sort
void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

// Unica funcion de busqueda binaria para encontrar los limites
int binarySearch(int n, const char target[MAX_LEN], int findLower) {
    int low = 1, high = n, result = n + 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if ((findLower && strcmp(words[mid], target) >= 0) || (!findLower && strcmp(words[mid], target) > 0)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    // Leer palabras del diccionario, indices desde 1
    for (int i = 1; i <= n; i++) {
        scanf("%s", words[i]);
    }

    // Ordenar el diccionario usando Merge Sort
    mergeSort(1, n);

    // Procesar las consultas
    for (int i = 1; i <= q; i++) {
        char w1[MAX_LEN], w2[MAX_LEN];
        scanf("%s %s", w1, w2);

        // Usar busqueda binaria para encontrar el rango
        int lower = binarySearch(n, w1, 1); // Buscar el limite inferior
        int upper = binarySearch(n, w2, 0) - 1; // Buscar el limite superior

        // Calcular cuantas palabras estan en el rango
        int count = upper - lower + 1;
        if (lower > upper) {
            count = 0; // No hay palabras en el rango
        }

        printf("%d\n", count);
    }

    return 0;
}
