#ifndef __DISPLAY__HELP__H
#define __DISPLAY__HELP__H
#include <ncurses.h>
#include "customString.h"

int centerHoriz(char*, int);
WINDOW *createWindow(int, int, int, int);
void destroyWindow(WINDOW*);
int report_choice(int mouse_x, int mouse_y, int x, int y, int numChoices, char* choices[]);
void print_menu(WINDOW *menuWIndow, int highlight, char* choices[], int numChoices);
void printCentered(int, char*);
void readString(string*, char);
int selectFromChoices(WINDOW* win, int y, int x, char** choices, int numChoices);
void highlightChoice(WINDOW* menuWindow, int y, int x, char** choices, int numChoices, int highlight);
#endif