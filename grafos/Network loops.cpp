#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# define MAXH 1005
# define MAXW 1005
# define WHITE 2
# define GRAY 1
# define BLACK 0
# define myInfinite 2147483647
# define NIL -1
#define MAXV 1000
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
    struct edge *Adj[MAXV + 1];
};


struct graph *ReadGraph(int vertices, int edges)
{
    int idVertex, idEdge, u, v, w;
    struct graph *G;
    struct edge *tempEdge;

    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertices;
    G->m_edges = edges;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;

    for(idEdge = 1; idEdge <= G->m_edges; idEdge++)
    {
        scanf("%d %d %d", &u, &v, &w);
        u++;
        v++;
        w *= -1;
        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->weight = w;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;

        if(u != v)
        {
            tempEdge = (struct edge *) malloc(sizeof(struct edge));
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

    if(G != NULL)
    {
        printf("Representation for graph's adjacent lists: \n");
        for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        {
            printf("[%d]: ", idVertex);
            tempEdge = G->Adj[idVertex];
            while(tempEdge != NULL)
            {
                printf(" -> [%d, %d]", tempEdge->vertex, tempEdge->weight);
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

int ExtraxtMin(int d[], int  InQuieue[],int n, int *sizeQueue)
{
    int u, minVertex = NIL, minDistance = myInfinite;
    for (u= 1; u<= n; u++)
    {
        if ((d[u] < minDistance)&&(InQuieue[u] == TRUE))
        {
            minDistance = d[u];
            minVertex = u;
        }
    }
    if(minVertex!= NIL)
    {
        *sizeQueue = *sizeQueue -1;
        InQuieue[minVertex] = FALSE;
    }

    return minVertex;
}

void Prim(struct graph *G, int s, int d[], int pi[])
{
    int u,v,sizeQueue = G->n_vertex,InQuieue[MAXV + 1],w;
    struct edge *tempEdge;

    for(u=1;u<= G->n_vertex;u++)
    {
        d[u] = myInfinite;
        pi[u] = NIL;
    }

    d[s] = 0;

    for(u= 1; u<= G->n_vertex; u++)
        InQuieue[u] = TRUE;

    while (sizeQueue > 0)
    {
        u = ExtraxtMin(d, InQuieue, G->n_vertex, &sizeQueue);
        if (u == NIL)
            break;
        tempEdge = G->Adj[u];
        while (tempEdge != NULL)
        {
            v= tempEdge->vertex;
            w= tempEdge->weight;
            if((InQuieue[v] == TRUE)&&(d[v] > w))
            {
                d[v] = w;
                pi[v] = u;
            }
            tempEdge = tempEdge->next;
        }
    }
}


void solver(struct graph *G)
{
    int d[MAXV +1],pi[MAXV +1], u, minWeight = myInfinite;
    Prim(G, 1, d, pi);

    for(u = 1; u <= G->n_vertex; u++)
    {
        d[u] *= -1;
    }

    for(u= 2; u <= G->n_vertex; u++)
    {
        if(d[u] < minWeight)
            minWeight = d[u];
    }
    
	if(minWeight == myInfinite * -1){
        printf("IMPOSSIBLE\n");
    }
    else
        printf("%d\n", minWeight);
}


int main()
{
    int vertices, edges;
    struct graph *G;

    while(scanf("%d %d", &vertices, &edges) && vertices > 0 && edges > 0)
    {
        G = ReadGraph(vertices, edges);
        solver(G);
        G = DeleteGraph(G);
    }
    return 0;
}
