#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C
#include "mainMenu.h"

vector* getUserDiaryMenu(struct Node*);
void diaryCrudMenu(vector* diary, struct Node*);
char** formatNextTenEntries(vector* diary, int startNum, char* button);
int numEntries(char** formattedEntries);

string* displayMainMenu(struct Node* productRoot)  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html


    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    // menu_win = newwin(0, 0, LINES, COLS);
    vector* userDiary = getUserDiaryMenu(productRoot);
    diaryCrudMenu(userDiary, productRoot);
    finish(0);
    // FIXME
    return newString();
}

void diaryAddMenu(vector* diary, struct Node* productRoot) {
    
    string* name = NULL;
    int instructionHeight = LINES / 6;
    char instructions[] = "What kind of food did you eat? ";
    Product* product = NULL;
    string* date = NULL;
    double numServings = 0;
    // Get product
    while (1) {
        clear();
        printExitButton();
        printCentered(instructionHeight, instructions);
        mvprintw(instructionHeight + 1, COLS/2 - 20, "Item Name: ");
        name = readProductName((COLS / 2) - 5, instructionHeight + 3, 100, '\n', productRoot);
        if (name == NULL) finish(0);
        struct Node* nearestNode = findClosestNode(productRoot, name->contents);
        product = selectFromNearbyProducts(COLS / 3, instructionHeight, nearestNode);
        
        if (product != NULL) break;
    }
    char dateInstructions[] = "What was the date?";
    while (1) {
        clear();
        printExitButton();
        printCentered(instructionHeight, dateInstructions);
        mvprintw(instructionHeight + 1, COLS/2 - 20, "Date (yyyy/mm/dd): ");
        date = readDate((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot);
        if (date == NULL) finish(0);
        break;
    }
    while (1) {
        clear();
        char servingInstructions[] = "How many servings did you eat?";
        char* productInfo = malloc(sizeof(char) * 500);
        sprintf(productInfo, "A serving of %s is %.2f %s", 
            product->name->contents, product->serving_size, product->serving_units->contents);
        printCentered(instructionHeight - 1, servingInstructions);
        printCentered(instructionHeight, productInfo);
        free(productInfo);
        printExitButton();
        mvprintw(instructionHeight + 1, COLS/2 - 22, "Servings (i.e 1.0): ");
        numServings = readFloat((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot); 
        if (numServings < 0) finish(0);
        break;
    }
    entry* new = entryFromProduct(product, date, numServings);
    if (new == NULL) {
        printw("ERROR NULL");
        getch();
    }
    // prettyPrintProduct(new->product);
    // getch();
    pushToVec(diary, new);
}

void diaryUpdateMenu(vector* diary, int index) {
    clear();
    int instructionHeight = LINES / 6;
    char* itemInfo = malloc(sizeof (char) * 500);
    entry* ent = diary->contents[index];
    sprintf(itemInfo,  "On %s you ate %.1f servings of %s.", ent->date->contents, 
                ent->servings, ent->product->name->contents);
    printCentered(instructionHeight, itemInfo);
    free(itemInfo);
    printUpdateMenuButtons();
    getch();

}

void diaryCrudMenu(vector* diary, struct Node* productRoot) {
    int instructionHeight = LINES / 6;
    char instructions[] = "Click any entry view, modify, or delete it, or press the button to add a new one.";
    int lastEntryDisplayed = 0;
    char addButton[] = " New Entry";
    char** currentPage;
    while(1) {
        clear();
        printExitButton();
        printPreviousButton(diary, lastEntryDisplayed, instructionHeight);
        printNextButton(diary, lastEntryDisplayed, instructionHeight);
        printCentered(instructionHeight, instructions);
        currentPage = formatNextTenEntries(diary, lastEntryDisplayed, addButton);
        int numToDisplay = numEntries(currentPage);
        int x = (COLS / 4);
        
        int choice = selectFromDiary(instructionHeight + 2, x, currentPage, numToDisplay + 1);
        if (choice == -5) finish(0);
        if (choice == -3 && lastEntryDisplayed > 0) {
            lastEntryDisplayed = max(lastEntryDisplayed - 10, 0);
            continue;
        }
         if (choice == -1 && (lastEntryDisplayed + 10) < diary->size) {
            lastEntryDisplayed = min(lastEntryDisplayed + 10, diary->size);
            continue;
        }
        if (choice == 0) diaryAddMenu(diary, productRoot);
        if (choice >= 1 && choice <= 10) diaryUpdateMenu(diary, (choice - 1 + lastEntryDisplayed));
        // break;
    }
}

int numEntries(char** formattedEntries) {
    int i;
    for (i = 1; i < 11; i++) {
        if (formattedEntries[i] == NULL) break;
    }
    return i - 1;
}

char** formatNextTenEntries(vector* diary, int startNum, char* button) {
    char** formattedEntries = malloc(sizeof(char*) * 11);
    formattedEntries[0] = button;
    int entriesIndex = 1;
    // Fill up to 10 empty slots
    for (int i = startNum; i < diary->size && entriesIndex < 11; i++) {
        entry* currentEntry = (entry*) diary->contents[i];
        formattedEntries[entriesIndex] = formatEntry(currentEntry);
        entriesIndex++;
    }
    // Write NULLs to empty slots
    for (int i = entriesIndex; i < 11; i++) {
        formattedEntries[i] = NULL;
    }
    return formattedEntries;
}

vector* getUserDiaryMenu(struct Node* productRoot) {
    //Open Welcome Screen
    WINDOW* start_menu = newwin(0, 0, LINES, COLS);
    char welcome[] = "Welcome to Nutrition Tracker Pro!";
    int welcomeHeight = LINES / 6;
    int choice;
    string* username;
    while (1) {
        clear();
        printCentered(welcomeHeight, welcome);
        //Get Username	
        char instructions[] = "Enter a username to continue: ";
        printExitButton();
        // printBackButton();
        mvprintw(welcomeHeight + 3, ((COLS - 40) / 2), instructions);
        username = readString(welcomeHeight+5, ((COLS - 10) / 2), 50, '\n');
        if (username == NULL) finish(0); // if exit button was clicked
        // move(welcomeHeight+3, 0);
        clear();
        printExitButton();
        // clrtoeol();
        int startx = (COLS - username->size - 8) / 2;
        mvprintw(welcomeHeight+3, startx, "Hello %s!", username->contents);

        
        //Check for log file
        if (!logFileExists(username->contents)) {
            printCentered(welcomeHeight+4, "We couldn't find any old log files for you");
            char* options[] = {"Start a new diary ", "Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+6, (COLS - 30) / 2, options, 2);
            if (choice == -5) finish(0);
            choice++; // Convert choice from index to counting number;
            if (choice == 1) {
                destroyWindow(start_menu);
                return newVector();
            }    
            if (choice == 2) continue;
        } else {
            printCentered(welcomeHeight+4, "We found your last save! Would you like to ");
            char* options[] = {"Open it", "Overwrite it", "Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+5, (COLS - 30) / 2, options, 3);
            if (choice == -5) finish(0);
            choice++; // Convert choice from index to counting number;
            if (choice == 1) {
                destroyWindow(start_menu);
                return readDiary(username->contents, productRoot);
            }
            if (choice == 2) {
                destroyWindow(start_menu);
                return newVector();
            }
            if (choice == 3) continue;
            
        }
    }
    
    getch();
    // Unreachable
    printf("Uh-oh! We reached unreachable!");
    getch();
    destroyWindow(start_menu);

    return newVector();
} 


void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        exit(0);
}




#endif
