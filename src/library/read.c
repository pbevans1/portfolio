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
    char buffer[1000];
    fgets(buffer, 1000, fp); // read header row
    fgets(buffer, 1000, fp); // read first data row
    vector* products = newVector();
    printf("%s\n", buffer);
    // fgets(buffer, 1000, fp);
    Product* firstProd = getProductFromString(buffer);
    printf("\nRead: %s\n", firstProd->name->contents);
    // printf("Pushing..\n");
    pushToVec(products, firstProd);
    // firstProd = getProductFromString(buffer);
    // pushToVec(products, firstProd);
    // firstProd = getProductFromString(buffer);
    // pushToVec(products, firstProd);
    int count = 0;
    // printf("%d ", count++);

    // while (fgets(buffer, 1000, fp)) {
    //     printf("%d", count++);
    //     pushToVec(products, getProductFromString(buffer));
    // }
    return products;
}
#endif