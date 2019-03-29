#ifndef __AVL__TREE_C
#define __AVL__TREE_C

#include "avlTree.h"

/*  C program to insert a node in AVL tree */
  
/* A utility function to get the height of the tree */
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
/* A utility function to get maximum of two integers */
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

int min(int a, int b) 
{ 
    return (a < b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(Product* product) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = product->name->contents; 
    node->product = product;
    node->left   = NULL; 
    node->right  = NULL; 
    node->parent = NULL;
    node->height = 1;  /* new node is initially added at leaf */
    return(node); 
} 
  
/* A utility function to right rotate subtree rooted with y 
  See the diagram given above. */
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
  
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    return x; 
} 
  
/* A utility function to left rotate subtree rooted with x 
 See the diagram given above. */
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    /* Perform rotation */
    y->left = x; 
    x->right = T2; 
  
    /*  Update heights */
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    /* Return new root */
    return y; 
} 
  
/* Get Balance factor of node N */
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
/* Recursive function to insert a key in the subtree rooted 
   with node and returns the new root of the subtree. */
//    Modified to compare string keys
struct Node* insert(struct Node* node, Product* prod) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(prod)); 
    char* key = prod->name->contents;
    int keysize = prod->name->size;
    if (strncmp(key,  node->key, keysize + 1) < 0) {
        node->left  = insert(node->left, prod); 
        node->left->parent = node;
        /* printf(" %s left of %s\n", node->) */
    }
        
    else if (strncmp(key,  node->key, keysize + 1) > 0) {
        node->right = insert(node->right, prod); 
        node->right->parent = node;
    }
    else /* Equal keys are not allowed in BST */
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    /*If this node becomes unbalanced, then 
     there are 4 cases */
  
    /*  Left Left Case */
    if (balance > 1 &&  (strncmp(key, node->left->key, keysize + 1) < 0)) /* (balance > 1 && key < node->left->key) */
        return rightRotate(node); 
  
    /* Right Right Case */
    if (balance < -1 && (strncmp(key, node->right->key, keysize + 1) > 0))  /*(balance < -1 && key > node->right->key) */
        return leftRotate(node); 
  
    /* Left Right Case  */
    if (balance > 1 && (strncmp(key, node->left->key, keysize + 1) > 0)) /* (balance > 1 && key > node->left->key) */
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    /* Right Left Case  */
    if (balance < -1 && (strncmp(key, node->right->key, keysize + 1) < 0)) /* (balance < -1 && key < node->right->key)*/
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
  
/* A utility function to print preorder traversal 
  of the tree. 
  The function also prints height of every node */
void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%s \n", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

// Custom - inorder traversal of the tree
void inOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        inOrder(root->left); 
        printf("%s \n", root->key);
        inOrder(root->right); 
    } 
} 


/*Adapted from https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ */
struct Node * minValue(struct Node* node) { 
  struct Node* current = node; 
   
  /* loop down to find the leftmost leaf */
  while (current->left != NULL) { 
    current = current->left; 
  } 
  return current; 
} 

/*Adapted from https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ */
struct Node * maxValue(struct Node* node) { 
  struct Node* current = node; 
   
  /* loop down to find the rightmost leaf */
  while (current->right != NULL) { 
    current = current->right; 
  } 
  return current; 
} 
  
  
/*From https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ */
struct Node* successor(struct Node *n) 
{ 
  if(n == NULL) return NULL;
  /*if n has bigger children, return the smallest*/
  if( n->right != NULL ) 
    return minValue(n->right); 
  

  /*Otherwise, travel up the tree until you find a left child or the root. Return it*/
  struct Node *p = n->parent; 
  while(p != NULL && n == p->right) 
  { 
     n = p; 
     p = p->parent; 
  } 
  return p; 
} 

/*Adapted from https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ */
struct Node* predecessor(struct Node *n) 
{ 
  if(n == NULL) return NULL;
  /*if n has smaller children, return the biggest*/
  if( n->left != NULL ) 
    return maxValue(n->left); 
  
  /* Otherwise, travel up the tree until you find a right child or the root. Return it */
  struct Node *p = n->parent; 
  while(p != NULL && n == p->left) 
  { 
     n = p; 
     p = p->parent; 
  } 
  return p; 
} 

// Custom
struct Node* findClosestNode(struct Node* root, char* key) {
    if (root == NULL) return NULL;
    int keysize = strlen(key);
    // if ((strncmp(key, root->key, keysize) == 0)) return root;
    if ((strncmp(key, root->key, keysize + 1) == 0) && strlen(root->key) == keysize) return root;
    if (strncmp(key, root->key, keysize + 1) <= 0) {
        //search left
        if (root->left == NULL) return root;
        return findClosestNode(root->left, key);
    }
    else {
        if (root->right == NULL) return root;
        return findClosestNode(root->right, key);
    }
}


#endif
