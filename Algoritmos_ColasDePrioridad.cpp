#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAX 500000
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

int main() {
    int A[MAX + 1], operation, element, heap_size = 0;

    while(scanf("%d", &operation) != EOF) {
        //insertar un elemento
        if(operation == 1) {
            scanf("%d", &element);
            MinPQ_Insert(A, element, &heap_size);
        }
        //extraer el menor elemento
        else if(operation == 2) {
            element = MinPQ_Extract(A, &heap_size);
            printf("%d\n", element);
        }
    }

    return 0;
}