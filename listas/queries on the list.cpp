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

struct node * DeleteElementOfAscentantLinkedList(struct node *head, int element, int **size){
    struct node *previous, *actual;
    if(head == NULL){
        return head;
    }
    else{
        if(element < head ->key){
            printf("", element);
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
                    return head;
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

void solution(struct node *head, int operation, int *size){
    int element, med1, med2, result;
    struct node *current;
    if(operation == 1){
        scanf("%d", &element);
        head = InsertElementInAscendantLinkedList(head, element);
        (*size)++;
    }
    else if(operation == 2){
        scanf("%d", &element);
        head = DeleteElementOfAscentantLinkedList(head, element, &size);
    }
    else{
        if(*size == 0){
            printf("Empty!\n");
        }
        else if(*size % 2 == 0){
            med1 = *size / 2;
            med2 = med1 + 1;
            current = head;
            for(int i = 1; i < med1; i++){
                current = current -> next;
            }
            result = current -> key;
            current = current -> next;
            result += current -> key;
            printf("%d\n", result / 2);
        }
        else{
            med1 = *size / 2;
            current = head;
            for(int i = 1; i <= med1; i++){
                current = current -> next;
            }
            printf("%d\n", current -> key);
        }
    }   
}


int main() {
    struct node *head;
    head = NULL;
    int operation, size, Q;
    size = 0;
    scanf("%d", &Q);
    for(int i = 1; i <= Q; i++){
        scanf("%d", &operation);
        solution(head, operation, &size);
    }
    return 0;
}