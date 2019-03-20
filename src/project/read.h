#ifndef __READ_CUST_H
#define __READ_CUST_H

#include "products.h"
#include "serving.h"
#include "../library/vector.h"
#include<stdio.h>
#include "../library/avlTree.h"
#include "diary.h"

struct Node* readProductFile(char[]);
vector* readServingFile(char[]);
entry* readDiary(char*);
int logFileExists(char*);
int fileExists(char*);
#endif