#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXT 1000
#define INFINITE ~(1 << 31)

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

void maxHeapify(int Q[], int i, int heapSize)
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
        maxHeapify(Q, largest, heapSize);
    }
}

void maxPQ_Insert(int Q[], int key, int *heapSize)
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

int maxPQ_Extract(int Q[], int *heapSize)
{
    int max = Q[1];
    Q[1] = Q[*heapSize];
    (*heapSize)--;
    maxHeapify(Q, 1, *heapSize);
    return max;
}

typedef struct Node Node;

struct Node
{
    int key;
    Node *next;
};

Node *push(Node *top, int element)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = element;
    newNode->next = top;
    top = newNode;

    return top;
}

int pop(Node **top)
{
    Node *current;
    int elem = INFINITE;

    if (*top != NULL)
    {
        elem = (*top)->key;
        current = *top;
        *top = (*top)->next;
        free(current);
    }

    return elem;
}

Node *enqueue(Node *tail, int element)
{
    Node *newNode;
    newNode = (Node *)malloc(sizeof(Node));
    newNode->key = element;

    if (tail == NULL)
        newNode->next = newNode;
    else
    {
        newNode->next = tail->next;
        tail->next = newNode;
    }
    tail = newNode;

    return tail;
}

int dequeue(Node **tail)
{
    int element = INFINITE;
    if (*tail != NULL)
    {
        if ((*tail)->next == *tail)
        {
            element = (*tail)->key;
            free(*tail);
            *tail = NULL;
        }
        else
        {
            Node *firstNode = (*tail)->next;
            element = firstNode->key;
            (*tail)->next = firstNode->next;
            free(firstNode);
        }
    }

    return element;
}

int main()
{
    int n, i, cmd, arg;
    Node *stackTop = NULL, *queueTail = NULL;
    int PQ[MAXT + 1], PQSize = 0;
    bool isStack, isQueue, isPQ;
    while (scanf("%d", &n) != EOF)
    {
        isStack = true;
        isQueue = true;
        isPQ = true;
        for (i = 0; i < n; i++)
        {
            scanf("%d", &cmd);
            scanf("%d", &arg);
            if (cmd == 1)
            {
                stackTop = push(stackTop, arg);
                queueTail = enqueue(queueTail, arg);
                maxPQ_Insert(PQ, arg, &PQSize);
            }
            else
            {
                isStack = isStack & (pop(&stackTop) == arg);
                isQueue = isQueue & (dequeue(&queueTail) == arg);
                isPQ = isPQ & (maxPQ_Extract(PQ, &PQSize) == arg);
            }
        }

        if (!(isStack | isQueue | isPQ))
            printf("impossible\n");
        else if ((isStack & isQueue) || (isQueue & isPQ) || (isStack & isPQ))
            printf("not sure\n");
        else if (isStack)
            printf("stack\n");
        else if (isQueue)
            printf("queue\n");
        else
            printf("priority queue\n");

        // Reset structures
        PQSize = 0;
        while (stackTop != NULL)
            pop(&stackTop);
        while (queueTail != NULL)
            dequeue(&queueTail);
    }
    return 0;
}