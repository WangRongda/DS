test: test.c circularLinkList.o 
	gcc -o test test.c circularLinkList.o
circularLinkList.o: circularLinkList.h circularLinkList.c
	gcc -c circularLinkList.c -o circularLinkList.o

clean:
	rm *.o test
