#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0

struct node
{
    int key;
    struct node *next;
};

// Funcion que inserta un nodo en la lista circular
struct node *Enqueue(struct node *tail, int element){
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    if(tail == NULL){
        newNode->next = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }

    return tail;
}

// Funcion que elimina el primer nodo de la lista circular
int Dequeue(struct node **tail){
    struct node *firstNode;
    int element = myInfinite;

    if(*tail == NULL){
        printf("Error: queue is empty\n");
    } else {
        if((*tail)->next == *tail){
            element = (*tail)->key;
            free(*tail);
            *tail = NULL;
        } else {
            firstNode = (*tail)->next;
            element = firstNode->key;
            (*tail)->next = firstNode->next;
            free(firstNode);
        }
    }

    return element;
}

// Funcion que imprime la lista circular
void printQueue(struct node *tail){
    struct node *current;

    if(tail == NULL){
        printf("Empty list\n");
    } else{
        current = tail->next;

        while(current != tail){
            printf("%d -> ", current->key);
            current = current->next;
        }

        printf("%d -> NULL \n", tail->key);
    }
}

int isEmptyQueue(struct node *tail){
    return tail == NULL ? TRUE : FALSE;
}

int main(){
    struct node *tail = NULL;
    int operation, element;

    while(scanf("%d", &operation) != EOF){
        if(operation == 1){
            scanf("%d", &element); //insertar un elemento
            tail = Enqueue(tail, element);
            printQueue(tail);
        } else if(operation == 2){ //extraer el primer elemento
            if(isEmptyQueue(tail) != TRUE){
                element = Dequeue(&tail);
                printf("%d\n", element);
            }
            printQueue(tail);
            
        } else if(operation == 3){ //mostrar la lista
            printQueue(tail);
            printf("\n");
        }else{//operacion invalida
            printf("Invalid operation\n options are 1 for enqueue, 2 for dequeue, 3 for print\n");
        }
    }

    return 0;
}