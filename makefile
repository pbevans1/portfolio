CFLAGS =-std=c11 -g
LIB = src/library
PROJ = src/project
BIN = bin
# PROJ_OBJS missing $(BIN)/serving.o 

LIB_OBJS = $(BIN)/vector.o $(BIN)/customString.o $(BIN)/displayHelper.o $(BIN)/avlTree.o
PROJ_OBJS = $(BIN)/mainMenu.o $(BIN)/products.o $(BIN)/read.o $(BIN)/hashTable.o $(PROJ)/main.c

make: $(PROJ_OBJS) $(LIB_OBJS) $(PROJ)/main.c
	gcc $(CFLAGS) -lncurses $(PROJ_OBJS) $(LIB_OBJS) -o $(BIN)/main.out

# Library Files
$(BIN)/customString.o: $(LIB)/customString.h $(LIB)/customString.c
	gcc $(CFLAGS) -c $(LIB)/customString.c -o $(BIN)/customString.o

$(BIN)/displayHelper.o: $(LIB)/displayHelper.c $(LIB)/displayHelper.h
	gcc $(CFLAGS) -c $(LIB)/displayHelper.c -o $(BIN)/displayHelper.o

$(BIN)/vector.o: $(LIB)/vector.h $(LIB)/vector.c
	gcc $(CFLAGS) -c $(LIB)/vector.c -o $(BIN)/vector.o

$(BIN)/avlTree.o: $(LIB)/avlTree.h $(LIB)/avlTree.c
	gcc $(CFLAGS) -c $(LIB)/avlTree.c -o $(BIN)/avlTree.o

# Project Files
$(BIN)/mainMenu.o: $(PROJ)/mainMenu.h $(PROJ)/mainMenu.c
	gcc $(CFLAGS) -c $(PROJ)/mainMenu.c -o $(BIN)/mainMenu.o

$(BIN)/products.o: 	$(PROJ)/products.h $(PROJ)/products.c
	gcc $(CFLAGS) -c $(PROJ)/products.c -o $(BIN)/products.o

# $(BIN)/serving.o: 	$(PROJ)/serving.h $(PROJ)/serving.c
# 	gcc $(CFLAGS) -c $(PROJ)/serving.c -o $(BIN)/serving.o

$(BIN)/read.o: 	$(PROJ)/read.h $(PROJ)/read.c
	gcc $(CFLAGS) -c $(PROJ)/read.c -o $(BIN)/read.o

$(BIN)/hashTable.o:  $(PROJ)/hashTable.h $(PROJ)/hashTable.c
	gcc $(CFLAGS) -c $(PROJ)/hashTable.c -o $(BIN)/hashTable.o


# General 
test: make 
	$(BIN)/main.out
	
clean:
	rm $(BIN)/*.o $(BIN)/*.out