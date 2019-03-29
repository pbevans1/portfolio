
#ifndef __READ_CUST_C
#define __READ_CUST_C
#include "read.h"

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
        Product* prod = getProductFromString(line);
        if (prod == NULL) continue;
        products = insert(products, prod);
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

vector* readDiary(char* username, struct Node* productRoot) {
    vector* diary = newVector();
    char location[100] = {'\0'};
    const int BUFFER_SIZE = 9000;
    char buffer[BUFFER_SIZE];
    char *line;
   
    strcpy(location, "data/");
    strcat(location, username);
    strcat(location, ".log");

    FILE* fp;
    fp = fopen(location, "r");
    if (fp == NULL) return diary;
    
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        line = buffer;
        if (strncmp(line, "~~~", 4) == 0) continue;
        entry* new = entryFromString(line, productRoot);
        if (new == NULL) continue;
        insertIntoDiary(diary, new);
    }
    
    fclose(fp);
    return diary;
}


#endif
