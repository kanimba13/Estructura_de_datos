#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int totalCases, idCase, s;
    unsigned long long int totalPages, triangular, forgottenPage;
    
    scanf("%d", &totalCases);
    
    for(idCase = 1; idCase <= totalCases; idCase++)
    {
        scanf("%d", &s);
        totalPages = (-1 + sqrt(1 + 8 * s)) / 2;
        triangular = (totalPages * (totalPages + 1)) / 2;
        
        totalPages++;
        
        if(triangular == s)
        {
            forgottenPage = totalPages;
        }
        else
        {
            triangular = (totalPages * (totalPages + 1)) / 2;
            forgottenPage = triangular - s;
        }
    printf("%llu %llu\n", forgottenPage, totalPages);
    }
    
    return 0;
}