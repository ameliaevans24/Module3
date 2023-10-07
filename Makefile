CFLAGS: -Wall -pedantic -std=c11 -l.	-g

all:	qtest test test1 test2 test3

queue.o:	queue.c	queue.h
					gcc $(CFLAGS)	-c	queue.c

list.o:	list.c list.h
				gcc $(CFLAGS) -c list.c

qtest.o:	qtest.c	queue.h
					gcc	$(CFLAGS)	-c	qtest.c

test.o:	test.c list.h
				gcc $(CFLAGS) -c test.c

test1.o:	test1.c list.h
					gcc $(CFLAGS) -c test1.c

test2.o: 	test2.c list.h
					gcc $(CFLAGS) -c test2.c

test3.o:	test3.c list.h
					gcc $(CFLAGS) -c test3.c

qtest:	qtest.o	queue.o
				gcc	$(CFLAGS)	qtest.o	queue.o	-o	qtest.c

test: 	test.o list.o
				gcc $(CFLAGS) test.o list.o -o test

test1:	test1.o list.o
				gcc $(CFLAGS) test1.o list.o -o test1

test2: 	test2.o list.o
				gcc $(CFLAGS) test2.o list.o -o test2

test3: 	test3.o list.o
				gcc $(CFLAGS) test3.o list.o -o test3

clean:
			rm -f *.o qtest	test test1 test2 test3


