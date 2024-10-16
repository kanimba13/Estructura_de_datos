#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *p;
    p = (int *) malloc(sizeof(int));
    printf("Size in bytes of type int: %d\n", sizeof(int));
    printf("Size in bytes of type int: %d\n", p);
    *p = 821;
    printf("Value of p: %d\n", p);
    printf("Value of *p: %d\n", *p);

    return 0;

}