#include "products.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define GDSN 0
#define LI 1
#define UNKNOWN 2

#ifndef __PRODUCTS__C
#define __PRODUCTS__C

Product* getProductFromString(char* buffer) {
    Product* product = malloc(sizeof(Product));
    char* nextField;
    const char* delimiter = "\",\"";

    nextField = strtokm(buffer, delimiter);
    ++nextField; //remove leading quote
    // printf("\n\n\n\n%s\n", nextField);
    if (strlen(nextField)) {
        product->NDB_Number = atoi(nextField);
    } else {
        product->NDB_Number = -1;
    }

    nextField = strtokm(NULL, delimiter);
    product->name = strFrom(nextField);

    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    if (strcmp(nextField, "LI") == 0) {
        product->source = LI;
        
    } else if (strcmp(nextField, "GDSN") == 0) {
        product->source = GDSN;
    } else {
        product->source = UNKNOWN;
    }


    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    if (strlen(nextField)) {
        product->gtin_upc = atoi(nextField);
    } else {
        product->gtin_upc = -1;
    }

    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    product->manufacturer = strFrom(nextField);



    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    if (strlen(nextField)) {
        strncpy(product->date_modified, nextField, 10);
        product->date_modified[10] = '\0';
    } 

    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    if (strlen(nextField)) {
        strncpy(product->date_available, nextField, 10);
        product->date_available[10] = '\0';
    } 

    nextField = strtokm(NULL, delimiter);
    if (strlen(nextField) > 1) nextField[strlen(nextField) -3] = '\0'; // If there is a string, remove the trailing quote
    product->ingredients = strFrom(nextField);
    // printStr(product->ingredients);


    return product;
    
}

void prettyPrintProduct(Product* product) {
    if (product == NULL) return;
    printf("Name: "); printStr(product->name); printf("\n");
    printf("\tManufacturer: "); printStr(product->manufacturer); printf("\n");
    printf("\tNDB Number: %d\n", product->NDB_Number);
    printf("\tUPC: %d\n", product->gtin_upc);
    printf("\tAvailable: %s\n", product->date_available);
    printf("\tModified: %s\n", product->date_modified);
    printf("\tIngredients: "); printStr(product->ingredients); printf("\n");
}



#endif 