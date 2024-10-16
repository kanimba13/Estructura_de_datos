#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
 
#define nInf -2147483646
#define pInf 2147483647
#define MAXT 100000
 
int parent(int i)
{
    return i / 2;
}
 
int left(int i)
{
    return 2 * i;
}
 
int right(int i)
{
    return 2 * i + 1;
}
 
void MaxHeapify(int Q[], int i, int heapSize)
{
    int l, r, largest, temp;
    l = left(i);
    r = right(i);
 
    if ((l <= heapSize) && (Q[l] > Q[i]))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
 
    if ((r <= heapSize) && (Q[r] > Q[largest]))
    {
        largest = r;
    }
 
    if (largest != i)
    {
        temp = Q[i];
        Q[i] = Q[largest];
        Q[largest] = temp;
        MaxHeapify(Q, largest, heapSize);
    }
}
 
void MinHeapify(int Q[], int i, int heapSize)
{
    int l, r, least, temp;
    l = left(i);
    r = right(i);
 
    if ((l <= heapSize) && (Q[l] < Q[i]))
    {
        least = l;
    }
    else
    {
        least = i;
    }
 
    if ((r <= heapSize) && (Q[r] < Q[least]))
    {
        least = r;
    }
 
    if (least != i)
    {
        temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;
        MinHeapify(Q, least, heapSize);
    }
}
 
void MaxPQ_Insert(int Q[], int key, int *heapSize)
{
    (*heapSize)++;
    Q[*heapSize] = key;
    int i = *heapSize;
 
    while (i > 1 && Q[parent(i)] < Q[i])
    {
        int temp = Q[i];
        Q[i] = Q[parent(i)];
        Q[parent(i)] = temp;
        i = parent(i);
    }
}
 
int MaxPQ_Extract(int Q[], int *heapSize)
{
    int max = Q[1];
    Q[1] = Q[*heapSize];
    (*heapSize)--;
    MaxHeapify(Q, 1, *heapSize);
    return max;
}
 
void MinPQ_Insert(int Q[], int key, int *heapSize)
{
    (*heapSize)++;
    Q[*heapSize] = key;
    int i = *heapSize;
 
    while (i > 1 && Q[parent(i)] > Q[i])
    {
        int temp = Q[i];
        Q[i] = Q[parent(i)];
        Q[parent(i)] = temp;
        i = parent(i);
    }
}
 
int MinPQ_Extract(int Q[], int *heapSize)
{
    int min = Q[1];
    Q[1] = Q[*heapSize];
    (*heapSize)--;
    MinHeapify(Q, 1, *heapSize);
    return min;
}
 
int getMedian(int *minHeap, int *minHeapSize, int *maxHeap, int *maxHeapSize) {
    if (*maxHeapSize >= *minHeapSize) {
        return maxHeap[1];
    } else {
        return minHeap[1];
    }
}
 
void balanceHeaps(int *minHeap, int *minHeapSize, int *maxHeap, int *maxHeapSize) {
    if (*maxHeapSize > *minHeapSize + 1) {
        int maxRoot = MaxPQ_Extract(maxHeap, maxHeapSize);
        MinPQ_Insert(minHeap, maxRoot, minHeapSize);
    } else if (*minHeapSize > *maxHeapSize) {
        int minRoot = MinPQ_Extract(minHeap, minHeapSize);
        MaxPQ_Insert(maxHeap, minRoot, maxHeapSize);
    }
}
 
int main() {
    int N, X, minPQ[MAXT + 1], minPQSize, maxPQ[MAXT + 1], maxPQSize;
    double acc;
 
    while (scanf("%d", &N) != EOF && N != 0) {
        maxPQSize = 0;
        minPQSize = 0;
        acc = 0;
 
        for (int i = 0; i < N; i++) {
            scanf("%d", &X);
 
            if (maxPQSize == 0 || X <= maxPQ[1]) {
                MaxPQ_Insert(maxPQ, X, &maxPQSize);
            } else {
                MinPQ_Insert(minPQ, X, &minPQSize);
            }
            balanceHeaps(minPQ, &minPQSize, maxPQ, &maxPQSize);
            acc += getMedian(minPQ, &minPQSize, maxPQ, &maxPQSize);
        }
        printf("%.2lf\n", acc / N);
    }
 
    return 0;
}