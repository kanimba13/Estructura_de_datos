#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

struct node {
    int key;
    struct node *next;
};

void printList(struct node *head){
    struct node *actualNode = head;
    while(actualNode != NULL){
        printf("%d -> ", actualNode->key);
        actualNode = actualNode->next;
    }
    printf("NULL\n");
}

struct node *InsertElementInAscendantLinkedList( struct node * head, int element){
    struct node *newNode, *previous, *actual;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    if(head == NULL){
        newNode -> next = head;
        head = newNode;
    }
    else{
        if(element <= head ->key){
            newNode -> next = head;
            head = newNode;
        }
        else{
            previous = head;
            actual = head -> next;
            while(actual != NULL && actual -> key < element){
                previous = actual;
                actual = actual -> next;
            }
            previous -> next = newNode;
            newNode -> next = actual;
        }
    }
    return head;
}

struct node * DeleteElementOfAscentantLinkedList(struct node *head, int element){
    struct node *previous, *actual;
    if(head == NULL){
        printf("The list is empty\n");
    }
    else{
        if(element < head ->key){
            printf("The element %d is not in the list\n", element);
        }
        else{
            if(element == head -> key){
                actual = head;
                head = head -> next;
                free(actual);
            }
            else{
                previous = head;
                actual = head -> next;
                while(actual != NULL && actual -> key < element){
                    previous = actual;
                    actual = actual -> next;
                }
                if(actual == NULL || actual -> key > element){
                    printf("The element %d is not in the list\n", element);
                }
                else{
                    previous -> next = actual -> next;
                    free(actual);
                }
            }
        }
        
    }
    return head;
}


int main() {

    int element, n, idElement;
    long long int result;
    struct node *head;

    while(scanf("%d", &n) && (n > 0)) {

        head = NULL;
        result = 0;

        for(idElement = 1; idElement <= n; idElement++) {
            scanf("%d", &element);
            head = InsertElementInAscendantLinkedList(head, element);
        }

        while(head ->next != NULL){
            element = head -> key;
            head = DeleteElementOfAscentantLinkedList(head, element);
            element += head -> key;
            head = DeleteElementOfAscentantLinkedList(head, head -> key);
            result += element;
            head = InsertElementInAscendantLinkedList(head, element);
        }
        printf("%lld\n", result);
    }

    return 0;
}