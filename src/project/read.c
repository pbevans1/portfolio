#include "read.h"
#include "../project/products.h"
#include "../project/serving.h"
#include<string.h>


#ifndef __READ_CUST_C
#define __READ_CUST_C

struct Node* readProductFile(char location[]) {
    FILE* fp = fopen(location, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    const int BUFFER_SIZE = 9000;
    char buffer[BUFFER_SIZE];
    struct Node* products = NULL;
    char *line;
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        line = buffer;
        products = insert(products, getProductFromString(buffer));
    }
    fclose(fp);

    return products;
}

int logFileExists(char* username) {
    char location[100] = {'\0'};
    strcpy(location, "data/");
    strcat(location, username);
    strcat(location, ".log");
    // printf("Looking in: %s\n", location);
    FILE* logFile;
    logFile = fopen(location, "r");
    if (logFile == NULL) return 0;
    fclose(logFile);
    return 1;
}

int fileExists(char* filename) {
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) return 0;
    fclose(file);
    return 1;
}

void readDiary(char* username) {
    
}


#endif