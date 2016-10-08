test: test.c doubleLinkList.o 
	gcc -o test test.c doubleLinkList.o
doubleLinkList.o: doubleLinkList.h doubleLinkList.c
	gcc -c doubleLinkList.c -o doubleLinkList.o

clean:
	rm *.o test
