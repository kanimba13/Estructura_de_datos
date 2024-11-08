#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0

struct nodeTree
{
    int key;
    struct nodeTree *left;
    struct nodeTree *right;
    struct nodeTree *parent;
};

void inOrderTreeWalk(struct nodeTree *x){
    if(x != NULL){
        inOrderTreeWalk(x->left);
        printf("%d ", x->key);
        inOrderTreeWalk(x->right);
    }
}

struct nodeTree *treeSearch(struct nodeTree *x, int k){
    while((x != NULL) && (k != x->key)){
        if(k < x->key){
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
    z->key = k;
    z->left = NULL; 
    z->right = NULL;
    y = NULL;
    x = T;
    while(x != NULL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        T = z;
    }else if(z->key < y->key){
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
        z->key = y->key;
        // Aqui se pueden copiar los campos de y a z
    }
    free(y);
    return T;
}

int main(){
    struct nodeTree *T = NULL, *x;
    int n, element, idElement;
    long long int sum;
    while(scanf("%d", &n) && n > 0){
        sum = 0;
        for(int i = 0; i < n; i++){
            scanf("%d", &element);
            T = treeInsert(T, element);
        }
        for(idElement = 1; idElement < n; idElement++){
            x = treeMinimum(T);
            element = x->key;
            T = treeDelete(T, x);
            x = treeMinimum(T);
            element += x->key;
            T = treeDelete(T, x);
            sum += element;
            T = treeInsert(T, element);
        }
        printf("%lld\n", sum);
        free(T);
        T = NULL; 
    }
    return 0;
}