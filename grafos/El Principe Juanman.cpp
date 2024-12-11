#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1
#define myInfinite 2147483647
#define MAXH 1000
#define MAXW 1000

struct cell{
    int coord_x;
    int coord_y;
};

void initializeMovements(struct cell movements[]){
    movements[1].coord_x = 0;
    movements[1].coord_y = -1;
    movements[2].coord_x = 0;
    movements[2].coord_y = 1;
    movements[3].coord_x = 1;
    movements[3].coord_y = 0;
    movements[4].coord_x = -1;
    movements[4].coord_y = 0;
}


void BFZ_Maze(char Maze[][MAXW + 1], int W, int H, struct cell s,int color[][MAXW + 1], int d[][MAXW + 1], struct cell pi[][MAXW + 1]){
    int idRow, idColumn, idHead = 1, idTail = 1, idMovement;
    struct cell NILcell, u, v, Q[MAXH * MAXW + 1], movements[5];
    NILcell.coord_x = NIL;
    NILcell.coord_y = NIL;

    for(idRow = 1; idRow <= H; idRow++){
        for(idColumn = 1; idColumn <= W; idColumn++){
            color[idRow][idColumn] = WHITE;
            d[idRow][idColumn] = myInfinite;
            pi[idRow][idColumn] = NILcell;
        }
    }

    color[s.coord_y][s.coord_x] = GRAY;
    d[s.coord_y][s.coord_x] = 0;
    pi[s.coord_y][s.coord_x] = NILcell;
    Q[idTail] = s;
    idTail ++;
    initializeMovements(movements);

    while(idHead < idTail){
        u = Q[idHead];
        idHead ++;
        for(idMovement = 1; idMovement <= 4; idMovement++){
            v.coord_x = u.coord_x + movements[idMovement].coord_x;
            v.coord_y = u.coord_y + movements[idMovement].coord_y;

            if((v.coord_x >= 1 && v.coord_x <= W) 
            && (v.coord_y >= 1 && v.coord_y <= H) 
            && (Maze[v.coord_y][v.coord_x] != '#') 
            && (color[v.coord_y][v.coord_x] == WHITE)){

                color[v.coord_y][v.coord_x] = GRAY;
                d[v.coord_y][v.coord_x] = d[u.coord_y][u.coord_x] + 1;
                pi[v.coord_y][v.coord_x] = u;
                Q[idTail] = v;
                idTail ++;
            }
        }
        color[u.coord_y][u.coord_x] = BLACK;
    }
}

struct cell ReadMaze(char Maze[][MAXW + 1], int W, int H){
    int idRow, idColumn;
    struct cell source;
    char line[MAXW + 1];
    for(idRow = 1; idRow <= H; idRow++){
        scanf("%s", line);
        for(idColumn = 1; idColumn <= W; idColumn++){
            if(line[idColumn - 1] == '@'){
                source.coord_x = idColumn;
                source.coord_y = idRow;
                line[idColumn - 1] = '.';
            }
            Maze[idRow][idColumn] = line[idColumn - 1];
        }
    }
    return source;
}

void PrintMaze(char Maze[][MAXW + 1], int W, int H){
    int idRow, idColumn;
    for(idRow = 1; idRow <= H; idRow++){
        for(idColumn = 1; idColumn <= W; idColumn++){
            printf("%c", Maze[idRow][idColumn]);
        }
        printf("\n");
    }
    printf("\n");
}

int solver(char Maze[][MAXW + 1], int W, int H, struct cell s){
    int color[MAXH + 1][MAXW + 1], d[MAXH + 1][MAXW + 1], idRow, idColumn, result = 0;
    struct cell pi[MAXH + 1][MAXW + 1];

    BFZ_Maze(Maze, W, H, s, color, d, pi);

    for (idRow = 1; idRow <= H; idRow++){
        for (idColumn = 1; idColumn <= W; idColumn++){
            if (d[idRow][idColumn] != myInfinite)
                result ++;
        }
    }
    return result;
}

int main(){
    int totalCases, idCase, W, H, result;
    char Maze[MAXH + 1][MAXW + 1];
    struct cell source;

    scanf("%d", &totalCases);
    for(idCase = 1; idCase <= totalCases; idCase++){
        scanf("%d %d", &W, &H);
        source = ReadMaze(Maze, W, H);
        result = solver(Maze, W, H, source);
        printf("Case %d: %d\n", idCase, result);
    }
    return 0;
}