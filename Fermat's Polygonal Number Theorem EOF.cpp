#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 10000000
#define MAX_TRIANGULARS 4472
#define MAX_SUMS (MAX_TRIANGULARS * MAX_TRIANGULARS)

int triangulars[MAX_TRIANGULARS];
int triangular_sums[MAX_SUMS];
int sums_count = 0;


void generate_triangulars() {
    for (int k = 1; k < MAX_TRIANGULARS; k++) {
        triangulars[k] = k * (k + 1) / 2;
    }
}


void generate_triangular_sums() {
    for (int i = 1; i < MAX_TRIANGULARS; i++) {
        for (int j = i; j < MAX_TRIANGULARS; j++) {
            int sum = triangulars[i] + triangulars[j];
            if (sum > MAX_N) break;
            triangular_sums[sums_count++] = sum;
        }
    }
}


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int is_triangular(int n) {
    for (int i = 1; i < MAX_TRIANGULARS; i++) {
        if (triangulars[i] == n) return 1;
        if (triangulars[i] > n) break;
    }
    return 0;
}


int binary_search(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return 1;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

int main() {
    generate_triangulars();
    generate_triangular_sums();
    
    
    qsort(triangular_sums, sums_count, sizeof(int), compare);
    
    int n;
    while (scanf("%d", &n) != EOF) {
        if (is_triangular(n)) {
            printf("1\n");
        } else if (binary_search(triangular_sums, sums_count, n)) {
            printf("2\n");
        } else {
            printf("3\n");
        }
    }
    
    return 0;
}