#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    struct node *next;
};

struct node *makeList(int n){
    struct node *head = NULL, *newNode;
    while(n >= 1){
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->key = n;
        newNode->next = head;
        head = newNode;
        n--;
    }
    return head;
}

void printLuckyPositions(struct node *head) {
    struct node *current = head;
    if(current == head){
        printf("%d", current->key);
        current = current->next;
    }
    while (current != NULL) {
        printf(" %d", current->key);
        current = current->next;
    }
    printf("\n");
}

struct node *deletePositions(struct node *head, int card_value, int *amount_soldiers, int lucky_spots) {
    struct node *current = head, *prev = NULL;
    int delete_amount, id_Delete, id_Position;

    if(*amount_soldiers >= card_value){
        if(*amount_soldiers > lucky_spots){
            if(card_value == 1){

                delete_amount = *amount_soldiers - lucky_spots;

                for(id_Delete = 1; id_Delete <= delete_amount; id_Delete++){
                    head = head->next;
                    free(current);
                    current = head;
                    (*amount_soldiers)--;
                }
            }else{

                delete_amount = *amount_soldiers / card_value;

                if( (*amount_soldiers - delete_amount) < lucky_spots){
                    delete_amount = *amount_soldiers - lucky_spots;
                }
                
                for(id_Delete = 0; id_Delete < delete_amount; id_Delete++){
                    for(id_Position = 1; id_Position < card_value; id_Position++){
                        prev = current;
                        current = current->next;  
                    }
                    prev->next = current->next;
                    free(current);
                    current = prev->next;
                    (*amount_soldiers)--;
                }                
            }
        }
    }
    return head;
}

struct node *delete_list(struct node *head){
    struct node *current = head, *next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    return NULL;
}
int main() {
    int t = 0;
    int amount_soldiers, lucky_spots, idCard;
    struct node *head;

    
    // Mientras existan selecciones
    while (scanf("%d %d", &amount_soldiers, &lucky_spots) != EOF) {
        // Leer el numero de soldados y puntos de suerte
        // Crear la lista enlazada simple
        head = makeList(amount_soldiers);

        int card_values[20];

        // Leer los 20 valores de las cartas
        for (int i = 0; i < 20; i++) {
            scanf("%d", &card_values[i]);
        }

        // Proceso de eliminacion de soldados hasta que queden "lucky_spots"
        int card_index = 0;
        for (idCard = 0; idCard < 20; idCard++) {
            head = deletePositions(head, card_values[card_index], &amount_soldiers, lucky_spots);
            card_index++;
        }

        // Imprimir la seleccion actual
        t++;
        printf("Selection #%d\n", t);
        printLuckyPositions(head);
        delete_list(head);
        printf("\n");
    }

    return 0;
}