#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAX 1000000

struct person{
    int key;
    char name[22];
};
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
void MinHeapify(struct person A[], int i, int heap_size) {
    
    int l, r, least;
    struct person temp;

    l = left(i);
    r = right(i);


    if (l <= heap_size && A[l].key < A[i].key){
       
        least = l;
    
    }
    else{
       
        least = i;
    
    }

    if((r<=heap_size) && (A[r].key <A [least].key)){
        
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
struct person MinPQ_minimum(struct person A[]) {
    return A[1];
}

//funcion que extrae el menor elemento del heap
struct person MinPQ_Extract(struct person A[], int *heap_size){

    struct person minPerson;
    minPerson.key = myNegativeInfinite;

    if(*heap_size < 1){
        printf("Error: heap underflow\n");
    }

    else{
        minPerson = A[1];
        A[1] = A[*heap_size];
        *heap_size = *heap_size - 1;
        MinHeapify(A, 1, *heap_size);

    }

    return minPerson;
}

//funcion que disminuye el valor de un nodo
void MinPQ_DecreaseKey(struct person A[], int i, struct person user) {
    
    struct person temp;

    if(user.key > A[i].key){
        printf("Error: new key is larger than current key\n");
    }

    A[i] = user;

    while(i > 1 && A[parent(i)].key > A[i].key){
        
        temp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = temp;
        i = parent(i);
    
    }

}

//funcion que inserta un nuevo elemento en el heap
void MinPQ_Insert(struct person A[], struct person user, int *heap_size) {
    
    *heap_size = *heap_size + 1;
    A[*heap_size].key = myPositiveInfinite;
    MinPQ_DecreaseKey(A, *heap_size, user);

}


int main() {

    int heap_size = 0, p, idLine = 0;
    struct person A[MAX + 1], user;
    char word[22];

    while(scanf("%s", word) != EOF) {

        if(word[0] != 'V')
        {
            scanf("%d", &p);
            user.key = (1000 - p ) * 1000000 + idLine;
            idLine++;
            strcpy(user.name, word);
            MinPQ_Insert(A, user, &heap_size);
        }
        else
        {
            if(heap_size == 0){

                printf("\n");
            
            }
            
            else if(heap_size > 0){
                
                    user = MinPQ_Extract(A, &heap_size);
                    printf("%s\n", user.name);
            
            }
        }
    }

    return 0;
}