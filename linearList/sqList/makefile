test: test.c sqList.o 
	gcc -o test test.c sqList.o
sqList.o: sqList.h sqList.c
	gcc -c sqList.c -o sqList.o

clean:
	rm *.o test
