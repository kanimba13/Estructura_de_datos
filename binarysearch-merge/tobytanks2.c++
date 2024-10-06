#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int binarySearch(int A[], int i, int j, int k)
{
    int m, result = -1;
    while(i <= j)
    {
        m = (i + j)/2;
        if(k == A[m])
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

int main() {
    int n, q, k;
    while (scanf("%d %d", &n, &q) != EOF){
   
        int A[n + 1];

        A[0] = 0;
        scanf("%d", &A[1]);
        A[1] = 1;

        for (int i = 2; i <= n; i++) {
            scanf("%d", &A[i]);
            A[i] = A[i - 1] + A[i];
        }

        while (q--) {

            scanf("%d", &k);

            int result = binarySearch(A, 1, n, k);
            if (result < 0)
                printf("%d ", (-1) * result - 2);
            
            else
                printf("%d ", result);
        }
        printf("\n");
    }
   
    return 0;
}

