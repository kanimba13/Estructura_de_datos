#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RED 1
#define BLACK 0
#define NILKey -2147483647
#define MAXT 200001

struct nodeRBTree {
    int key;
    int color;
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *p;
};

void InorderTreeWalk(struct nodeRBTree *x) {
    if (x->key != NILKey) {
        InorderTreeWalk(x->left);
        if (x->color == BLACK)
            printf("(%d, BLACK) ", x->key);
        else
            printf("(%d, RED) ", x->key);
        InorderTreeWalk(x->right);
    }
}

struct nodeRBTree *TreeSearch(struct nodeRBTree *x, int k) {
    while ((x->key != NILKey) && (k != x->key)) {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

struct nodeRBTree *TreeMinimum(struct nodeRBTree *x) {
    while (x->left->key != NILKey)
        x = x->left;
    return x;
}

struct nodeRBTree *TreeMaximum(struct nodeRBTree *x) {
    while (x->right->key != NILKey)
        x = x->right;
    return x;
}

struct nodeRBTree *TreeSuccessor(struct nodeRBTree *x) {
    struct nodeRBTree *y;
    if (x->right->key != NILKey)
        return TreeMinimum(x->right);
    y = x->p;
    while ((y->key != NILKey) && (x == y->right)) {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *TreePredecessor(struct nodeRBTree *x) {
    struct nodeRBTree *y;
    if (x->left->key != NILKey)
        return TreeMaximum(x->left);
    y = x->p;
    while ((y->key != NILKey) && (x == y->left)) {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *y;
    y = x->right;
    x->right = y->left;
    y->left->p = x;
    y->p = x->p;
    if (x->p->key == NILKey)
        T = y;
    else {
        if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
    }
    y->left = x;
    x->p = y;
    return T;
}

struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *y;
    y = x->left;
    x->left = y->right;
    y->right->p = x;
    y->p = x->p;
    if (x->p->key == NILKey)
        T = y;
    else {
        if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
    }
    y->right = x;
    x->p = y;
    return T;
}

struct nodeRBTree *AssignNilLeaf() {
    struct nodeRBTree *w;
    w = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    w->color = BLACK;
    w->key = NILKey;
    w->left = NULL;
    w->right = NULL;
    return w;
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

struct nodeRBTree *RB_Insert(struct nodeRBTree *T, int k) {
    struct nodeRBTree *x, *y, *z;
    z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    z->color = RED;
    z->key = k;
    z->left = AssignNilLeaf();
    z->left->p = z;
    z->right = AssignNilLeaf();
    z->right->p = z;
    y = (T->key != NILKey) ? T->p : T;
    x = T;
    while (x->key != NILKey) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y->key == NILKey)
        T = z; /* Empty tree. */
    else {
        free(x);
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
    T = RB_InsertFixup(T, z);
    return T;
}

struct nodeRBTree *RB_DeleteFixup(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *w;
    while ((x != T) && (x->color == BLACK)) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                T = LeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    T = RightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                T = LeftRotate(T, x->p);
                x = T;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                T = RightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    T = LeftRotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                T = RightRotate(T, x->p);
                x = T;
            }
        }
    }
    x->color = BLACK;
    return T;
}

struct nodeRBTree *RB_Delete(struct nodeRBTree *T, struct nodeRBTree *z) {
    struct nodeRBTree *x, *y;
    y = ((z->left->key == NILKey) || (z->right->key == NILKey)) ? z : TreeSuccessor(z);
    x = (y->left->key != NILKey) ? y->left : y->right;
    x->p = y->p;
    if (y->p->key == NILKey)
        T = x;
    else {
        if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
    }
    if (y != z)
        z->key = y->key;
        /* Copy all information fields from y to z. */
    if (y->color == BLACK)
        T = RB_DeleteFixup(T, x);
    free(y);
    return T;
}

int main() {
    
    int n, m, n_index, m_index, actual, puntaje_maximo, puntaje_actual, contador;
    struct nodeRBTree *T;
    T = AssignNilLeaf();
    puntaje_maximo = 0;
    puntaje_actual = 0;

    scanf("%d %d", &n, &m);
    int V[n + 1];

    for (int i = 1; i <= n; i++)
        scanf("%d", &V[i]);
    
    contador = 1;
    
    for (n_index = 1; n_index <= n; n_index++)
    {
        if (n == 1)
            break;
        
        actual = V[n_index];
        if(n_index == 1)
        {
            for (m_index = contador; m_index <= m; m_index++)
                {
                    if (n_index + m_index > n)
                        break;
                    T = RB_Insert(T, V[n_index + m_index]);
                }
            contador = m_index;
        }
        else if (n_index + m <= n)
        {
            T = RB_Insert(T, V[n_index + m]);
            T = RB_Delete(T, TreeSearch(T, V[n_index]));      
        }
        else
        {
            T = RB_Delete(T, TreeSearch(T, V[n_index]));
        }
        if(T->key != NILKey)
            puntaje_actual = TreeMaximum(T)->key - actual;

        if (puntaje_actual > puntaje_maximo)
            puntaje_maximo = puntaje_actual;
    }

    printf("%d\n", puntaje_maximo);
    return 0;
}