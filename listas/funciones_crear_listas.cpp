#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

struct node {
    int key;
    struct node *next;
};

struct node *makeList(int n){
    struct node *head = NULL, *newNode;
    while(n <= 1){
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->key = n;
        newNode->next = head;
        head = newNode;
        n--;
    }
}

void printList(struct node *head){
    struct node *actualNode = head;
    while(actualNode != NULL){
        printf("%d\n", actualNode->key);
        actualNode = actualNode->next;
    }
    printf("NULL\n");
}

void deleteList(struct node *head){
    struct node *actualNode = head;
    while(actualNode != NULL){
        actualNode = actualNode->next;
        free(actualNode);
        actualNode = actualNode;
    }
}

int main(){
    struct node *head;
    int n;
    scanf("%d", &n);
    head = makeList(n);
    printList(head);
    deleteList(head);
    printList(head);
    return 0;
}