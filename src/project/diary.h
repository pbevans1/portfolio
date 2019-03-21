#ifndef __DIARY__H
#define __DIARY__H
#include "../library/customString.h"
#include "products.h"
#include "stdlib.h"
#include "../library/avlTree.h"

typedef struct __entry {
    int isDeleted;
    string* key;
    string* date;
    string* productName;
    Product* product;
    double servings;
} entry;

entry* newEntry(string*, string*, double, struct Node*);
char* formatEntry(entry*);
void swapEntriesAt(vector*, int, int);
void insertIntoDiary(vector*, entry*);
int binarySearchDiary(vector* diary, string* key, int low, int high);
entry* entryFromString(char*, struct Node*);
#endif