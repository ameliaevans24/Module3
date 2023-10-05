CFLAGS: -Wall -pedantic -std=c11 -l.	-g

all:	test test1 test2 test3

list.o:	list.c list.h
				gcc $(CFLAGS) -c list.c

test.o:	test.c list.h
				gcc $(CFLAGS) -c test.c

test1.o:	test1.c list.h
					gcc $(CFLAGS) -c test1.c

test2.o: 	test2.c list.h
					gcc $(CFLAGS) -c test2.c

test3.o:	test3.c list.h
					gcc $(CFLAGS) -c test3.c

test: 	test.o list.o
				gcc $(CFLAGS) test.o list.o -o test

test1:	test1.o list.o
				gcc $(CFLAGS) test1.o list.o -o test1

test2: 	test2.o list.o
				gcc $(CFLAGS) test2.o list.o -o test2

test3: 	test3.o list.o
				gcc $(CFLAGS) test3.o list.o -o test3

clean:
			rm -f *.o test test1 test2 test3

