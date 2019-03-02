

#include<stdio.h>
#include<stdlib.h>
#include "../library/vector.h"
#include "../library/customString.h"
#include "../library/read.c"
#include "players.h"
#include "mainMenu.h"



int main() {
    // FILE* fp;
    // fp = fopen("../../data/Products.csv", "r");
    vector* vec = readPlayerFile("data/Products.csv");
    // FILE* fp = fopen("data/Products.csv", "r");
    // if (fp == NULL) {
    //     printf("Error opening file!\n");
    //     return -1;
    // }
    // char buffer[700];
    // fgets(buffer, 700, fp);
    // printf("%s", buffer);

    
    // displayMainMenu();
    return 0;

} 