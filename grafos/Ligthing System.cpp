#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXV 10000
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1


struct edge
{
    int vertex;
/*  int weight;  */
    struct edge *next;
};


struct graph
{
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV + 1];
};


struct graph *ReadGraph(int vertices, int edges)
{
    int idVertex, idEdge, u, v;
    struct graph *G;
    struct edge *tempEdge;

    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertices;
    G->m_edges = edges;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;

    for(idEdge = 1; idEdge <= G->m_edges; idEdge++)
    {
        scanf("%d %d", &u, &v);
        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;

        if(u != v)
        {
            tempEdge = (struct edge *) malloc(sizeof(struct edge));
            tempEdge->vertex = u;
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

    if(G != NULL)
    {
        printf("Representation for graph's adjacent lists: \n");
        for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        {
            printf("[%d]: ", idVertex);
            tempEdge = G->Adj[idVertex];
            while(tempEdge != NULL)
            {
                printf(" -> %d", tempEdge->vertex);
                tempEdge = tempEdge->next;
            }
            printf(" -> NULL\n");
        }
    }
    else
        printf("Empty Graph.\n");
}


struct graph *DeleteGraph(struct graph *G)
{
    int idVertex;
    struct edge *ActualEdge, *NextEdge;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    {
        ActualEdge = G->Adj[idVertex];
        while(ActualEdge != NULL)
        {
            NextEdge = ActualEdge->next;
            free(ActualEdge);
            ActualEdge = NextEdge;
        }
    }
    free(G);
    G = NULL;
    return G;
}

void DFS_Visit(struct graph *G, int u, int color[], int pi[], int d[], int f[], int *time)
{
    int v;
    struct edge *tempEdge;
    color[u] = GRAY;
    *time = *time + 1;
    d[u] = *time;
    tempEdge = G->Adj[u];
    while (tempEdge != NULL)
    {
        v = tempEdge->vertex;
        if (color[v] == WHITE)
        {
            pi[v] = u;
            DFS_Visit(G, v, color, pi, d, f, time);
        }
        tempEdge = tempEdge->next;
    }
    color[u] = BLACK;
    *time = *time + 1;
    f[u] = *time;

}

void DFS (struct graph *G, int color[], int pi[], int d[], int f[])
{
    int u, time = 0;
    for(u = 1; u <= G->n_vertex; u++)
    {
        color[u] = WHITE;
        pi[u] = NIL;
    }
    for(u = 1; u <= G->n_vertex; u++)
    {
        if (color[u] == WHITE)
            DFS_Visit(G, u, color, pi, d, f, &time);
    }
}

void solver(struct graph *G){
    int u, color[MAXV + 1], d[MAXV + 1], f[MAXV + 1], pi[MAXV + 1];
    int sizeTree;
    DFS(G, color, pi, d, f);

    for(u = 1; u <= G->n_vertex; u++){
        if(pi[u] == NIL){
            sizeTree = ceil((double)(f[u] - d[u])/2.0);
            printf("%d %d\n", u, sizeTree);
        }
    }   
}

int main()
{
    int vertices, edges;
    struct graph *G;

    while(scanf("%d %d", &vertices, &edges) != EOF)
    {
        G = ReadGraph(vertices, edges);
        solver(G);
        G = DeleteGraph(G);
    }
    return 0;
}