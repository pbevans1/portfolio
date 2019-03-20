#include "products.h"
#include "serving.h"
#include "../library/vector.h"
#include<stdio.h>
#include "../library/avlTree.h"



#ifndef __READ_CUST_H
#define __READ_CUST_H

struct Node* readProductFile(char[]);
vector* readServingFile(char[]);
void readDiary(char*);
int logFileExists(char*);
int fileExists(char*);
#endif