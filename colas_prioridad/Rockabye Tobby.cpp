#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define myPositiveInfinite 2147483647
#define myNegativeInfinite -2147483647
#define MAX 1000000

struct person {
    int key;          // Momento en el que se debe tomar la medicina
    int period;       // Periodo de repeticion de la medicina
    int index;        // Indice que indica el orden de insercion
    char name[15];    // Nombre de la medicina
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

    // Comparar primero por key (tiempo) y en caso de empate, por el orden de insercion (indice)
    if (l <= heap_size && (A[l].key < A[i].key || (A[l].key == A[i].key && A[l].index < A[i].index))) {
        least = l;
    } else {
        least = i;
    }

    if (r <= heap_size && (A[r].key < A[least].key || (A[r].key == A[least].key && A[r].index < A[least].index))) {
        least = r;
    }

    if (least != i) {
        temp = A[i];
        A[i] = A[least];
        A[least] = temp;
        MinHeapify(A, least, heap_size);
    }
}

//funcion que extrae el menor elemento del heap
struct person MinPQ_Extract(struct person A[], int *heap_size) {
    struct person minPerson;
    minPerson.key = myNegativeInfinite;

    if (*heap_size < 1) {
        printf("Error: heap underflow\n");
    } else {
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

    if (user.key > A[i].key) {
        printf("Error: new key is larger than current key\n");
    }

    A[i] = user;

    while (i > 1 && (A[parent(i)].key > A[i].key || (A[parent(i)].key == A[i].key && A[parent(i)].index > A[i].index))) {
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
    int cant_med, cant_min_tomar, period, casos, heap_size, order;
    struct person A[MAX + 1], user;
    char medicina[15];

    scanf("%d", &casos);
    while (casos--) {
        heap_size = 0;
        order = 0;
        scanf("%d %d", &cant_med, &cant_min_tomar);

        // Insertar todas las medicinas en el heap
        for (int i = 0; i < cant_med; i++) {
            scanf("%s %d", medicina, &period);
            user.key = period;
            user.period = period;  // Guardar el periodo original
            user.index = order++;  // Asignar un indice unico para el orden de insercion
            strcpy(user.name, medicina);
            MinPQ_Insert(A, user, &heap_size);
        }

        // Imprimir las primeras k medicinas por prioridad
        for (int i = 0; i < cant_min_tomar; i++) {
            user = MinPQ_Extract(A, &heap_size);
            printf("%d %s\n", user.key, user.name);
            
            // Reinserta la medicina con el tiempo actualizado (siguiente vez que debe tomarse)
            user.key += user.period;  // Suma el periodo al tiempo actual
            MinPQ_Insert(A, user, &heap_size);
        }
    }

    return 0;
}

