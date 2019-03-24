

#ifndef __PRODUCTS__C
#define __PRODUCTS__C
#define GDSN 0
#define LI 1
#define UNKNOWN 2

#include "products.h"


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

    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        product->ml_g_size = atof(nextField);
    } else {
        product->ml_g_size = 0.0;
    }

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

double gramsCaloriesPerServing(Product* product) {
    double portionSizeAdjustment = product->ml_g_size / 100.0;
    return product->energy_units * portionSizeAdjustment;
}

double gramsProteinPerServing(Product* product) {
    double portionSizeAdjustment = product->ml_g_size / 100.0;
    return product->protein_units * portionSizeAdjustment;
}

double gramsFatPerServing(Product* product) {
    double portionSizeAdjustment = product->ml_g_size / 100.0;
    return product->fat_units * portionSizeAdjustment;
}

double gramsCarbsPerServing(Product* product) {
    double portionSizeAdjustment = product->ml_g_size / 100.0;
    return product->carb_units * portionSizeAdjustment;
}

void prettyPrintProduct(Product* product) {
    if (product == NULL) return;
    printf("Name: "); printStr(product->name); printf("\n");
    printf("\tManufacturer: "); printStr(product->manufacturer); printf("\n");
    printf("\tEnergy: %.1f\n", product->energy_units);
    printf("\tCarbs: %.1f\n", product->carb_units);
    printf("\tFat: %.1f\n", product->fat_units);
    printf("\tProtein: %.1f\n", product->protein_units);
    printf("\tServing Volume: %.1f %s\n", product->ml_g_size, product->ml_g);
    printf("\tServing Size: %.1f %s\n", product->serving_size, product->serving_units->contents);
}



#endif 
