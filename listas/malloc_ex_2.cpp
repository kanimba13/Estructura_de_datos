#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef struct R
{
    int a;
    float b;
    double c;
    char *p;
}   estructura;

int main()
{
    printf("Sise in bytes of int: %d\n", sizeof(int));
    printf("Sise in bytes of float: %d\n", sizeof(float));
    printf("Sise in bytes of double: %d\n", sizeof(double));
    printf("Sise in bytes of long long int: %d\n", sizeof(long long int));
    printf("Sise in bytes of char: %d\n", sizeof(char));
    printf("Sise in bytes of estructura: %d\n", sizeof(estructura));

//  int n = 10;
/*  estructura *q;
    q = (estructura *)malloc(sizeof(estructura));

    q->a = 8;
    q->b = 10.31;
    q->c = 10.32;
    q->p = (char *)malloc(n);
    strcpy(q->p, "Cadena");
    printf("%d %.2f %.2lf %s\n", q->a, q->b, q->c, q->p);
*/

//operador -> es para hacer referencia a un puntero
//operador . es para hacer referencia a un dato estatico

/*  estructura q
    q.a = 8;
    q.b = 10.31;
    q.c = 10.32;
    q.p = (char *)malloc(n);
    strcpy(q.p, "Cadena");
    printf("%d %.2f %.2lf %s\n", q.a, q.b, q.c, q.p);
*/    
    return 0;
}