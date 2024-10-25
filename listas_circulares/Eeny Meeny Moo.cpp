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

int solver(int n, int skips){
    struct node *tail = NULL;
    int i = 1;
    while(i <= n){
        tail = InsertInCircularLinkedList(tail, i);
        i++;
    }
    while(tail->next != tail){
        tail = DeleteFirstNodeInCircularLinkedList(tail);
        for(i = 0; i < skips; i++){
            tail = tail->next;
        }
    }
    if(tail->key == 2){
        return skips + 1;
    }
    else{
        return solver(n, skips + 1);
    }
}

int main(){
    int n;

    while(scanf("%d", &n)){
        if(n == 0){
            break;
        }else{
        printf("%d\n",solver(n, 1));
        }
    }

    return 0;
}