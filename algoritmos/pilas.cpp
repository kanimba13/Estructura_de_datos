#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0

struct node
{
    int key;
    struct node *next;
};

struct node *Push (struct node *top, int element)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;
    newNode->next = top;
    top = newNode;

    return top;
}

int Pop (struct node **top)
{
    struct node *current;
    int element = myInfinite;
    if(*top == NULL)
    {
        printf("Error: empty stack\n");
    }
    else
    {
        element = (*top)->key;
        current = *top;
        *top = (*top)->next;
        free(current);
    }

    return element;
}

int isEmptyStack (struct node *top)
{
    return top == NULL ? TRUE : FALSE;
}

void PrintStack (struct node *top)
{
    struct node *current;
    current = top;
    while(current != NULL)
    {
        printf("%d -> ", current->key);
        current = current->next;
    }
    printf("NULL\n");
}

int main (){
    struct node *top = NULL;
    int element, operation;
    while(scanf("%d", &operation) != EOF)
    {
        if(operation == 1)//Push
        {
            scanf("%d", &element);
            top = Push(top, element);
            PrintStack(top);
        }
        else if(operation == 2)//Pop
        {
            element = Pop(&top);
            if(element != myInfinite)
                printf("Element popped: %d\n", element);
        }
        else {
            printf("Invalid operation\n 1: Push\n 2: Pop\n");
        }
    }
    return 0;
}