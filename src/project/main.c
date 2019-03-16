

#include<stdio.h>
#include<stdlib.h>
#include "../library/vector.h"
#include "../library/customString.h"
#include "read.h"
#include "products.h"
#include "serving.h"
#include "mainMenu.h"
#include "hashTable.h"



int main() {
    vector* products = readProductFile("data/food_nutrient_db.csv");
    // Product* current;
    // vector* servings = readServingFile("data/food_nutrient_db.csv");
    prettyPrintProduct(products->contents[0]);
    // printf("\n%d\n", servings->size);
    // int count = products->size;
    // hashTable* servingInfo = servingTableFrom(servings);
    // prettyPrintServing((Serving*) popFromVec(servings));

    // printf("\n%d\n", servingInfo->size);

    // Serving* test = malloc(sizeof(Serving));
    // unsigned long testhash = hashServing(test);
    // insertServingHash(servingInfo, testhash, test);
    // printf("\n%d\n", servingInfo->size);  
 

    return 0;
} 