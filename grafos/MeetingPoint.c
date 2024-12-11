#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MAXV 100005
#define myInfinite 2147483647
#define longlongPInfinite ~((long long)1 << 63)
#define longlongNInfinite ((long long)1 << 63)
#define NIL -1
#define TRUE 1
#define FALSE 0

struct edge
{
    int vertex;
    int weight;
    struct edge *next;
};

struct graph
{
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV];
};

typedef struct
{
    int *array;
    int length;
    int capacity;
} IntVector;

void intVectorNew(IntVector *v)
{
    v->length = 0;
    v->capacity = 0;
    v->array = NULL;
}

void intVectorPushBack(IntVector *v, int value)
{
    if (v->length == v->capacity)
    {
        if (v->capacity == 0)
        {
            v->capacity = 1;
            v->array = (int *)malloc(sizeof(int) * v->capacity);
        }
        else
        {
            v->capacity *= 2;
            v->array = (int *)realloc(v->array, sizeof(int) * v->capacity);
        }
    }
    v->array[v->length++] = value;
}

void intVectorDestroy(IntVector *v)
{
    if (v->array)
        free(v->array);
}

void myMerge(int A[], int p, int q, int r)
{
    int n1 = q - p + 1, n2 = r - q;
    int i, j, k;
    int L[n1], R[n2];

    // Copy left and right subarrays
    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    i = 0; // Initial index for L
    j = 0; // Initial index for R
    k = p; // Initial index for merged array

    // Merge L and R back into A
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k++] = L[i++];
        }
        else
        {
            A[k++] = R[j++];
        }
    }

    // Copy remaining elements of L, if any
    while (i < n1)
    {
        A[k++] = L[i++];
    }

    // Copy remaining elements of R, if any
    while (j < n2)
    {
        A[k++] = R[j++];
    }
}

void MergeSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) >> 1;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

void intVectorSort(IntVector *v)
{
    MergeSort(v->array, 0, v->length - 1);
}

struct nodePQ
{
    int vertex;
    long long distance;
};

int Parent(int i)
{
    return i >> 1; /* return i / 2; */
}

int Left(int i)
{
    return i << 1; /* return 2 * i; */
}

int Right(int i)
{
    return (i << 1) + 1; /* return 2 * i + 1; */
}

void MinHeapify(struct nodePQ Q[], int i, int heapSize, int positionVertex[])
{
    int l, r, least, tempPosition;
    struct nodePQ tempNode;
    l = Left(i);
    r = Right(i);

    if ((l <= heapSize) && (Q[l].distance < Q[i].distance))
        least = l;
    else
        least = i;

    if ((r <= heapSize) && (Q[r].distance < Q[least].distance))
        least = r;

    if (least != i)
    {
        tempPosition = positionVertex[Q[i].vertex];
        tempNode = Q[i];

        positionVertex[Q[i].vertex] = positionVertex[Q[least].vertex];
        Q[i] = Q[least];

        positionVertex[Q[least].vertex] = tempPosition;
        Q[least] = tempNode;

        MinHeapify(Q, least, heapSize, positionVertex);
    }
}

int MinPQ_Extract(struct nodePQ Q[], int *heapSize, int positionVertex[])
{
    int myMin = 0;

    if (*heapSize >= 1)
    {
        myMin = Q[1].vertex;

        positionVertex[Q[*heapSize].vertex] = 1;
        Q[1] = Q[*heapSize];

        *heapSize = *heapSize - 1;
        MinHeapify(Q, 1, *heapSize, positionVertex);
    }
    return myMin;
}

void MinPQ_DecreaseKey(struct nodePQ Q[], int i, long long key, int positionVertex[])
{
    int tempPosition;
    struct nodePQ tempNode;

    if (key < Q[i].distance)
    {
        Q[i].distance = key;

        while ((i > 1) && (Q[Parent(i)].distance > Q[i].distance))
        {
            tempPosition = positionVertex[Q[i].vertex];
            tempNode = Q[i];

            positionVertex[Q[i].vertex] = positionVertex[Q[Parent(i)].vertex];
            Q[i] = Q[Parent(i)];

            positionVertex[Q[Parent(i)].vertex] = tempPosition;
            Q[Parent(i)] = tempNode;

            i = Parent(i);
        }
    }
}

void MinPQ_Insert(struct nodePQ Q[], long long key, int vertex, int *heapSize, int positionVertex[])
{
    *heapSize = *heapSize + 1;
    Q[*heapSize].distance = longlongPInfinite;
    Q[*heapSize].vertex = vertex;
    positionVertex[vertex] = *heapSize;
    MinPQ_DecreaseKey(Q, *heapSize, key, positionVertex);
}

struct graph *ReadGraph(int vertexes, int edges)
{
    int idVertex, idEdge, u, v, w;
    struct graph *G;
    struct edge *tempEdge;
    G = (struct graph *)malloc(sizeof(struct graph));
    G->n_vertex = vertexes;
    G->m_edges = edges;
    for (idVertex = 0; idVertex < G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;
    for (idEdge = 0; idEdge < G->m_edges; idEdge++)
    {
        scanf("%d %d %d", &u, &v, &w);
        u--;
        v--;
        tempEdge = (struct edge *)malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->weight = w;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;
        if (u != v)
        {
            tempEdge = (struct edge *)malloc(sizeof(struct edge));
            tempEdge->vertex = u;
            tempEdge->weight = w;
            tempEdge->next = G->Adj[v];
            G->Adj[v] = tempEdge;
        }
    }
    return G;
}

void PrintGraph(struct graph *G)
{
    int idVertex;
    struct edge *tempEdge;
    if (G != NULL)
    {
        printf("\n Representation for graph 's adjacent lists : \n\n");
        for (idVertex = 0; idVertex < G->n_vertex; idVertex++)
        {
            printf("[%d]: ", idVertex + 1);
            tempEdge = G->Adj[idVertex];
            while (tempEdge != NULL)
            {
                printf(" -> (%d, %d)", tempEdge->vertex + 1, tempEdge->weight);
                tempEdge = tempEdge->next;
            }
            printf(" -> NULL \n");
        }
    }
    else
        printf("\nEmpty Graph.\n");
}

struct graph *DeleteGraph(struct graph *G)
{
    int idVertex;
    struct edge *currentEdge, *NextEdge;
    for (idVertex = 0; idVertex < G->n_vertex; idVertex++)
    {
        currentEdge = G->Adj[idVertex];
        while (currentEdge != NULL)
        {
            NextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = NextEdge;
        }
    }
    free(G);
    G = NULL;
    return G;
}

void Dijkstra(struct graph *G, long long d[], int pi[], int s)
{
    int u, v, w, heapSize = 0;
    struct nodePQ Q[MAXV + 1];
    int positionVertex[MAXV + 1], inQueue[MAXV + 1];
    struct edge *tempEdge;

    for (u = 0; u < G->n_vertex; u++)
    {
        pi[u] = NIL;
        inQueue[u] = TRUE;

        if (u == s)
        {
            MinPQ_Insert(Q, 0, s, &heapSize, positionVertex);
            d[s] = 0;
        }
        else
        {
            MinPQ_Insert(Q, longlongPInfinite, u, &heapSize, positionVertex);
            d[u] = longlongPInfinite;
        }
    }

    while (heapSize >= 1)
    {
        u = MinPQ_Extract(Q, &heapSize, positionVertex);

        if (d[u] == longlongPInfinite)
            break;

        inQueue[u] = FALSE;

        tempEdge = G->Adj[u];
        while (tempEdge != NULL)
        {
            v = tempEdge->vertex;
            w = tempEdge->weight;

            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                pi[v] = u;
                MinPQ_DecreaseKey(Q, positionVertex[v], d[v], positionVertex);
            }
            tempEdge = tempEdge->next;
        }
    }
}

void DeleteVertex(struct graph *G, int vertex)
{
    struct edge *currentEdge, *NextEdge, *prevEdge;
    int idVertex;
    for (idVertex = 0; idVertex < G->n_vertex; idVertex++)
    {
        currentEdge = G->Adj[idVertex];
        prevEdge = NULL;
        while (currentEdge != NULL)
        {
            if (currentEdge->vertex == vertex)
            {
                NextEdge = currentEdge->next;
                if (prevEdge == NULL)
                    G->Adj[idVertex] = NextEdge;
                else
                    prevEdge->next = NextEdge;
                free(currentEdge);
                currentEdge = NextEdge;
            }
            else
            {
                prevEdge = currentEdge;
                currentEdge = currentEdge->next;
            }
        }
    }
    for (currentEdge = G->Adj[vertex]; currentEdge != NULL; currentEdge = NextEdge)
    {
        NextEdge = currentEdge->next;
        free(currentEdge);
    }
    G->Adj[vertex] = NULL;
}

void solver(struct graph *G, int source, int target)
{
    int i, pi[MAXV];
    long long d[MAXV];
    long long d2[MAXV];
    long long halfWayDistance;
    IntVector nodes;

    Dijkstra(G, d, pi, source);
    halfWayDistance = d[target];
    DeleteVertex(G, target);
    Dijkstra(G, d2, pi, source);
    intVectorNew(&nodes);
    for (i = 0; i < G->n_vertex; i++)
        if (d[i] == halfWayDistance * 2 && d[i] != d2[i])
            intVectorPushBack(&nodes, i);

    if (nodes.length == 0)
        printf("*\n");
    else
    {
        intVectorSort(&nodes);
        printf("%d", nodes.array[0] + 1);
        for (i = 1; i < nodes.length; i++)
            printf(" %d", nodes.array[i] + 1);
        printf("\n");
    }
}

int main()
{
    int vertices, edges, source, target;
    struct graph *G;
    scanf("%d %d", &vertices, &edges);
    scanf("%d %d", &source, &target);
    source--;
    target--;
    G = ReadGraph(vertices, edges);
    // PrintGraph(G);
    solver(G, source, target);
    G = DeleteGraph(G);
    return 0;
}