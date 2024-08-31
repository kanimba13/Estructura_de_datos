#include <stdio.h>

// Function to compute Johann's Function using the optimized formula
unsigned long long johanns_function(int n) {
    return (unsigned long long)n * (n + 1) * (n + 2) / 6;
}

int main() {
    int t;
    
    // Read the number of test cases
    scanf("%d", &t);
    
    while (t--) {
        int n;
        
        // Read the value of n
        scanf("%d", &n);
        
        // Compute and print the result for this test case
        printf("%llu\n", johanns_function(n));
    }

    return 0;
}
