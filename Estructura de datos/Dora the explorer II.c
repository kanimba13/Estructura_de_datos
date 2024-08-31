#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int x, y;
    unsigned long long diagonal, n, result;
    while (scanf("%d", &x) && scanf("%d", &y) && x > 0 && y > 0) {
        diagonal = x + y - 1;
        n = diagonal * (diagonal + 1) / 2;
        if (diagonal % 2 == 0) {
            result = n - diagonal + x;
        }
        else {
            result = n - diagonal + y;
        }
        printf("%llu\n", result);
    }
    return 0;
}