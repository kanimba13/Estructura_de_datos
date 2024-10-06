#include <stdio.h>
#include <stdlib.h>


int binarySearch(int A[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == key) {
            return mid;
        } else if (A[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
       
        int A[n], cumulativeSum[n + 1];
        cumulativeSum[0] = 0; 

     
        for (int i = 1; i <= n; i++) {
            scanf("%d", &A[i - 1]);
            cumulativeSum[i] = cumulativeSum[i - 1] + A[i - 1];
        }

        int totalSum = cumulativeSum[n];  

     
        if (totalSum % 3 != 0) {
            printf("0\n");
            continue;
        }

        int lado = totalSum / 3;  
        int contador = 0;

    
        for (int i = 1; i <= n; i++) {
            int firstTarget = cumulativeSum[i] + lado;
            int secondTarget = cumulativeSum[i] + 2 * lado;

  
            int firstIndex = binarySearch(cumulativeSum, i + 1, n, firstTarget);
            if (firstIndex != -1) {
        
                int secondIndex = binarySearch(cumulativeSum, firstIndex + 1, n, secondTarget);
                if (secondIndex != -1) {
                    contador++;
                }
            }
        }
        
  
        printf("%d\n", contador);
    }

    return 0;
}