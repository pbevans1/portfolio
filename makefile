# Define Variables
CFLAGS = -std=c11 -g -Wall
LIB = src/library
PROJ = src/project
BIN = bin
DATA = data/food_database.csv
DOWNLOADS = dataBuilder/Nutrients.csv dataBuilder/Serving_size.csv dataBuilder/Products.csv
LIB_OBJS = $(BIN)/vector.o $(BIN)/customString.o $(BIN)/avlTree.o
PROJ_OBJS = $(BIN)/mainMenu.o $(BIN)/products.o $(BIN)/read.o $(BIN)/diary.o $(BIN)/displayHelper.o $(PROJ)/main.c

make: bin $(PROJ_OBJS) $(LIB_OBJS) $(PROJ)/main.c $(DATA)
	gcc $(CFLAGS) $(PROJ_OBJS) $(LIB_OBJS) -o $(BIN)/main.out -lcurses 

# Library File Recipes
$(BIN)/customString.o: $(LIB)/customString.h $(LIB)/customString.c
	gcc $(CFLAGS) -c $(LIB)/customString.c -o $(BIN)/customString.o

$(BIN)/vector.o: $(LIB)/vector.h $(LIB)/vector.c
	gcc $(CFLAGS) -c $(LIB)/vector.c -o $(BIN)/vector.o

$(BIN)/avlTree.o: $(LIB)/avlTree.h $(LIB)/avlTree.c
	gcc $(CFLAGS) -c $(LIB)/avlTree.c -o $(BIN)/avlTree.o

# Project File Recipes
$(BIN)/mainMenu.o: $(PROJ)/mainMenu.h $(PROJ)/mainMenu.c
	gcc $(CFLAGS) -c $(PROJ)/mainMenu.c -o $(BIN)/mainMenu.o

$(BIN)/displayHelper.o: $(PROJ)/displayHelper.c $(PROJ)/displayHelper.h
	gcc $(CFLAGS) -c $(PROJ)/displayHelper.c -o $(BIN)/displayHelper.o

$(BIN)/products.o: 	$(PROJ)/products.h $(PROJ)/products.c
	gcc $(CFLAGS) -c $(PROJ)/products.c -o $(BIN)/products.o

$(BIN)/read.o: 	$(PROJ)/read.h $(PROJ)/read.c
	gcc $(CFLAGS) -c $(PROJ)/read.c -o $(BIN)/read.o

$(BIN)/diary.o:  $(PROJ)/diary.h $(PROJ)/diary.c
	gcc $(CFLAGS) -c $(PROJ)/diary.c -o $(BIN)/diary.o

# Data Check Recipes
$(DATA): $(DOWNLOADS)
	$(info echo 'data/food_database.csv' is missing. Add it or use 'make database' to build it.")
	$(error missing data file)

$(DOWNLOADS):
	$(info Data files (Nutrients.csv, Products.csv, Serving_size.csv) are missing from 'dataBuilder/')
	$(info Add them to the directory or use 'make download 'to download them.)
	$(error missing data file)

# Build Database Recipe
database: $(DOWNLOADS)
	mkdir data
	./shellScripts/buildData.sh

# Download Database Recipe
download:
	./shellScripts/download.sh

# Helpful Commands
test: make 
	$(BIN)/main.out

bin: 
	mkdir bin
	
clean:
	rm $(BIN)/*.o $(BIN)/*.out

clean-all: 
	rm $(BIN)/*.o $(BIN)/*.out
	rm data/* dataBuilder/*

build-all: download database make

test-all: build-all
	$(BIN)/main.out

run: make
	$(BIN)/main.out

user-list: list-users

users: list-users

list-users:
	$(info Here's the list of users)
	@ls data/*.log 2> /dev/null | sed 's/\(.*\)\..*/\1/' | sed 's/data\///'
	@echo 

help: 
	$(info General - To use the program, use 'make run' and follow the directions on screen. You should use keyboard and mouse to navigate.)
	$(info Quitting - The exit button is in the top left corner.)
	$(info Username -If you've forgotten your username try "make list-users")

