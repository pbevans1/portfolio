#include "read.h"
#include "../project/products.c"
#include<string.h>

#ifndef __READ_CUST_C
#define __READ_CUST_C

vector* readProductFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    char buffer[700];
    fgets(buffer, 700, fp);
    printf("%s", buffer);
    fgets(buffer, 700, fp);
    printf("%s\n\n", buffer);
    Product* firstProd = getProductFromString(buffer);
    // printf("%s\n%s\n", strtok(buffer, ","), strtok(NULL, ","));
    vector* products = newVector();
    pushToVec(products, firstProd);

    // for(int i = 0; i< 2218; i++) {
    
    // while (fgets(buffer, 700, fp)) {
    //     pushToVec(products, getPlayer(buffer));
    // }
    return products;
}
#endif