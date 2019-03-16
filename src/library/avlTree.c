#ifndef __AVL__TREE_C
#define __AVL__TREE_C

#include "avlTree.h"

// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 

  

  
// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
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
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, Product* prod) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(prod)); 
    char* key = prod->name->contents;
  
    if (strcmp(key,  node->key) < 0) {
        node->left  = insert(node->left, prod); 
        node->left->parent = node;
        // printf(" %s left of %s\n", node->)
    }
        
    else if (strcmp(key,  node->key) > 0) {
        node->right = insert(node->right, prod); 
        node->right->parent = node;
    }
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 &&  (strcmp(key, node->left->key) < 0)) // (balance > 1 && key < node->left->key)
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && (strcmp(key, node->right->key) > 0))  //(balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && (strcmp(key, node->left->key) > 0)) // (balance > 1 && key > node->left->key)
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && (strcmp(key, node->right->key) < 0)) //(balance < -1 && key < node->right->key)
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
  
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%s \n", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

// A utility function to print inorder traversal 
// of the tree. 
// The function also prints height of every node 
void inOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        inOrder(root->left); 
        printf("%s \n", root->key);
        inOrder(root->right); 
    } 
} 






// struct Node * minValue(struct Node* node) { 
//   struct Node* current = node; 
   
//   /* loop down to find the leftmost leaf */
//   while (current->left != NULL) { 
//     current = current->left; 
//   } 
//   return current; 
// } 

// struct Node * maxValue(struct Node* node) { 
//   struct Node* current = node; 
   
//   /* loop down to find the leftmost leaf */
//   while (current->right != NULL) { 
//     current = current->right; 
//   } 
//   return current; 
// } 
  
  
// struct Node* successorChild(struct Node *n) 
// { 
//   // step 1 of the above algorithm  
//   if( n->right != NULL ) 
//     return minValue(n->right); 
  
//   // step 2 of the above algorithm 
//   return NULL;
// } 

// struct Node* predChild(struct Node *n) 
// { 
//   // step 1 of the above algorithm  
//   if( n->left != NULL ) 
//     return maxValue(n->right); 
  
//   // step 2 of the above algorithm 
//   return NULL;
// } 

// void checkBSTForward(struct Node *root) {
//     if (root == NULL) return;
//     //FIXME using predecessor/successor
//     struct Node* s = successorChild(root);
//     if (s == NULL) return;
//     if(strcmp(root->key, s->key) > 0) {
//         printf("Error: %s after %s\n", root->key, s->key);
//     } else {
//         printf("Good: %s before %s\n", root->key, s->key);
//     }
//     checkBSTForward(root->left);
//     checkBSTForward(root->right);
//     return;

// }

// void checkBSTback(struct Node *root) {
//     if (root == NULL) return;
//     //FIXME using predecessor/successor
//     struct Node* s = predChild(root);
//     if (s == NULL) return;
//     if(strcmp(root->key, s->key) > 0) {
//         printf("Error: %s before %s\n", root->key, s->key);
//     } else {
//         printf("Good: %s before %s\n", root->key, s->key);
//     }
//     checkBSTback(root->left);
//     checkBSTback(root->right);
//     return;

// }
  
/* Drier program to test above function*/
int testAVL(vector* products)  
{ 
  struct Node *root = NULL; 
  
  /* Constructing tree given in the above figure */
  Product* p;
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p); 
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p); 
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p); 
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p); 
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p); 
  p = (Product*) popFromVec(products);
  printf("Inserting: %s\n", p->name->contents);
  root = insert(root, p);  
  
  /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
  */
  
  printf("Preorder traversal of the constructed AVL"
         " tree is \n"); 
  preOrder(root); 

 printf("\n\nInorder traversal of the constructed AVL"
         " tree is \n"); 
  inOrder(root); 
  
//   checkBSTForward(root);
//   printf("\n");
//   checkBSTback(root);
  return 0; 
}



#endif