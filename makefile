CFLAGS =-std=c11
LIB = src/library
PROJ = src/project
BIN = bin

LIB_OBJS = $(BIN)/vector.o $(BIN)/customString.o $(BIN)/displayHelper.o
PROJ_OBJS = $(BIN)/mainMenu.o $(BIN)/products.o $(PROJ)/main.c

make: $(PROJ_OBJS) $(LIB_OBJS) $(PROJ)/main.c
	gcc $(CFLAGS) -lncurses $(PROJ_OBJS) $(LIB_OBJS) -o $(BIN)/main.out

# Library Files
$(BIN)/customString.o: $(LIB)/customString.h $(LIB)/customString.c
	gcc $(CFLAGS) -c $(LIB)/customString.c -o $(BIN)/customString.o

$(BIN)/displayHelper.o: $(LIB)/displayHelper.c $(LIB)/displayHelper.h
	gcc $(CFLAGS) -c $(LIB)/displayHelper.c -o $(BIN)/displayHelper.o

$(BIN)/vector.o: $(LIB)/vector.h $(LIB)/vector.c
	gcc $(CFLAGS) -c $(LIB)/vector.c -o $(BIN)/vector.o

# Project Files
$(BIN)/mainMenu.o: $(PROJ)/mainMenu.h $(PROJ)/mainMenu.c
	gcc $(CFLAGS) -c $(PROJ)/mainMenu.c -o $(BIN)/mainMenu.o

$(BIN)/products.o: 	$(PROJ)/products.h $(PROJ)/products.c
	gcc $(CFLAGS) -c $(PROJ)/products.c -o $(BIN)/products.o


# General 
test: make 
	$(BIN)/main.out
	
clean:
	rm $(BIN)/*.o $(BIN)/*.out