#include <stdio.h>
#include <math.h>

int main() {
    unsigned long long int steps, triangular, x, y, k;
    
    while (scanf("%llu", &steps) && steps > 0) {
    k = (-1 + sqrt(1 + 8 * steps)) / 2;
    triangular = (k * (k + 1)) / 2;

    if (triangular != steps) {
        k++;
        triangular = (k * (k + 1)) / 2;
    }

    if (k % 2 == 0) {
        x = steps - (triangular - k);
        y = k + 1 - x;
    } else {
        y = steps - (triangular - k);
        x = k + 1 - y;
    }
        printf("%llu %llu\n", x, y); 
    }
    return 0;
}