#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct node
{
    int key;
    struct node *next;
};

// Funcion que inserta un nodo en la lista circular
struct node *InsertInCircularLinkedList(struct node *tail, int element){
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
struct node *DeleteFirstNodeInCircularLinkedList(struct node *tail){
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
            free(firstNode);
        }
    }

    return tail;
}

// Funcion que imprime la lista circular
void PrintCircularLinkedList(struct node *tail){
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

int solver(int n, int k){
    struct node *tail = NULL, *actual;
    int i, idSoldier, idMovement, josephusPosition;
    
    for(i = 1; i <= n; i++){
        tail = InsertInCircularLinkedList(tail, i);
    }

    for(idSoldier = 1; idSoldier < n; idSoldier++){
       for(idMovement = 1; idMovement < k; idMovement++){
        tail = tail->next;
        }

        tail = DeleteFirstNodeInCircularLinkedList(tail);
    }
    josephusPosition = tail->key;
    free(tail);
    return josephusPosition;
}

int main(){
    int n, k;

    while(scanf("%d %d", &n, &k) && (n > 0 && k > 0)){
        printf("%d\n",solver(n, k));
    }

    return 0;
}