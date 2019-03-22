#include "displayHelper.h"


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

string* createButtonString(char* text, int size) {
	string* new = malloc(sizeof(string));
	new->size = size;
	new->capacity = size + 1;
	new->contents = malloc(sizeof(char) * new->capacity);
	new->contents[new->size] = '\0';
	int textSize = strlen(text);
	int numSpaces = (size - textSize) / 2;
	for (int i = 0; i < numSpaces; i++) {
		new->contents[i] = ' ';
	}
	strcat(new->contents, text);
	for (int i = numSpaces + textSize; i < new->size; i++) {
		new->contents[i] = ' ';
	}
	return new;
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
int report_choice(int mouse_x, int mouse_y, int startx, int endx, int y, int numChoices, char* choices[])
{	
	int choice;
 
	for(choice = 0; choice < numChoices; ++choice) {
		if(mouse_y == (y + (choice * 2)) && mouse_x >= startx && mouse_x <= endx)
		{	
			return choice;	
		} 
	}
	return -2;
}

int reportDiaryChoice(int mouse_x, int mouse_y, int startx, int endx , int y, int numChoices, char* choices[]) //corrects for double spacing
{	
	int choice;
	if(mouse_y == y && mouse_x >= (COLS / 2) - 5  && mouse_x <= (COLS / 2) + 5) return 0; // handle add button
	for(choice = 1; choice < numChoices; ++choice) {
		if(mouse_y == (y + (choice * 2)) && mouse_x >= startx && mouse_x <= endx)
		{	
			return choice;	
		} 
	}
	return -2;
}

void printCentered(int y, char* message) {
	int x = (COLS - strlen(message)) / 2;
	mvprintw(y, x, message);
	refresh();
}

int maxLen(char** choices, int numChoices) {
	int max = -1;
	for (int i = 0; i < numChoices; i++) {
		int len = strlen(choices[i]);
		if (len > max) max = len;
	}
	return max;
}

void writeSpacesUntil(int x) {
	int currentx, y;
	getyx(stdscr, y, currentx);
	for (int i = currentx; i < x; i++) {
		addch(' ');
	}
}

int selectFromChoices(WINDOW* win, int y, int x, char** choices, int numChoices) {
	cbreak();               /* Don't wait for newline when reading characters */
    noecho();
	MEVENT event;
	int input, choice;
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(win, TRUE);
	attron(A_REVERSE); 
	int maxlength = maxLen(choices, numChoices);
	for (int i = 0; i < numChoices; i++) {
		string* button = createButtonString(choices[i], maxlength);
		mvprintw(y+(i*2), x, button->contents);
		freeStr(button);
	}
	attroff(A_REVERSE);
	refresh();
	choice = 0;
	while(1){ 
		// highlightChoice(win, y, x, choices, numChoices, choice);
		// input = wgetch(win);
		input = getch();
		if (input == KEY_MOUSE) {
			if(getmouse(&event) == OK){
				int mouseChoice = report_choice(event.x, event.y, x, x+maxlength, y, numChoices, choices);
				if (mouseChoice < 0) continue;
				choice = mouseChoice;
				return choice;
			}
		}
		// if (input == KEY_UP)  if (--choice < 0) choice = numChoices - 1;
		// if (input == KEY_DOWN) choice = (choice + 1) % numChoices;
		if ((input) > 48 && (input - 1) <= (48 + numChoices)) return input - 48; // if input between 0 and numchoices, convert to int
		// if (input == 10) return choice; // Enter
	}
	return choice; // return the choice
}

int selectFromDiary(int y, int x, char** choices, int numChoices) {
	cbreak();               /* Don't wait for newline when reading characters */
    noecho();
	MEVENT event;
	int input, choice;
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(stdscr, TRUE);
	attron(A_REVERSE); 
	printCentered(y, choices[0]);
	attroff(A_REVERSE);
	
	int maxlength = maxLen(choices, numChoices);
	for (int i = 1; i < numChoices; i++) {
		mvprintw(y+(i*2), x, choices[i]); //double space
		writeSpacesUntil(maxlength);
	}
	refresh(); 
	choice = 0;
	while(1){ 
		// highlightChoice(win, y, x, choices, numChoices, choice);
		// input = wgetch(win);
		input = getch();
		if (input == KEY_MOUSE) {
			if(getmouse(&event) == OK){
				int mouseChoice = reportDiaryChoice(event.x, event.y, x, x + maxlength, y, numChoices, choices);
				if (mouseChoice < 0) continue;
				choice = mouseChoice;
				return choice;
			}
		}
		// if (input == KEY_UP)  if (--choice < 0) choice = numChoices - 1;
		// if (input == KEY_DOWN) choice = (choice + 1) % numChoices;
		// if ((input) > 48 && (input - 1) <= (48 + numChoices)) return input - 48; // if input between 0 and numchoices, convert to int
		// if (input == 10) return choice; // Enter
	}
	return choice; // return the choice
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

Product* selectFromNearbyProducts(int x, int y, struct Node* closest) {
	clear();
	char instructions[] = "Click a product to select it, or back to search again.";
	printCentered(y, instructions);
	struct Node* nearestProducts[5];
	char* productNames[6];
	nearestProducts[1] = predecessor(closest);
	nearestProducts[2] = predecessor(nearestProducts[1]);
	nearestProducts[0] = closest;
	nearestProducts[3] = successor(closest);
	nearestProducts[4] = successor(nearestProducts[3]);
	int maxLength = 0;
	char backButton[] = "   Back   ";
	productNames[0] = backButton;
	for (int i = 0; i < 5; i++) {
		char* name = nearestProducts[i]->product->name->contents;
		// printw("%d: %s\n", i, name);
		int nameLen = strlen(name);
		if (nameLen > maxLength) maxLength = nameLen;
		productNames[i + 1] = name;
	}
	int choice = selectFromDiary(y + 4, x, productNames, 6);
	choice--; // convert to index into products
	if (choice < 0) return NULL;
	return nearestProducts[choice]->product;

}


string* readProductName(int startx, int starty, int maxLength, char delimiter, struct Node* productRoot) {
	noecho(); 
	string* input = newString();
	int ch;
	int x, y;
	MEVENT event;
	char button[] = "  Search  ";
	attron(A_REVERSE);
	mvprintw(starty, startx, button);
	attroff(A_REVERSE);
	move(starty - 2, startx - 4);
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
			ch -= 32;
			pushToStr(input, ch);
			addch(ch);
		} else if (ch >= 65 && ch <= 90 && input->size < maxLength) {
			pushToStr(input, ch);
			addch(ch);
		} else if (ch >= 48 && ch <= 57 && input->size < maxLength) {
			pushToStr(input, ch);
			addch(ch);
		} else if (ch == '\n' && input->size != 0) {
			break;
		} else if (ch == KEY_MOUSE && input->size != 0) {
			if(getmouse(&event) == OK){
				// printw("x, %d, y: %d", event.x, event.y);
				if (event.y == starty && event.x >= startx- 5 && event.x <= startx + 5)
				break;
			}
		}
		
    }
	return input;

    // // restore your cbreak / echo settings here
	// trimStr(input);
	// return NULL;
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