#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int key;
    struct node *left, *right, *parent;
};

struct node *treeParent (struct node *root, int key)
{
    struct node *current = root;
    struct node *prev = NULL;
    while (current != NULL)
    {
        prev = current;
        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return prev;
}

struct node *treeRigth (struct node *root)
{
    struct node *current = root;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

struct node *treeLeft (struct node *root)
{
    struct node *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct node *treeMinimum (struct node *root)
{
    struct node *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct node *treeMaximum (struct node *root)
{
    struct node *current = root;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

struct node *treeSucesor(struct node *root, int key)
{
    struct node *current = treeParent(root, key);
    if (current == NULL)
    {
        return NULL;
    }
    if (current->right != NULL)
    {
        return treeMinimum(current->right);
    }
    struct node *prev = current->parent;
    while (prev != NULL && current == prev->right)
    {
        current = prev;
        prev = prev->parent;
    }
    return prev;
}

struct node *treePredecesor(struct node *root, int key)
{
    struct node *current = treeParent(root, key);
    if (current == NULL)
    {
        return NULL;
    }
    if (current->left != NULL)
    {
        return treeMaximum(current->left);
    }
    struct node *prev = current->parent;
    while (prev != NULL && current == prev->left)
    {
        current = prev;
        prev = prev->parent;
    }
    return prev;
}

struct node *treeInsert (struct node *root, int key)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    if (root == NULL)
    {
        return newNode;
    }
    struct node *prev = treeParent(root, key);
    if (key < prev->key)
    {
        prev->left = newNode;
    }
    else
    {
        prev->right = newNode;
    }
    newNode->parent = prev;
    return root;
}

int deleteElement(int key){

}
