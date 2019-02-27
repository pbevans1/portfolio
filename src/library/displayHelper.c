#include "displayHelper.h"
#include <string.h>

#ifndef __DISPLAY__HELP__C
#define __DISPLAY__HELP__C

int centerHoriz(char message[], int numCols) {
    return ((numCols - strlen(message))/2);
}



#endif