

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
    string* username = displayMainMenu();
    printStr(username);
    // char searchString[500];
    // struct Node* products = readProductFile("data/food_nutrient_db.csv");
    
    // printf("Enter an item to look for: ");
    // scanf("%s", searchString);
    // uppercase(searchString);
    // struct Node* bestResult = findClosestNode(products, searchString);
    
    
    // if (strcmp(bestResult->key, searchString) == 0) {
    //     prettyPrintProduct(bestResult->product);
    // } else {
    //     printf("We couldn't find anything named '%s'. Did you mean any of these?\n", searchString);
    //     printf("\t%s\n", bestResult->key);
    //     printf("\t%s\n", predecessor(bestResult)->key);  
    //     printf("\t%s\n", successor(bestResult)->key); 
    // }

 

    return 0;
} 