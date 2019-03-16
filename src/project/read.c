#include "read.h"
#include "../project/products.h"
#include "../project/serving.h"
#include<string.h>


#ifndef __READ_CUST_C
#define __READ_CUST_C

vector* readProductFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }


    const int BUFFER_SIZE = 9000;
    char buffer[BUFFER_SIZE];
    vector* products = newVector();
    int count = 0;
    char *line;
    // fgets(buffer, BUFFER_SIZE, fp); // read header row
    // for (int i = 0; i < 1742; i++) {
    //     fgets(buffer, BUFFER_SIZE, fp);
    //     line = buffer;
    //     printf("%d\n", count++);
    //     pushToVec(products, getProductFromString(line));
    // }
    // fgets(buffer, BUFFER_SIZE, fp);
    // printf("%s", buffer);

    // pushToVec(products, getProductFromString(buffer));
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        line = buffer;
        // printf("%d\n", count++);
        pushToVec(products, getProductFromString(buffer));
    }

    return products;
}

vector* readServingFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    const int BUFFER_SIZE = 5000;
    char buffer[BUFFER_SIZE];
    vector* servings = newVector();

    fgets(buffer, BUFFER_SIZE, fp); // read header row
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        pushToVec(servings, getServingFromString(buffer));
    }

    return servings;
}


#endif