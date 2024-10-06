#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void sumarAyB(int a , int b, int c){
    c = a + b;
}   

void sumarAyBprima(int a , int b, int *c){
    *c = a + b;
}
int main(){
    int a = 10, b = 15, c = 0;
    sumarAyB(a, b, c);
    printf("c = %d\n", c);
    
    sumarAyBprima(a, b, &c);
    printf("c = %d\n", c);
}