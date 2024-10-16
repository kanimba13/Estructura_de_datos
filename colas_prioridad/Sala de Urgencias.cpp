#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXT 200000
#define myNegativeInfinite -2147483647
#define myPositiveInfinite 2147483647

typedef struct {
    int hora_llegada;
    int prioridad;
    char nombre[22];
    long long key;
} Paciente;

typedef struct {
    Paciente pacientes[MAXT];
    int heapSize;
} MinHeap;

int Parent(int i) {
    return i / 2;
}

int Left(int i) {
    return 2 * i;
}

int Right(int i) {
    return 2 * i + 1;
}

void MinHeapify(MinHeap *heap, int i) {
    int l = Left(i), r = Right(i), least = i;
    Paciente temp;

    if (l <= heap->heapSize &&
        (heap->pacientes[l].key < heap->pacientes[i].key)) {
        least = l;
    }

    if (r <= heap->heapSize &&
        (heap->pacientes[r].key < heap->pacientes[least].key)) {
        least = r;
    }

    if (least != i) {
        temp = heap->pacientes[i];
        heap->pacientes[i] = heap->pacientes[least];
        heap->pacientes[least] = temp;
        MinHeapify(heap, least);
    }
}

Paciente MinPQ_Extract(MinHeap *heap) {
    if (heap->heapSize < 1) {
        Paciente empty = {myNegativeInfinite, myNegativeInfinite, "", 0};
        return empty;
    } else {
        Paciente min = heap->pacientes[1];
        heap->pacientes[1] = heap->pacientes[heap->heapSize];
        heap->heapSize--;
        MinHeapify(heap, 1);
        return min;
    }
}

void MinPQ_Insert(MinHeap *heap, Paciente paciente) {
    heap->heapSize++;
    heap->pacientes[heap->heapSize] = paciente;
    int i = heap->heapSize;

    while (i > 1 && heap->pacientes[Parent(i)].key > heap->pacientes[i].key) {
        Paciente temp = heap->pacientes[i];
        heap->pacientes[i] = heap->pacientes[Parent(i)];
        heap->pacientes[Parent(i)] = temp;
        i = Parent(i);
    }
}

int main() {
    MinHeap heap;
    heap.heapSize = 0;
   
    int n;  
    while (scanf("%d", &n) != EOF) {
        heap.heapSize = 0;
        for (int i = 0; i < n; i++) {
            int tipo, hora;
            scanf("%d %d", &tipo, &hora);
           
            if (tipo == 1) {
                int prioridad;
                char nombre[22];
                scanf("%d %s", &prioridad, nombre);
               
                Paciente paciente;
                paciente.hora_llegada = hora;
                paciente.prioridad = prioridad;
                strcpy(paciente.nombre, nombre);
                paciente.key = (long long)prioridad * 1000000 + hora;
               
                MinPQ_Insert(&heap, paciente);
               
            } else if (tipo == 2) {
                Paciente atendido = MinPQ_Extract(&heap);
                if (atendido.prioridad != myNegativeInfinite) {
                    int tiempo_espera = hora - atendido.hora_llegada;
                    printf("%d %d %d %s\n", atendido.hora_llegada, hora, tiempo_espera, atendido.nombre);
                }
            }
        }
    }

    return 0;
}