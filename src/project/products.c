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
    Product* product = malloc(sizeof(product));
    char* nextField;
    const char* delimiter = "\",\"";

    nextField = strtokm(buffer, delimiter);
    ++nextField; //remove leading quote
    printf("\n\n\n\n%s\n", nextField);
    if (strlen(nextField)) {
        product->NDB_Number = atoi(nextField);
    } else {
        product->NDB_Number = -1;
    }

    nextField = strtokm(NULL, delimiter);
    printf("Raw: %s\n", nextField);
    product->name = strFrom(nextField);
    printf("Line 26: "); printStr(product->name); printf("\n");
    printf("Line 27: "); printStr(product->name); printf("\n");


    nextField = strtokm(NULL, delimiter);
    printf("Line 31: "); printStr(product->name); printf("\n");
    // printf("%s\n", nextField);
    if (strcmp(nextField, "LI") == 0) {
        printf("Line 34: "); printStr(product->name); printf("\n");
        printf("source: %p\n", &(product->source));
        printf("name:  %p\n", &(product->name));
        printf("name contents:  %p\n", &(product->name->contents));
        product->source = LI;
        printf("name contents after:  %p\n", &(product->name->contents));
        printf("Line 36: "); printStr(product->name); printf("\n");
        
    } else if (strcmp(nextField, "GDSN") == 0) {
        printf("Line 38: "); printStr(product->name); printf("\n");
        product->source = GDSN;
    } else {
        printf("Line 41: "); printStr(product->name); printf("\n");
        product->source = UNKNOWN;
    }
    printf("Line 44: "); printStr(product->name); printf("\n");


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

    printf("Line 59: "); printStr(product->name); printf("\n");


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
    // printf("%s == \n ", nextField);
    product->ingredients = strFrom(nextField);
    // printf("Constructed! ");
    // printStr(product->ingredients);

    printf("Line 76: "); printStr(product->name); printf("\n");


    return product;
    
}

void prettyPrintProduct(Product* product) {
    printf("Name: "); printStr(product->name); printf("\n");
    printf("\tManufacturer: "); printStr(product->manufacturer); printf("\n");
    printf("\tNDB Number: %d\n", product->NDB_Number);
    printf("\tUPC: %d\n", product->gtin_upc);
    printf("\tAvailable: %s\n", product->date_available);
    printf("\tModified: %s\n", product->date_modified);
    printf("\t"); printStr(product->ingredients); printf("\n");
    

}

// From https://stackoverflow.com/questions/29847915/implementing-strtok-whose-delimiter-has-more-than-one-character
char *strtokm(char *str, const char *delim)
{ 
    static char *tok;
    static char *next;
    char *m;

    if (delim == NULL) return NULL;

    tok = (str) ? str : next;
    if (tok == NULL) return NULL;

    m = strstr(tok, delim);

    if (m) {
        next = m + strlen(delim);
        *m = '\0';
    } else {
        next = NULL;
    }

    return tok;
}

#endif 