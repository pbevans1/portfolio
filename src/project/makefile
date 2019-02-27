CFLAGS =-std=c11

# make: dynamicArray.o
# 	gcc $(CFLAGS) main.c dynamicArray.o

# dynamicArray.o: ../library/dynamicArray.h ../library/dynamicArray.c
# 	gcc $(CFLAGS) -c ../library/dynamicArray.c

make: vector.o customString.o mainMenu.o displayHelper.o
	gcc $(CFLAGS) -lncurses main.c vector.o customString.o mainMenu.o displayHelper.o -o main.out

vector.o: ../library/vector.h ../library/vector.c
	gcc $(CFLAGS) -c ../library/vector.c

customString.o: ../library/customString.h ../library/customString.c
	gcc $(CFLAGS) -c ../library/customString.c

mainMenu.o: mainMenu.h mainMenu.c
	gcc $(CFLAGS) -c mainMenu.c

displayHelper.o: ../library/displayHelper.c ../library/displayHelper.h
	gcc $(CFLAGS) -c ../library/displayHelper.c

test: make
	./main.out

clean:
	rm *.o *.out