#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXV 100000
#define NIL -1
#define TRUE 1
#define FALSE 0

struct edge {
    int vertex;
    int weight;
    struct edge *next;
};

struct graph {
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV + 1];
};

struct minHeapNode {
    int v;
    int weight;
};

struct minHeap {
    int size;
    int capacity;
    int *pos;
    struct minHeapNode **array;
};

struct minHeapNode* newMinHeapNode(int v, int weight) 
{
    struct minHeapNode* minHeapNode = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));
    minHeapNode->v = v;
    minHeapNode->weight = weight;
    return minHeapNode;
}

struct minHeap* createMinHeap(int capacity)
{
    struct minHeap* minHeap = (struct minHeap*)malloc(sizeof(struct minHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct minHeapNode**)malloc(capacity * sizeof(struct minHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct minHeapNode** a, struct minHeapNode** b) 
{
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct minHeap* minHeap, int idx) 
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->weight < minHeap->array[smallest]->weight)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->weight < minHeap->array[smallest]->weight)
        smallest = right;

    if (smallest != idx) 
    {
        struct minHeapNode* smallestNode = minHeap->array[smallest];
        struct minHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct minHeap* minHeap) 
{
    return minHeap->size == 0;
}

struct minHeapNode* extractMin(struct minHeap* minHeap) 
{
    if (isEmpty(minHeap))
        return NULL;

    struct minHeapNode* root = minHeap->array[0];
    struct minHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct minHeap* minHeap, int v, int weight) 
{
    int i = minHeap->pos[v];
    minHeap->array[i]->weight = weight;

    while (i && minHeap->array[i]->weight < minHeap->array[(i - 1) / 2]->weight) 
    {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct minHeap* minHeap, int v) 
{
    return minHeap->pos[v] < minHeap->size;
}

struct graph* ReadGraph(int vertices, int edges) 
{
    int u, v, w;
    struct graph *G = (struct graph *)malloc(sizeof(struct graph));
    G->n_vertex = vertices;
    G->m_edges = edges;

    for (int i = 1; i <= vertices; i++)
        G->Adj[i] = NULL;

    for (int i = 0; i < edges; i++) 
    {
        scanf("%d %d %d", &u, &v, &w);
        struct edge *newEdge = (struct edge *)malloc(sizeof(struct edge));
        newEdge->vertex = v;
        newEdge->weight = w;
        newEdge->next = G->Adj[u];
        G->Adj[u] = newEdge;

        newEdge = (struct edge *)malloc(sizeof(struct edge));
        newEdge->vertex = u;
        newEdge->weight = w;
        newEdge->next = G->Adj[v];
        G->Adj[v] = newEdge;
    }

    return G;
}

int PrimMST(struct graph* graph) 
{
    int V = graph->n_vertex;
    int *key = (int*)malloc((V + 1) * sizeof(int));
    int *parent = (int*)malloc((V + 1) * sizeof(int));
    struct minHeap* minHeap = createMinHeap(V);

    for (int v = 1; v <= V; ++v) 
    {
        key[v] = INT_MAX;
        minHeap->array[v - 1] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v - 1;
    }

    key[1] = 0;
    minHeap->array[0] = newMinHeapNode(1, key[1]);
    minHeap->pos[1] = 0;

    minHeap->size = V;

    while (!isEmpty(minHeap)) 
    {
        struct minHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        struct edge* crawl = graph->Adj[u];
        while (crawl != NULL) 
        {
            int v = crawl->vertex;

            if (isInMinHeap(minHeap, v) && crawl->weight < key[v]) 
            {
                key[v] = crawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            crawl = crawl->next;
        }
    }

    int totalWeight = 0;
    for (int i = 1; i <= V; ++i)
        totalWeight += key[i];

    return totalWeight;
}

int main() 
{
    int N, C;
    scanf("%d %d", &N, &C);
    struct graph* G = ReadGraph(N, C);
    printf("%d\n", PrimMST(G));
    return 0;
}
