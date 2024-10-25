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
    int max;
    int min;
};

struct node *Push (struct node *top, int element)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;
    newNode->next = top;
    if(top == NULL)
    {
        newNode->max = element;
        newNode->min = element;
    }
    else
    {
        newNode->max = element > top->max ? element : top->max;
        newNode->min = element < top->min ? element : top->min;
    }
    top = newNode;

    return top;
}

int Pop (struct node **top)
{
    struct node *current;
    int element = myInfinite;
    if(*top != NULL)
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
    int element, operation, numberOfQueries, numberOfElements;
    scanf("%d", &numberOfQueries);
    while(numberOfQueries--)
    {
        struct node *top = NULL;
        scanf("%d", &numberOfElements);
        while(numberOfElements--)
        {
            scanf("%d", &operation);
            if(operation == 1)
            {
                scanf("%d", &element);
                top = Push(top, element);
                
            }
            else if(operation == 2)
            {
                element = Pop(&top);
                
            }
            else if(operation == 3)
            {
                if(isEmptyStack(top) != TRUE)
                {
                    printf("%d\n", top->max - top->min);
                }else{
                    printf("Empty!\n");
                }
            }
        }
    }
    return 0;
}