#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

void myMerge(char *A[], int p, int q, int r)
{
    int n1 = q - p + 1, n2 = r - q;
    int i, j, k;
    char *L[n1], *R[n2];

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
        if (strcmp(L[i], R[j]) <= 0)
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

void MergeSort(char *A[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) >> 1;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

typedef struct
{
    char **array;
    int length;
    int capacity;
} StringVector;

void stringVectorNew(StringVector *v)
{
    v->length = 0;
    v->capacity = 0;
    v->array = NULL;
}

void stringVectorPushBack(StringVector *v, char *value)
{
    if (v->length == v->capacity)
    {
        if (v->capacity == 0)
        {
            v->capacity = 1;
            v->array = (char **)malloc(sizeof(char *) * v->capacity);
        }
        else
        {
            v->capacity *= 2;
            v->array = (char **)realloc(v->array, sizeof(char *) * v->capacity);
        }
    }
    v->array[v->length++] = value;
}

void stringVectorSort(StringVector *v)
{
    MergeSort(v->array, 0, v->length - 1);
}

void stringVectorDestroy(StringVector *v, bool freeStrings)
{
    if (freeStrings)
    {
        for (int i = 0; i < v->length; i++)
            free(v->array[i]);
    }
    if (v->array)
        free(v->array);
}

void initializeMovements(Cell movements[])
{
    // 1: Down, 2: Right, 3: Left, 4: Up
    // Accommodating the direction choices to the whims of the judge.
    movements[0].coord_x = 0;
    movements[0].coord_y = 0;
    movements[4].coord_x = 0;
    movements[4].coord_y = -1;
    movements[1].coord_x = 0;
    movements[1].coord_y = 1;
    movements[2].coord_x = 1;
    movements[2].coord_y = 0;
    movements[3].coord_x = -1;
    movements[3].coord_y = 0;
}

void BFS_Maze(char Maze[MAXH][MAXW], int W, int H, Cell s,
              int color[MAXH][MAXW], int d[MAXH][MAXW], Cell pi[MAXH][MAXW])
{
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement;
    Cell NILcell, u, v, Q[MAXH * MAXW], movements[5];
    NILcell.coord_x = NIL;
    NILcell.coord_y = NIL;
    initializeMovements(movements);

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            color[idRow][idColumn] = WHITE;
            d[idRow][idColumn] = INFINITE;
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
    }
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

char movementAssigner(Cell prevCell, Cell currentCell)
{
    if (prevCell.coord_x == currentCell.coord_x)
    {
        if (prevCell.coord_y < currentCell.coord_y)
            return 'D';
        else
            return 'U';
    }
    else
    {
        if (prevCell.coord_x < currentCell.coord_x)
            return 'R';
        else
            return 'L';
    }
}

void solver(char Maze[MAXH][MAXW], int W, int H, Cell s)
{
    int color[MAXH][MAXW], d[MAXH][MAXW], idRow, idColumn, i;
    Cell pi[MAXH][MAXW];
    Cell currentCell, prevCell;
    char *movString;
    // The maximum number of theoretical paths is pi * (min(W, H) - 1), but I don't want to assume such unrealistic, horrible and *empty* case.
    // So we're gonna use my modern vector technology. TM, all rights reserved :D
    StringVector farthestPaths;
    int farthestDistance = 0;

    BFS_Maze(Maze, W, H, s, color, d, pi);

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            if (d[idRow][idColumn] != INFINITE && d[idRow][idColumn] > farthestDistance)
            {
                farthestDistance = d[idRow][idColumn];
            }
        }
    }

    stringVectorNew(&farthestPaths);

    for (idRow = 1; idRow <= H; idRow++)
    {
        for (idColumn = 1; idColumn <= W; idColumn++)
        {
            if (d[idRow][idColumn] == farthestDistance)
            {
                prevCell.coord_x = idColumn;
                prevCell.coord_y = idRow;
                movString = (char *)malloc(farthestDistance + 1);
                movString[farthestDistance] = '\0';
                currentCell = pi[idRow][idColumn];
                i = farthestDistance - 1;
                while (i >= 0)
                {
                    movString[i] = movementAssigner(currentCell, prevCell);
                    prevCell = currentCell;
                    currentCell = pi[currentCell.coord_y][currentCell.coord_x];
                    i--;
                }
                stringVectorPushBack(&farthestPaths, movString);
            }
        }
    }

    printf("%d %d\n", farthestPaths.length, farthestDistance);
    stringVectorSort(&farthestPaths);
    for (i = 0; i < farthestPaths.length; i++)
    {
        printf("%s\n", farthestPaths.array[i]);
    }
    // stringVectorDestroy(&farthestPaths, true);
}

int main()
{
    char Maze[MAXH][MAXW];
    int totalCases, idCase, W, H;
    Cell source;

    scanf("%d", &totalCases);
    for (idCase = 1; idCase <= totalCases; idCase++)
    {
        scanf("%d %d", &W, &H);
        source = ReadMaze(Maze, W, H);
        printf("Case %d:\n", idCase);
        solver(Maze, W, H, source);
    }
    return 0;
}
