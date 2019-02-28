#include <ncurses.h>
#ifndef __DISPLAY__HELP__H
#define __DISPLAY__HELP__H


int centerHoriz(char*, int);
WINDOW *createWindow(int, int, int, int);
void destroyWindow(WINDOW*);
void report_choice(int mouse_x, int mouse_y, int startx, int starty, int *choiceNum, int numChoices, char* choices[]);
void print_menu(WINDOW *menuWIndow, int highlight, char* choices[], int numChoices);

#endif