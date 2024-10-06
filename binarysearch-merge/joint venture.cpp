#include <iostream>
#include <vector>
#include <algorithm>
#define myInfinite 2147483647

using namespace std;

int BinarySearch(unsigned long long int A[], int i, int j, unsigned long long int k) {
    int result = -1, m;
    while (i <= j) {
        m = (i + j) / 2;
        if (k == A[m]) {
            result = m;
            break;
        } else if (k > A[m]) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }
    if (result == -1) {
        result = -1 * i - 1;
    }
    return result;
}

void myMerge(unsigned long long int A[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<unsigned long long int> L(n1 + 1), R(n2 + 1);
    
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[n1] = myInfinite;
    R[n2] = myInfinite;
    
    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void MergeSort(unsigned long long int A[], int p, int r){
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long int ancho, num;
    cin >> ancho >> num;
    vector<unsigned long long int> piezas(num);

    for(unsigned long long int &pieza : piezas) {
        cin >> pieza;
    }

    MergeSort(piezas.data(), 0, num - 1);
    
    bool found = false;
    for (int i = 0; i < num && !found; i++) {
        unsigned long long int complemento = ancho * 10000000ULL - piezas[i];
        int posicion = BinarySearch(piezas.data(), 0, num - 1, complemento);
        
        
        if (posicion >= 0 && posicion != i) {
            cout << "yes " << piezas[i] << " " << piezas[posicion] << "\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "danger";
    }

    return 0;
}