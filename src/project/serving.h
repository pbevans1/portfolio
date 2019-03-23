#include "../library/customString.h"

#ifndef __SERVING__H 
#define __SERVING__H 


typedef struct __serving {
    int NDB_Number;
    int servingSize;
    string* regUnit;
    int houseServingSize;
    string* houseUnit;
    
} Serving;


Serving* getServingFromString(char*);
void prettyPrintServing(Serving*);

#endif
