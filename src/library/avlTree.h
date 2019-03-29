

#ifndef __AVL__TREE_H
#define __AVL__TREE_H
#include <string.h>
#include "../project/products.h"
#include "vector.h"
#include<stdio.h> 
#include<stdlib.h> 


struct Result {
    Product* todo;
};

struct Node 
{ 
    char* key;
    Product* product;
    struct Node *left; 
    struct Node *right; 
    struct Node *parent;
    int height; 
}; 


int max(int a, int b); 
int min(int a, int b); 
struct Node* newNode(Product* product);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* root, struct Node* node, Product* prod, struct Result* todo);
void preOrder(struct Node *root);
void inOrder(struct Node *root);
struct Node* findClosestNode(struct Node* root, char* key);
struct Node* predecessor(struct Node *n) ;
struct Node* successor(struct Node *n);
int testAVL();
struct Node* insertWithBrand(struct Node* root, struct Node* node, Product* prod);



#endif
