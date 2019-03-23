#include "serving.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define GDSN 0
#define LI 1
#define UNKNOWN 2

#ifndef __SERVING__C
#define __SERVING__C

Serving* getServingFromString(char* buffer) {
    Serving* serving = malloc(sizeof(Serving));
    char* nextField;
    const char* delimiter = "\",\"";

    nextField = strtokm(buffer, delimiter);
    ++nextField; //remove leading quote
    // printf("\n\n\n\n%s\n", nextField);
    if (strlen(nextField)) {
        serving->NDB_Number = atoi(nextField);
    } else {
        serving->NDB_Number = -1;
    }

    nextField = strtokm(NULL, delimiter);
    if (strlen(nextField)) {
        serving->servingSize = atoi(nextField);
    } else {
        serving->servingSize = -1;
    }

    nextField = strtokm(NULL, delimiter);
    serving->regUnit= strFrom(nextField);


    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    if (strlen(nextField)) {
        serving->houseServingSize = atoi(nextField);
    } else {
        serving->houseServingSize = -1;
    }

    nextField = strtokm(NULL, delimiter);
    // printf("%s\n", nextField);
    serving->houseUnit = strFrom(nextField);



    
    return serving;
    
}

void prettyPrintServing(Serving* serving) {
    if (serving == NULL) return;
    // printf("Name: "); printStr(product->name); printf("\n");
    // printf("\tManufacturer: "); printStr(product->manufacturer); printf("\n");
    printf("\nNDB Number: %d\n", serving->NDB_Number);
    // printf("\tUPC: %d\n", product->gtin_upc);
    // printf("\tAvailable: %s\n", product->date_available);
    // printf("\tModified: %s\n", product->date_modified);
    // printf("\tIngredients: "); printStr(product->ingredients); printf("\n");
}

#endif 
