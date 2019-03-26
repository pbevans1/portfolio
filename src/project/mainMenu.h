#ifndef __MAIN__MENU__H
#define __MAIN__MENU__H
#include <curses.h>
#include "../library/customString.h"
#include "../library/avlTree.h"
#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "string.h"
#include "read.h"
#include "diary.h"

void displayMainMenu();
void finish(int);
void saveAndQuit(vector* diary, string* username);



#endif
