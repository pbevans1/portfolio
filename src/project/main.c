
#ifndef __MAIN__TRACKER__C
#define __MAIN__TRACKER__C

#include<stdio.h>
#include<stdlib.h>
#include "../library/vector.h"
#include "../library/customString.h"
#include "read.h"
#include "products.h"
#include "mainMenu.h"
#include "../library/avlTree.h"


int main() {
    struct Node* products;
    if (!fileExists("data/food_database.csv")) {
        printf("data/food_database.csv is missing. You can use 'make database' to build it.\n");
        return 1;
    }
    
    products = readProductFile("data/food_database.csv");
    displayMainMenu(products);
 

    return 0;
} 

#endif
