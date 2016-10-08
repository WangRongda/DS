test: test.c singleLinkList.o 
	gcc -o test test.c singleLinkList.o
singleLinkList.o: singleLinkList.h singleLinkList.c
	gcc -c singleLinkList.c -o singleLinkList.o

clean:
	rm *.o test
