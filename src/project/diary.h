#ifndef __DIARY__H
#define __DIARY__H
#include "../library/customString.h"
#include "products.h"
#include "stdlib.h"
#include "../library/avlTree.h"

typedef struct __entry {
    int isDeleted;
    string* date;
    string* username;
    string* productName;
    Product* product;
    double servings;
} entry;

entry* newEntry(string*, string*, string*, int, struct Node*);
char* formatEntry(entry*);
#endif