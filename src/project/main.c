

#include<stdio.h>
#include<stdlib.h>
#include "../library/vector.h"
#include "../library/customString.h"
#include "read.h"
#include "products.h"
#include "serving.h"
#include "mainMenu.h"
#include "hashTable.h"
#include "../library/avlTree.h"


int main() {
    // vector* products = readProductFile("data/food_nutrient_db.csv");
    char searchString[500];
    struct Node* products = readProductFile("data/food_nutrient_db.csv");
    printf("Enter an item to look for: ");
    scanf("%s", searchString);
    uppercase(searchString);
    struct Node* bestResult = findClosestNode(products, searchString);
    if (bestResult->key == searchString) {
        prettyPrintProduct(bestResult->product);
    } else {
        printf("We couldn't find anything named '%s'. Did you mean any of these?\n", searchString);
        printf("\t%s\n", bestResult->key);
        printf("\t%s\n", predecessor(bestResult)->key);  
        printf("\t%s\n", successor(bestResult)->key); 

    }

    // printf("Enter a product to search")
    // inOrder(root);
    // testAVL(products); 
    // Product* current; 
    // vector* servings = readServingFile("data/food_nutrient_db.csv");
    // prettyPrintProduct(products->contents[0]);
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