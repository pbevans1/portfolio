#include "displayHelper.h"
#include <string.h>

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
void report_choice(int mouse_x, int mouse_y, int start_x, int start_y, int *choiceNum, int numChoices, char* choices[])
{	int i,j, choice;

	i = start_x + 2;
	j = start_y + 3;
	for(choice = 0; choice < numChoices; ++choice)
		if(mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice]))
		{	if(choice == numChoices - 1)
				*choiceNum = -1;		
			else
				*choiceNum = choice + 1;	
			break;
		}
}

#endif