#include "displayHelper.h"
#include <string.h>
#include <stdlib.h>

#ifndef __DISPLAY__HELP__C
#define __DISPLAY__HELP__C

int centerHoriz(char message[], int numCols) {
    return ((numCols - strlen(message))/2);
}

// From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html 
WINDOW *createWindow(int height, int width, int starty, int startx) {	
    WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters for the vertical and horizontal lines */
	wrefresh(local_win);		/* Show that box */
	return local_win;
}

// From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
void destroyWindow(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); // Erase borders
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

void print_menu(WINDOW *menuWIndow, int highlight, char* choices[], int numChoices)
{
	int x, y, i;
	x = 2;
	y = 2;
	box(menuWIndow, 0, 0);
	for(i = 0; i < numChoices; ++i)
	{	if(highlight == i + 1)
		{	wattron(menuWIndow, A_REVERSE); 
			mvwprintw(menuWIndow, y, x, "%s", choices[i]);
			wattroff(menuWIndow, A_REVERSE);
		}
		else
			mvwprintw(menuWIndow, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menuWIndow);
}

/* Report the choice according to mouse position */
int report_choice(int mouse_x, int mouse_y, int x, int y, int numChoices, char* choices[])
{	
	int choice;
 
	for(choice = 0; choice < numChoices; ++choice) {
		if(mouse_y == (y + choice) && mouse_x >= x && mouse_x <= (x + strlen(choices[choice])))
		{	
			return choice;	
		} 
	}
	return -1;
}

void printCentered(int y, char* message) {
	int x = (COLS - strlen(message)) / 2;
	mvprintw(y, x, message);
	refresh();
}

int selectFromChoices(WINDOW* win, int y, int x, char** choices, int numChoices) {
	cbreak();               /* Don't wait for newline when reading characters */
    noecho();
	MEVENT event;
	int input, choice;
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(win, TRUE);
	
	for (int i = 0; i < numChoices; i++) {
		mvprintw(y+i, x, choices[i]);
	}
	refresh();
	choice = 0;
	while(1){ 
		highlightChoice(win, y, x, choices, numChoices, choice);
		// input = wgetch(win);
		input = getch();
		if (input == KEY_MOUSE) {
			if(getmouse(&event) == OK){
			// printf("Bueller?");
				int mouseChoice = report_choice(event.x, event.y, x, y, numChoices, choices);
				// printf("Mouse at: %d, %d\n", event.y, event.x);
				// printf("Choice at: %d, %d\n", y, x);
				if (mouseChoice < 0) continue;
				choice = mouseChoice;
				return choice;
			}
		}
		if (input == KEY_UP)  if (--choice < 0) choice = numChoices - 1;
		if (input == KEY_DOWN) choice = (choice + 1) % numChoices;
		if ((input) > 48 && (input - 1) <= (48 + numChoices)) return input - 48; // if input between 0 and numchoices, convert to int
		if (input == 10) return choice; // Enter
	}
	return choice + 1; // return the choice, converted to one-indexed.
}

void highlightChoice(WINDOW* menuWindow, int y, int x, char** choices, int numChoices, int highlight) {
	// printf("Highlighting!");
	// for(int i = 0; i < numChoices; ++i)
	// {	if(highlight == (i + 1))
	// 	{	wattron(menuWindow, A_REVERSE); 
	// 		mvwprintw(menuWindow, y, x, "%s", choices[i]);
	// 		wattroff(menuWindow, A_REVERSE);
	// 	}
	// 	else
	// 		mvwprintw(menuWindow, y, x, "%s", choices[i]);
	// 	++y;
	// }
	highlight = highlight % numChoices;
	for(int i = 0; i < numChoices; ++i)
	{	if(highlight == i)
		{	attron(A_REVERSE); 
			mvprintw(y + i, x, "%s", choices[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y + i, x, "%s", choices[i]);
	}
	// wrefresh(menuWindow);
	refresh();
}

string* readString(int maxLength, char delimiter) {
	noecho();
	string* input = newString();
	char ch;
	int x, y;
    while (1) 
    {
		ch = getch();
		if (ch == delimiter && input->size != 0) break;
		if (ch == 127 || ch == 8) { //backspace or delete
			popFromStr(input);
			getyx(stdscr, y, x);
			mvprintw(y, x-1, " ");
			mvprintw(y, x-1, "\0");
		} else if (ch >= 97 && ch <= 122 && input->size < maxLength) {
			pushToStr(input, ch);
			addch(ch);
		} else if (ch >= 65 && ch <= 90 && input->size < maxLength) {
			ch += 32;
			pushToStr(input, ch);
			addch(ch);
		}
		refresh();
    }

    // // restore your cbreak / echo settings here
	// trimStr(input);
    return input;
	// return NULL;
}

#endif