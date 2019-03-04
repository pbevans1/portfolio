

#include<stdio.h>
#include<stdlib.h>
#include "../library/vector.h"
#include "../library/customString.h"
#include "read.h"
#include "products.h"
#include "serving.h"
#include "mainMenu.h"



int main() {
    vector* products = readProductFile("data/Products.csv");
    Product* current;
    vector* servings = readServingFile("data/Serving_size.csv");
    int count = products->size;
    prettyPrintServing((Serving*) popFromVec(servings));
    printf("\n%d\n", servings->size);
    return 0;
} 