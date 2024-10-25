#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct node
{
    int key;
    struct node *next;
    struct node *prev;
};

// Funcion que inserta un nodo en la lista circular
struct node *InsertInCircularDoubleLinkedList(struct node *tail, int element){
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    if(tail == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;
        newNode->prev = tail;
        tail->next = newNode;
        newNode->next->prev = newNode;
        tail = newNode;
    }

    return tail;
}

// Funcion que elimina el primer nodo de la lista circular
struct node *DeleteFirstNodeInCircularDoubleLinkedList(struct node *tail){
    struct node *firstNode;

    if(tail == NULL){
        printf("Error: empty list\n");
    } else {
        if(tail->next == tail){
            free(tail);
            tail = NULL;
        } else {
            firstNode = tail->next;
            tail->next = firstNode->next;
            tail->next->prev = tail;
            free(firstNode);
        }
    }

    return tail;
}

// Funcion que imprime la lista circular
void PrintFromFirstToLast(struct node *tail){
    struct node *currentNode;

    if(tail == NULL){
        printf("Empty list\n");
    } else{
        currentNode = tail->next;

        while(currentNode != tail){
            printf("%d -> ", currentNode->key);
            currentNode = currentNode->next;
        }

        printf("%d -> ... \n", tail->key);
    }
}

// Funcion que imprime la lista circular en orden inverso
void PrintFromLastToFirst(struct node *tail){
    struct node *currentNode, *firstNode;

    if(tail == NULL){
        printf("Empty list\n");
    } else{
        currentNode = tail;
        firstNode = tail->next;

        while(currentNode != firstNode){
            printf("%d -> ", currentNode -> key);
            currentNode = currentNode -> prev;
        }

        printf("%d -> ... \n", firstNode->key);
    }
}

int main(){
    struct node *tail = NULL;
    int operation, element;

    while(scanf("%d", &operation) != EOF){
        if(operation == 1){
            scanf("%d", &element); //insertar un elemento
            tail = InsertInCircularDoubleLinkedList(tail, element);
            PrintFromFirstToLast(tail);
            PrintFromLastToFirst(tail);
        } else if(operation == 2){ //extraer el primer elemento
            tail = DeleteFirstNodeInCircularDoubleLinkedList(tail);
            PrintFromFirstToLast(tail);
            PrintFromLastToFirst(tail);
        } else if(operation == 3){ //mostrar la lista
            PrintFromFirstToLast(tail);
            PrintFromLastToFirst(tail);
            printf("\n");
        }else{//operacion invalida
            printf("Invalid operation\n options are 1 for insert, 2 for delete, 3 for print\n");
        }
    }

    return 0;
}