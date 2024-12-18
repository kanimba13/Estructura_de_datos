#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0

struct nodeTree
{
    int element;
    struct nodeTree *left;
    struct nodeTree *right;
    struct nodeTree *parent;
};

void inOrderTreeWalk(struct nodeTree *x){
    if(x != NULL){
        inOrderTreeWalk(x->left);
        printf("%d ", x->element);
        inOrderTreeWalk(x->right);
    }
}

struct nodeTree *treeSearch(struct nodeTree *x, int k){
    while((x != NULL) && (k != x->element)){
        if(k < x->element){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return x;
}

struct nodeTree *treeMinimum(struct nodeTree *x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

struct nodeTree *treeMaximum(struct nodeTree *x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

struct nodeTree *treeSuccessor(struct nodeTree *x){
    struct nodeTree *y;
    if(x->right != NULL){
        return treeMinimum(x->right);
    }
    y = x->parent;
    while((y != NULL) && (x == y->right)){
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeTree *treePredecesor(struct nodeTree *x){
    struct nodeTree *y;
    if(x->left != NULL){
        return treeMaximum(x->left);
    }
    y = x->parent;
    while((y != NULL) && (x == y->left)){
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeTree *treeInsert(struct nodeTree *T, int k){
    struct nodeTree *x, *y, *z;
    z = (struct nodeTree *)malloc(sizeof(struct nodeTree));
    z->element = k;
    z->left = NULL; 
    z->right = NULL;
    y = NULL;
    x = T;
    while(x != NULL){
        y = x;
        if(z->element < x->element){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        T = z;
    }else if(z->element < y->element){
        y->left = z;
    }else{
        y->right = z;
    }
    return T;
}

struct nodeTree *treeDelete(struct nodeTree *T, struct nodeTree *z){
    struct nodeTree *x, *y;
    if(z->left == NULL || z->right == NULL){
        y = z;
    }else{
        y = treeSuccessor(z);
    }
    if(y->left != NULL){
        x = y->left;
    }else{
        x = y->right;
    }
    if(x != NULL){
        x->parent = y->parent;
    }
    if(y->parent == NULL){
        T = x;
    }else if(y == y->parent->left){
        y->parent->left = x;
    }else{
        y->parent->right = x;
    }
    if(y != z){
        z->element = y->element;
        // Aqui se pueden copiar los campos de y a z
    }
    free(y);
    return T;
}

int main(){
    struct nodeTree *T = NULL, *x;
    int operation, element;
    while((scanf("%d %d", &operation, &element)) != EOF){
        if(operation == 1){ // Insert in the tree
            T = treeInsert(T, element);
            inOrderTreeWalk(T);
        }else if(operation == 2){ // Delete in the tree
            x = treeSearch(T, element);
            if(x != NULL){
                T = treeDelete(T, x);
            }
            else{
                printf("the element %d is not in the tree\n", element);
            }
            inOrderTreeWalk(T);
        }else{
            printf("Invalid operation\n 1. Insert in the tree\n 2. Delete in the tree\n");
        }
    }
    return 0;
}