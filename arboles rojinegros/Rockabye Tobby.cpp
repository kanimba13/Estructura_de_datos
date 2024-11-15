#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0
#define NILKey -2147483647


struct nodeRBTree *NIL;

struct nodeRBTree {
    int key;            
    int period;         
    int color;
    int index;          
    char name[16];      
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *p;
};


void InitializeNILNode() {
    NIL = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    NIL->color = BLACK;
    NIL->key = NILKey;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->p = NULL;
}


struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NIL) {
        T = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    return T;
}


struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == NIL) {
        T = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
    return T;
}


struct nodeRBTree *RB_InsertFixup(struct nodeRBTree *T, struct nodeRBTree *z) {
    struct nodeRBTree *y;
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    T = LeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                T = RightRotate(T, z->p->p);
            }
        } else {
            y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    T = RightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                T = LeftRotate(T, z->p->p);
            }
        }
    }
    T->color = BLACK;
    return T;
}


struct nodeRBTree *RB_Insert(struct nodeRBTree *T, int key, int period, char *name, int index) {
    struct nodeRBTree *x, *y, *z;
    z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    z->color = RED;
    z->key = key;
    z->period = period;
    z->index = index;  
    strcpy(z->name, name);
    z->left = NIL;
    z->right = NIL;
    z->p = NIL;

    y = NIL;
    x = T;

    
    while (x != NIL) {
        y = x;
        if (z->key < x->key || (z->key == x->key && z->index < x->index)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;

    if (y == NIL) {
        T = z;  
    } else {
        if (z->key < y->key || (z->key == y->key && z->index < y->index)) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    T = RB_InsertFixup(T, z);
    return T;
}


struct nodeRBTree *TreeMinimum(struct nodeRBTree *x) {
    while (x->left != NIL) {
        x = x->left;
    }
    return x;
}

// Encuentra el sucesor de un nodo
struct nodeRBTree *TreeSuccessor(struct nodeRBTree *x) {
    struct nodeRBTree *y;
    if (x->right != NIL) {
        return TreeMinimum(x->right);
    }
    y = x->p;
    while (y != NIL && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

int main() {
    InitializeNILNode();  

    int t;
    scanf("%d", &t);

    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);

        struct nodeRBTree *T = NIL;  

        
        for (int i = 0; i < n; i++) {
            char name[16];
            int period;
            scanf("%s %d", name, &period);
            T = RB_Insert(T, period, period, name, i);  
        }

        struct nodeRBTree *current = TreeMinimum(T);

        
        for (int i = 0; i < k; i++) {
            if (current != NIL) {
                printf("%d %s\n", current->key, current->name);
                int new_key = current->key + current->period;  
                T = RB_Insert(T, new_key, current->period, current->name, current->index);  
                current = TreeSuccessor(current);  
            }
        }
    }

    return 0;
}
