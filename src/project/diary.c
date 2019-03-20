#ifndef __DIARY__C
#define __DIARY__C
#include "diary.h"

entry* newEntry(string* username, string* productName, string* date, int numServings, struct Node* root) {
    
    struct Node* productNode = findClosestNode(root, productName->contents);
    Product* closestProduct = productNode->product;
    if (!strEquals(closestProduct->name, productName)) {
        return NULL;
    }
    entry* new = malloc(sizeof(entry));
    new->isDeleted = 0;
    new->date = date;
    new->username = username;
    new->productName = productName;
    new->product = closestProduct;
    new->servings = numServings;
    return new;
}

char* formatEntry(entry* ent) {
    char name[50];
    strcpy(name, ent->productName->contents);
    return name;
}

void freeEntry(entry* ent) {
    freeStr(ent->productName);
    freeStr(ent->username);
    freeStr(ent->date);
    free(ent);
}







#endif