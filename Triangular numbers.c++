#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    unsigned long int n, triangular, k, kplus;
    
    while((cin >> n) && (n > 0))
    {
        k = (-1 + (unsigned long int) sqrt(1 + 8*(double)n))/2;
        kplus= k+1;
    
    if (k % 2 == 0){
        k /=2;
    }
    else{
        kplus /=2;
    }
    triangular = k * kplus;
    
    if(triangular == n)
        cout<< "YES\n";
    
    else
        cout<< "NO\n";
    }
    return 0;
}