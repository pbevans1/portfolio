#ifndef __DIARY__C
#define __DIARY__C
#include "diary.h"

entry* newEntry(string* productName, string* date, double numServings, struct Node* root) {
    
    struct Node* productNode = findClosestNode(root, productName->contents);
    Product* closestProduct = productNode->product;
    if (!strEquals(closestProduct->name, productName)) {
        return NULL;
    }
    entry* new = malloc(sizeof(entry));
    new->isDeleted = 0;
    new->date = date;
    // new->username = username;
    new->productName = productName;
    new->product = closestProduct;
    new->servings = numServings;
    new->key = joinStr(date, productName, ": ");
    return new;
}
entry* entryFromProduct(Product* prod, string* date, double numServings) {
    entry* new = malloc(sizeof(entry));
    new->product = prod;
    new->isDeleted = 0;
    new->date = date;
    new->productName = copyStr(prod->name);
    new->servings = numServings;
    new->key = joinStr(new->date, new->product->name, ": ");
    return new;
}


char* formatEntry(entry* ent) {
    char* name = malloc(sizeof(char) * (400));
    sprintf(name, "%s: %.1f servings of %s", ent->date->contents, ent->servings, ent->product->name->contents);
    return name;
}

void freeEntry(entry* ent) {
    freeStr(ent->productName);
    // freeStr(ent->username);
    freeStr(ent->date);
    free(ent);
}

int binarySearchDiary(vector* diary, string* key, int low, int high) {
    if (low > (high)) return -1;
    int mid = low + ((high - low) / 2);
    entry* current = (entry*) diary->contents[mid];
    int ordering = strcmp(key->contents, current->key->contents);
    if (ordering == 0) return mid;
    if (ordering < 0) return binarySearchDiary(diary, key, low, mid -1);
    return binarySearchDiary(diary, key, mid+1, high);
}

void insertIntoDiary(vector* diary, entry* new) {
    int previousIndex = diary->size - 1;
    pushToVec(diary, new);
    // insertionSort the newest entry
    while(previousIndex >= 0) {
        entry* previousEntry = (entry*) diary->contents[previousIndex];
        if (strcmp(previousEntry->key->contents, new->key->contents) < 0) {
            //if entries are out of order
            swapEntriesAt(diary, previousIndex, (previousIndex + 1));
            previousIndex--;
        } else { //If they're in order, we're done
            break;
        }
    }

}

void deleteAtIndex(vector* diary, int index) {
    if (index < 0 || index >= diary->size) return;
    // shift contents left
    for(int i = index; i < diary->size - 1; i++) {
        diary->contents[i] = diary->contents[i+1];
    }
    // remove the last entry (which is now duplicated)
    popFromVec(diary);
}

void swapEntriesAt(vector* diary, int i1, int i2) {
    void* temp;
    temp = diary->contents[i1];
    diary->contents[i1] = diary->contents[i2];
    diary->contents[i2] = temp;
}

entry* entryFromString(char* line, struct Node* productRoot) {
    char* nextField;
    const char* delimiter = "~";
    int numServings;
    // Read Date
    nextField = strsep(&line, delimiter);
    string* date = strFrom(nextField);

    // Read product name
    nextField = strsep(&line, delimiter);
    string* productName = strFrom(nextField);
    
    // Read servings
    nextField = strsep(&line, delimiter);
    if (strlen(nextField)) {
        numServings = atof(nextField);
    } else {
        numServings =  0;
    }

    return newEntry(productName, date, numServings, productRoot);
}


void saveDiary(vector* diary, string* username) {
    if (diary->size == 0) return;
    FILE* fp;
    char location[100] = {'\0'};
    strcpy(location, "data/");
    strcat(location, username->contents);
    strcat(location, ".log");
    remove(location);
    if (diary->size > 0) {
        fp = fopen(location, "w");
        int i;
        for(i = 0; i < diary->size; i++) {
            entry* current = (entry*) diary->contents[i];
            fprintf(fp, "%s~%s~%.2f\n", current->date->contents, 
            current->product->name->contents, current->servings);
        }
        fclose(fp);

    }
}

#endif
