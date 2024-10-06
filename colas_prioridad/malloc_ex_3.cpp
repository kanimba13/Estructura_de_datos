#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int main(){
    char *p, *q;
    int n = 12;
    p = (char *)malloc(n);
    strcpy(p, "Pascal");
    q = (char *)malloc(n);
    strcpy(q, "Lenguaje C");
    printf("%s %s\n", p, q);
    free(q);//se libera la memoria para evitar memoria zombie
    printf("%s %s\n", p, q);
    q = p;
    printf("%s %s\n", p, q);
}