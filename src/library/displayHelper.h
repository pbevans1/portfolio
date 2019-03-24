#ifndef __DISPLAY__HELP__H
#define __DISPLAY__HELP__H
#include <curses.h>
#include "customString.h"
#include "../project/products.h"
#include <string.h>
#include <stdlib.h>
#include "../library/avlTree.h"
#include "../project/diary.h"

typedef struct __button {
    char* text;
    int x;
    int y; 
    int size;
} Button;

int backButtonWasClicked(int, MEVENT);
void printExitButton();
void printBackButton();
int exitButtonWasClicked(int, MEVENT); 
int centerHoriz(char*, int);
WINDOW *createWindow(int, int, int, int);
void destroyWindow(WINDOW*);
int report_choice(int mouse_x, int mouse_y, int startx, int endx, int y, int numChoices, char* choices[]);
void print_menu(WINDOW *menuWIndow, int highlight, char* choices[], int numChoices);
void printCentered(int, char*);
string* readString(int, int, int, char);
int selectFromChoices(WINDOW*, int y, int x, char** choices, int numChoices);
void highlightChoice(WINDOW* menuWindow, int y, int x, char** choices, int numChoices, int highlight);
int selectFromDiary(int y, int x, char** choices, int numChoices);
string* readProductName(int startx, int starty, int maxLength, char delimiter, struct Node* productRoot);
Product* selectFromNearbyProducts(int x, int y, struct Node* closest);
string* readDate(int startx, int starty, char delimiter, struct Node* productRoot);
double readFloat(int startx, int starty, char delimiter, struct Node* productRoot);
void printPreviousButton(vector* diary, int lastDisplayed, int instructionHeight);
void printNextButton(vector* diary, int lastDisplayed, int instructionHeight);
int previousButtonClicked(int input, MEVENT event);
int nextButtonClicked(int input, MEVENT event);
void printUpdateMenuButtons();
int updateMenuButtonClicked(int input, MEVENT event);
void printEntry(entry*);
void printCancelButton();
#endif
