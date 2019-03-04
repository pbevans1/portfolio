#include "read.h"
#include "../project/products.h"
#include<string.h>


#ifndef __READ_CUST_C
#define __READ_CUST_C

vector* readProductFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }


    const int BUFFER_SIZE = 5000;
    char buffer[BUFFER_SIZE];
    vector* products = newVector();

    fgets(buffer, BUFFER_SIZE, fp); // read header row
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        pushToVec(products, getProductFromString(buffer));
    }

    return products;
}
#endif