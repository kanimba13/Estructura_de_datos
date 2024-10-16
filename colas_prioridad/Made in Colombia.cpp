#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAX 100005
//funcion que retorna el padre de un nodo
int parent(int i) {
    return i / 2;
}

//funcion que retorna el hijo izquierdo de un nodo
int left(int i) {
    return 2 * i;
}

//funcion que retorna el hijo derecho de un nodo
int right(int i) {
    return 2 * i + 1;
}

//funcion que mantiene la propiedad de heap minimo
void MinHeapify(int A[], int i, int heap_size) {
    
    int l, r, least, temp;

    l = left(i);
    r = right(i);


    if (l <= heap_size && A[l] < A[i]){
       
        least = l;
    
    }
    else{
       
        least = i;
    
    }

    if((r<=heap_size) && (A[r]<A[least])){
        
        least = r;
    
    }

    if(least != i){
        
        temp = A[i];
        A[i] = A[least];
        A[least] = temp;
        MinHeapify(A, least, heap_size);
    
    }

}

//funcion que muestra el menor elemento del heap
int MinPQ_minimum(int A[]) {
    return A[1];
}

//funcion que extrae el menor elemento del heap
int MinPQ_Extract(int A[], int *heap_size){

    int min = myNegativeInfinite;

    if(*heap_size < 1){
        printf("Error: heap underflow\n");
    }

    else{
        min = A[1];
        A[1] = A[*heap_size];
        *heap_size = *heap_size - 1;
        MinHeapify(A, 1, *heap_size);

    }

    return min;
}

//funcion que disminuye el valor de un nodo
void MinPQ_DecreaseKey(int A[], int i, int key) {
    
    int temp;

    if(key > A[i]){
        printf("Error: new key is larger than current key\n");
    }

    A[i] = key;

    while(i > 1 && A[parent(i)] > A[i]){
        
        temp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = temp;
        i = parent(i);
    
    }

}

//funcion que inserta un nuevo elemento en el heap
void MinPQ_Insert(int A[], int key, int *heap_size) {
    
    *heap_size = *heap_size + 1;
    A[*heap_size] = myPositiveInfinite;
    MinPQ_DecreaseKey(A, *heap_size, key);

}

// Funcion que mantiene la propiedad de heap maximo
void MaxHeapify(int A[], int i, int heap_size) {
    int l, r, largest, temp;

    l = left(i);
    r = right(i);

    // Se cambian las comparaciones para heap de maximo
    if (l <= heap_size && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r <= heap_size && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        MaxHeapify(A, largest, heap_size);
    }
}

// Funcion que muestra el mayor elemento del heap
int MaxPQ_maximum(int A[]) {
    return A[1];
}

// Funcion que extrae el mayor elemento del heap
int MaxPQ_Extract(int A[], int *heap_size) {
    int max = myNegativeInfinite;

    if (*heap_size < 1) {
        printf("Error: heap underflow\n");
    } else {
        max = A[1];
        A[1] = A[*heap_size];
        *heap_size = *heap_size - 1;
        MaxHeapify(A, 1, *heap_size);
    }

    return max;
}

// Funcion que aumenta el valor de un nodo
void MaxPQ_IncreaseKey(int A[], int i, int key) {
    int temp;

    if (key < A[i]) {
        printf("Error: new key is smaller than current key\n");
    }

    A[i] = key;

    while (i > 1 && A[parent(i)] < A[i]) {
        temp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = temp;
        i = parent(i);
    }
}

// Funcion que inserta un nuevo elemento en el heap
void MaxPQ_Insert(int A[], int key, int *heap_size) {
    *heap_size = *heap_size + 1;
    A[*heap_size] = myNegativeInfinite;  // El valor se inicializa con el menor posible
    MaxPQ_IncreaseKey(A, *heap_size, key);
}


int main() {
    int MIN[MAX + 1], MAXI[MAX + 1], numero_datos, heap_size_MIN, heap_size_MAX, elementos;
    double resultado;
    long long int suma;

    while (1) { // Bucle infinito hasta que numero_datos sea 0
        scanf("%d", &numero_datos);
        if (numero_datos == 0) break; // Salir cuando numero_datos sea igual a 0
        
        heap_size_MIN = 0;
        heap_size_MAX = 0;
        resultado = 0.0;
        suma = 0;
        
        for (int i = 1; i <= numero_datos; i++) {
            scanf("%d", &elementos);

            if(heap_size_MAX == heap_size_MIN){
                if(elementos < MAXI[1]){
                    MaxPQ_Insert(MAXI, elementos, &heap_size_MAX);
                }
                else{
                    MinPQ_Insert(MIN, elementos, &heap_size_MIN);
                    MaxPQ_Insert(MAXI, MinPQ_Extract(MIN, &heap_size_MIN), &heap_size_MAX);      
                }
            }
            else{
                if(elementos < MAXI[1]){
                    MaxPQ_Insert(MAXI, elementos, &heap_size_MAX); 
                    MinPQ_Insert(MIN, MaxPQ_Extract(MAXI, &heap_size_MAX), &heap_size_MIN);
                }
                else{
                    MinPQ_Insert(MIN, elementos, &heap_size_MIN);
                }
            }
            suma += MaxPQ_maximum(MAXI);
        }
        resultado = (double) suma / numero_datos;
        printf("%.2lf\n", resultado);
    }
    return 0;
}