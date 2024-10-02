#include <stdio.h>
#include <stdlib.h>
 
#define myInfinite 2147483647
 
typedef struct
{
    int query;
    int count;
} SubsetInfo;
 
void myMergeSubset(SubsetInfo A[], int p, int q, int r)
{
    int i, j, k, n1 = q - p + 1, n2 = r - q;
    SubsetInfo L[n1 + 2], R[n2 + 2];
    SubsetInfo placeholder = {myInfinite, 0};
 
    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];
 
    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];
 
    L[n1 + 1] = placeholder;
    R[n2 + 1] = placeholder;
 
    i = 1;
    j = 1;
 
    for (k = p; k <= r; k++)
    {
        if (L[i].count > R[j].count || (L[i].count == R[j].count && L[i].query <= R[j].query))
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}
 
void mergeSortSubset(SubsetInfo A[], int p, int r)
{
    int q;
 
    if (p < r)
    {
        q = (p + r) / 2;
        mergeSortSubset(A, p, q);
        mergeSortSubset(A, q + 1, r);
        myMergeSubset(A, p, q, r);
    }
}
 
void myMerge(int A[], int p, int q, int r)
{
    int i, j, k, n1 = q - p + 1, n2 = r - q;
    int L[n1 + 2], R[n2 + 2];
 
    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];
 
    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];
 
    L[n1 + 1] = myInfinite;
    R[n2 + 1] = myInfinite;
 
    i = 1;
    j = 1;
 
    for (k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}
 
void mergeSort(int A[], int p, int r)
{
    int q;
 
    if (p < r)
    {
        q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}
 
int binarySearch(int A[], int t, int l, int r)
{
    int m;
 
    while (l <= r)
    {
        m = (l + r) / 2;
 
        if (A[m] == t)
            return m;
        else if (A[m] < t)
            l = m + 1;
        else
            r = m - 1;
    }
 
    return -1 * l - 1;
}
 
int main()
{
    int n, k, s, cursor, i, j, sets_count;
    int *A, *S, max_pos;
    SubsetInfo *results;
 
    scanf("%d", &n);
    scanf("%d", &k);
    A = malloc(sizeof(int) * n);
    S = malloc(sizeof(int) * k);
    for (cursor = 0; cursor < n; cursor++)
        scanf("%d", &A[cursor]);
    for (cursor = 0; cursor < k; cursor++)
        scanf("%d", &S[cursor]);
 
    results = malloc(sizeof(SubsetInfo) * k);
    mergeSort(A, 0, n - 1);
 
    for (cursor = 0; cursor < k; cursor++)
    {
        s = S[cursor];
        sets_count = 0;
        // printf("%d:\n", s);
 
        max_pos = binarySearch(A, s, 0, n - 1);
        if (max_pos < 0)
            max_pos = -1 * max_pos - 2;
 
        i = 0;
        j = max_pos;
 
        while (i < j)
        {
            if (A[i] + A[j] == s)
            {
                // printf("%d %d\n", A[i], A[j]);
                sets_count++;
                i++;
                j--;
            }
            else if (A[i] + A[j] < s)
                i++;
            else
                j--;
        }
        results[cursor].query = s;
        results[cursor].count = sets_count;
    }
 
    mergeSortSubset(results, 0, k - 1);
    for (cursor = 0; cursor < k; cursor++)
    {
        printf("%d %d\n", results[cursor].query, results[cursor].count);
    }
    free(A);
    free(S);
    free(results);
}