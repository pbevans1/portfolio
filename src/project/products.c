

#ifndef __PRODUCTS__C
#define __PRODUCTS__C

#include "products.h"


Product* getProductFromString(char* line) {
    Product* product = malloc(sizeof(Product));
    char* nextField;
    const char* delimiter = "~";

    // Read product number
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->product_id = atoi(nextField);
    } else {
        product->product_id = -1;
    }

    // Read product name
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    uppercase(nextField);
    product->name = strFrom(nextField);

    // Read product manufacturer
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    uppercase(nextField);
    product->manufacturer = strFrom(nextField);

    // Read calories
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->energy_units = atof(nextField);
    } else {
        product->energy_units = 0.0;
    }

    // Read carbs
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->carb_units = atof(nextField);
    } else {
        product->carb_units = 0.0;
    }

    // Read fat
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->fat_units = atof(nextField);
    } else {
        product->fat_units = 0.0;
    }

    // Read protein
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->protein_units = atof(nextField);
    } else {
        product->protein_units = 0.0;
    }

    // Read size in grams or ml
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->ml_g_size = atof(nextField);
    } else {
        product->ml_g_size = 0.0;
    }

    // Read gram or ml label
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    strncpy(product->ml_g, nextField, 2);
    product->ml_g[2] = '\0';

    // Read household serving size
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
    if (strlen(nextField)) {
        product->serving_size = atoi(nextField);
    } else {
        product->serving_size = 0.0;
    }
    
    // Read household serving units
    nextField = mystrsep(&line, delimiter);
    if (nextField == NULL) return NULL;
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
