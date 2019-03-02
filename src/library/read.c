#include "read.h"

#ifndef __READ_CUST_C
#define __READ_CUST_C

vector* readPlayerFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    char buffer[700];
    fgets(buffer, 700, fp);
    printf("%s", buffer);
    vector* products = newVector();
    // for(int i = 0; i< 2218; i++) {
    
    // while (fgets(buffer, 700, fp)) {
    //     pushToVec(products, getPlayer(buffer));
    // }
    return products;
}
#endif