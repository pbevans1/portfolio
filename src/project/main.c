
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


int main(int argc, char** argv) {
    struct Node* products;
    if (!fileExists("data/food_database.csv")) {
        printf("data/food_database.csv is missing. You can use 'make database' to build it.\n");
        return 1;
    }
    if (argc > 1) {
        printf("Help:\n");
        printf("\tGeneral: To use the program, type 'make run' and follow the directions on screen. You should use keyboard and mouse to navigate.\n");
        printf("\tQuitting: The exit button is in the top left corner.\n");
        printf("\tUsername: If you've forgotten your username try 'make list-users'\n");
        return 2;
    }
    //Read products into AVL tree
    products = readProductFile("data/food_database.csv");
    if (products == NULL) {
        printf("data/food_database.csv has no valid entries. You can use 'make database' to rebuild it.\n");
        return 1;
    }
    // Enter menu
    displayMainMenu(products);
 

    return 0;
} 

#endif
