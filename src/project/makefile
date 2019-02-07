CFLAGS =-std=c11

# make: dynamicArray.o
# 	gcc $(CFLAGS) main.c dynamicArray.o

# dynamicArray.o: ../library/dynamicArray.h ../library/dynamicArray.c
# 	gcc $(CFLAGS) -c ../library/dynamicArray.c

make: vector.o customString.o
	gcc $(CFLAGS) main.c vector.o customString.o -o main.out

vector.o: ../library/vector.h ../library/vector.c
	gcc $(CFLAGS) -c ../library/vector.c

customString.o: ../library/customString.h ../library/customString.c
	gcc $(CFLAGS) -c ../library/customString.c

test: make
	./main.out

clean:
	rm *.o *.out