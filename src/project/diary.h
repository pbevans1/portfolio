#ifndef __DIARY__H
#define __DIARY__H
#include "../library/customString.h"
#include "products.h"

typedef struct __entry {
    string* username;
    string* productName;
    Product* product;
    string* date;
    double servings;
    struct __entry* next;
    struct __entry* prev;
} entry;








#endif