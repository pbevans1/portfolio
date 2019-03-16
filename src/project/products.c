#include "products.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define GDSN 0
#define LI 1
#define UNKNOWN 2

#ifndef __PRODUCTS__C
#define __PRODUCTS__C

Product* getProductFromString(char* line) {
    Product* product = malloc(sizeof(Product));
    char* nextField;
    const char* delimiter = "~";

    
    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->product_id = atoi(nextField);
    } else {
        product->product_id = -1;
    }

    nextField = strsep(&line, delimiter);
    product->name = strFrom(nextField);

    nextField = strsep(&line, delimiter);
    product->manufacturer = strFrom(nextField);

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->energy_units = atof(nextField);
    } else {
        product->energy_units = 0.0;
    }

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->carb_units = atof(nextField);
    } else {
        product->carb_units = 0.0;
    }

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->fat_units = atof(nextField);
    } else {
        product->fat_units = 0.0;
    }

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->protein_units = atof(nextField);
    } else {
        product->protein_units = 0.0;
    }
    // printf("2\n");

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->ml_g_size = atof(nextField);
    } else {
        product->ml_g_size = 0.0;
    }
    // printf("3\n");

    nextField = strsep(&line, delimiter);
    strcpy(product->ml_g, nextField);

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->serving_size = atoi(nextField);
    } else {
        product->serving_size = 0.0;
    }
    
    nextField = strsep(&line, delimiter);
    product->serving_units = strFrom(nextField);

    return product;
    
}

void prettyPrintProduct(Product* product) {
    if (product == NULL) return;
    printf("Name: "); printStr(product->name); printf("\n");
    printf("\tManufacturer: "); printStr(product->manufacturer); printf("\n");
    printf("\tEnergy: %f\n", product->energy_units);
    printf("\tCarbs: %f\n", product->carb_units);
    printf("\tFat: %f\n", product->fat_units);
    printf("\tProtein: %f\n", product->protein_units);
    printf("\tServing Volume: %f %s\n", product->ml_g_size, product->ml_g);
    printf("\tServing Size: %f %s\n", product->serving_size, product->serving_units->contents);
}



#endif 