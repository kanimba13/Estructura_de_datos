#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -2147483648
#define INFINITE 2147483647
#define MAXH 1001
#define MAXW 1001

typedef struct
{
    int coord_x;
    int coord_y;
} Cell;

typedef struct IntVector
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

void initializeMovements(Cell movements[])
{
    movements[0].coord_x = 0;
    movements[0].coord_y = 0;
    movements[1].coord_x = 0;
    movements[1].coord_y = -1;
    movements[2].coord_x = 0;
    movements[2].coord_y = 1;
    movements[3].coord_x = 1;
    movements[3].coord_y = 0;
    movements[4].coord_x = -1;
    movements[4].coord_y = 0;
}

/// @brief Returns the total cells reachable from the starting point
int BFS_Maze(char Maze[MAXH][MAXW], int W, int H, Cell s, int mark,
             int color[MAXH][MAXW], int clusterMarks[MAXH][MAXW], int d[MAXH][MAXW], Cell pi[MAXH][MAXW])
{
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement, totalReachableCells = 0;
    Cell NILcell, u, v, Q[MAXH * MAXW], movements[5];
    NILcell.coord_x = NIL;
    NILcell.coord_y = NIL;
    initializeMovements(movements);

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            color[idRow][idColumn] = WHITE;
            pi[idRow][idColumn] = NILcell;
        }
    }

    color[s.coord_y][s.coord_x] = GRAY;
    d[s.coord_y][s.coord_x] = 0;
    pi[s.coord_y][s.coord_x] = NILcell;
    Q[idTail] = s;
    idTail = idTail + 1;

    while (idHead < idTail)
    {
        u = Q[idHead];
        idHead = idHead + 1;
        for (idMovement = 1; idMovement <= 4; idMovement++)
        {
            v.coord_x = u.coord_x + movements[idMovement].coord_x;
            v.coord_y = u.coord_y + movements[idMovement].coord_y;
            if (v.coord_x >= 1 && v.coord_x <= W && v.coord_y >= 1 && v.coord_y <= H && Maze[v.coord_y][v.coord_x] == '.' && color[v.coord_y][v.coord_x] == WHITE)
            {
                color[v.coord_y][v.coord_x] = GRAY;
                d[v.coord_y][v.coord_x] = d[u.coord_y][u.coord_x] + 1;
                pi[v.coord_y][v.coord_x] = u;
                Q[idTail] = v;
                idTail++;
            }
        }

        color[u.coord_y][u.coord_x] = BLACK;
        totalReachableCells++;
        clusterMarks[u.coord_y][u.coord_x] = mark;
    }

    return totalReachableCells;
}

Cell ReadMaze(char Maze[MAXH][MAXW], int W, int H)
{
    int idRow, idColumn;
    char line[MAXW];
    Cell source;

    for (idRow = 1; idRow <= H; idRow++)
    {
        scanf("%s", line);
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            if (line[idColumn - 1] == '@')
            {
                source.coord_x = idColumn;
                source.coord_y = idRow;
                line[idColumn - 1] = '.';
            }

            Maze[idRow][idColumn] = line[idColumn - 1];
        }
    }

    return source;
}

void PrintMaze(char Maze[MAXH][MAXW], int W, int H)
{
    int idRow, idColumn;

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
            printf("%c ", Maze[idRow][idColumn]);
        printf("\n");
    }
    printf("\n");
}

void solver(char Maze[MAXH][MAXW], int W, int H, int queriesCount)
{
    int color[MAXH][MAXW], clusterMarks[MAXH][MAXW], d[MAXH][MAXW], idRow, idColumn;
    Cell pi[MAXH][MAXW];
    Cell startingPoint;
    IntVector clusters;

    intVectorNew(&clusters);

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            d[idRow][idColumn] = INFINITE;
        }
    }

    for (int i = 0; i < queriesCount; i++)
    {
        scanf("%d %d", &startingPoint.coord_y, &startingPoint.coord_x);

        if (d[startingPoint.coord_y][startingPoint.coord_x] == INFINITE)
            intVectorPushBack(&clusters, BFS_Maze(Maze, W, H, startingPoint, clusters.length, color, clusterMarks, d, pi));

        printf("%d\n", clusters.array[clusterMarks[startingPoint.coord_y][startingPoint.coord_x]]);
    }

    intVectorDestroy(&clusters);
}

int main()
{
    char Maze[MAXH][MAXW];
    int totalCases, idCase, W, H, queriesCount;

    scanf("%d", &totalCases);
    for (idCase = 1; idCase <= totalCases; idCase++)
    {
        scanf("%d %d", &W, &H);
        ReadMaze(Maze, W, H);
        scanf("%d", &queriesCount);
        printf("Case %d:\n", idCase);
        solver(Maze, W, H, queriesCount);
    }
    return 0;
}
