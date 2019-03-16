#include "../library/customString.h"

#ifndef __PRODUCTS__H 
#define __PRODUCTS__H 

enum units {
    g = 0,
    ml =  1,
    UNKNOWN = 2,
};

// typedef struct __product {
//     int NDB_Number;
//     string* name;
//     int source;
//     int gtin_upc;
//     string* manufacturer;
//     char date_modified[11];
//     char date_available[11];
//     string* ingredients;
    
// } Product;

typedef struct __product {
    int product_id;
    string* name;
    string* manufacturer;
    double energy_units;
    double carb_units;
    double fat_units;
    double protein_units;
    double ml_g_size;
    char ml_g[3];
    double serving_size;
    string* serving_units;
    
} Product;

Product* getProductFromString(char*);
char *strtokm(char*, const char*);
void prettyPrintProduct(Product*);

#endif