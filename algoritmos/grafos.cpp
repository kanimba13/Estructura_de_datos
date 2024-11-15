#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXV 1000
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1
#define myInfinite 2147483647

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

void BFS (struct graph *G, int s, int d[], int color[], int pi[]){
    int u, v, Q[MAXV + 1], idHead = 1, idTail = 1;
    struct edge *tempEdge;
    
    for(u = 1; u <= G->n_vertex; u++){
        color[u] = WHITE;
        d[u] = myInfinite;
        pi[u] = NIL;
    }
    color[s] = GRAY;
    d[s] = 0;
    pi[s] = NIL;

    Q[idTail] = s;
    idTail++;

    while (idTail != idHead){
        u = Q[idHead];
        idHead++;
        tempEdge = G->Adj[u];

        while (tempEdge != NULL){
            v = tempEdge->vertex;
            if (color[v] == WHITE){
                color[v] = GRAY;
                d[v] = d[u] + 1;
                pi[v] = u;
                Q[idTail] = v;
                idTail++;
            }
            tempEdge = tempEdge->next;
        }
        color[u] = BLACK;
    }
}

void path(int pi[], int u, int s){
    if (u == s)
        printf("%d", s);
    else{
        path(pi, pi[u], s);
        printf(" -> %d", u);
    }
}

void solver(struct graph *G, int s){
    int d[MAXV + 1], color[MAXV + 1], pi[MAXV + 1], u;
    int furthest = 0, furthestVertex = 0;
    BFS(G, s, d, color, pi);
    printf("\n");
    for(u = 1; u <= G->n_vertex; u++){
        printf("color[%d] = ", u);
        if (color[u] == WHITE)
            printf("WHITE\n");
        else if (color[u] == GRAY)
            printf("GRAY\n");
        else
            printf("BLACK\n");
    }
    printf("\n");
    for(u = 1; u <= G->n_vertex; u++){
        printf("d[%d] = ", u);
        if (d[u] == myInfinite)
            printf("infinite\n");
        else
            printf("%d\n", d[u]);
        if(d[u] > furthest){
            furthest = d[u];
            furthestVertex = u;
        }
        
    }
    printf("\n");
    for(u = 1; u <= G->n_vertex; u++){
        printf("pi[%d] = ", u);
        if (pi[u] == NIL)
            printf("NIL\n");
        else
            printf("%d\n", pi[u]);
    }
    printf("\n");
    printf("Furthest vertex = %d, distance = %d\n", furthestVertex, furthest);
    path(pi, furthestVertex, s);
    printf("\n");
}

void DFS(struct graph *G){
    int u, color[MAXV + 1], d[MAXV + 1], f[MAXV + 1], pi[MAXV + 1], time = 0;
    for(u = 1; u <= G->n_vertex; u++){
        color[u] = WHITE;
        pi[u] = NIL;
    }
    for(u = 1; u <= G->n_vertex; u++){
        if (color[u] == WHITE)
            DFS_Visit(G, u, color, d, f, pi, &time);
    }
}

void DFS_Visit(struct graph *G, int u, int color[], int d[], int f[], int pi[], int *time){
    int v;
    struct edge *tempEdge;
    color[u] = GRAY;
    *time = *time + 1;
    d[u] = *time;
    tempEdge = G->Adj[u];
    while (tempEdge != NULL){
        v = tempEdge->vertex;
        if (color[v] == WHITE){
            pi[v] = u;
            DFS_Visit(G, v, color, d, f, pi, time);
        }
        tempEdge = tempEdge->next;
    }
    color[u] = BLACK;
    *time = *time + 1;
    f[u] = *time;
}

int main()
{
    int vertices, edges;
    struct graph *G;

    while(scanf("%d %d", &vertices, &edges) != EOF)
    {
        G = ReadGraph(vertices, edges);
        PrintGraph(G);
        solver(G, 5);
        G = DeleteGraph(G);
        PrintGraph(G);
    }
    return 0;
}