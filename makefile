CFLAGS =-std=c11

make: bin/vector.o bin/customString.o
	gcc $(CFLAGS) src/project/main.c bin/vector.o bin/customString.o -o bin/main.out

bin/vector.o: src/library/vector.h src/library/vector.c
	gcc $(CFLAGS) -c src/library/vector.c -o bin/vector.o

bin/customString.o: src/library/customString.h src/library/customString.c
	gcc $(CFLAGS) -c src/library/customString.c -o bin/customString.o

test: make
	bin/main.out

clean:
	rm bin/*