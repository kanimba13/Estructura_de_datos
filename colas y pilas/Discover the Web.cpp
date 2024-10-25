#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define myInfinite NULL
#define TRUE 1
#define FALSE 0

struct node
{
    char key[100]; // Cambiamos a un array de caracteres (string)
    struct node *next;
};

struct node *Push(struct node *top, char *element)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->key, element); // Guardamos el string en el nuevo nodo
    newNode->next = top;
    top = newNode;

    return top;
}

char *Pop(struct node **top)
{
    struct node *current;
    char *element = NULL;
    if (*top == NULL)
    {
        printf("Error: empty stack\n");
    }
    else
    {
        element = (char*)malloc(100);
        strcpy(element, (*top)->key);
        current = *top;
        *top = (*top)->next;
        free(current);
    }

    return element;
}

struct node *cleanPile(struct node *top)
{
    struct node *current;
    while (top != NULL)
    {
        current = top;
        top = top->next;
        free(current);
    }
    return top;
}

int isEmptyStack(struct node *top)
{
    return top == NULL ? TRUE : FALSE;
}

int main()
{
    struct node *back = NULL, *forward = NULL;
    int amount_cases, i = 1;
    char element[100], operation[100];
    scanf("%d", &amount_cases);
    while (i <= amount_cases)
    {
        back = Push(back, "http://www.lightoj.com/");
        printf("Case %d:\n", i);
        while(1){

            scanf("%s", operation);

            if (strcmp(operation, "VISIT") == 0) // Push
            {
                scanf("%s", element);
                back = Push(back, element);
                printf("%s\n", back->key);
                forward = cleanPile(forward);
            }
            else if (strcmp(operation, "BACK") == 0) // Pop
            { 
                if (strcmp(back->key, "http://www.lightoj.com/") == 0)
                    printf("Ignored\n");
                else{
                    forward = Push(forward, Pop(&back));
                    printf("%s\n", back->key);
                }
                    
            }
            else if(strcmp(operation, "FORWARD") == 0)
            {
                if(forward == NULL)
                    printf("Ignored\n");
                else
                {
                    back = Push(back, Pop(&forward));
                    printf("%s\n", back->key);
                }
            }
            else if(strcmp(operation, "QUIT") == 0){ // Exit
                break;
            }
        }
        i++;
        back = cleanPile(back);
        forward = cleanPile(forward);
    }
    return 0;
}
