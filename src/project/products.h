#include "../library/customString.h"

#ifndef __PRODUCTS__H 
#define __PRODUCTS__H 

// enum source {
//     GDSN = 0,
//     LI =  1,
//     UNKNOWN = 2,
// };

typedef struct __product {
    int NDB_Number;
    string* name;
    int source;
    int gtin_upc;
    string* manufacturer;
    char date_modified[11];
    char date_available[11];
    string* ingredients;
    
} Product;


Product* getProductFromString(char*);
char *strtokm(char*, const char*);
void prettyPrintProduct(Product*);

#endif