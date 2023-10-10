CFLAGS: -Wall -pedantic -std=c11 -l.	-g

all:	qtest7	qtest6	qtest5	qtest test test1 test2 test3

queue.o:	queue.c	queue.h
					gcc $(CFLAGS)	-c	queue.c

list.o:	list.c list.h
				gcc $(CFLAGS) -c list.c

qtest.o:	qtest.c	queue.h
					gcc	$(CFLAGS)	-c	qtest.c
					
qtest5.o:	qtest5.c	queue.h
			gcc	$(CFLAGS)	-c	qtest5.c

qtest6.o:	qtest6.c	queue.h
			gcc	$(CFLAGS)	-c	qtest6.c
			
qtest7.o:	qtest7.c	queue.h
			gcc	$(CFLAGS)	-c	qtest7.c

test.o:	test.c list.h
				gcc $(CFLAGS) -c test.c

test1.o:	test1.c list.h
					gcc $(CFLAGS) -c test1.c

test2.o: 	test2.c list.h
					gcc $(CFLAGS) -c test2.c

test3.o:	test3.c list.h
					gcc $(CFLAGS) -c test3.c

qtest:	qtest.o	queue.o
				gcc	$(CFLAGS)	qtest.o	queue.o	-o	qtest

qtest5:	qtest5.o	queue.o
		gcc	$(CLFAGS)	qtest5.o	queue.o	-o	qtest5

qtest6:	qtest6.o	queue.o
		gcc	$(CFLAGS)	qtest6.o	queue.o	-o	qtest6
		
qtest7:	qtest7.o	queue.o
		gcc	$(CFLAGS)	qtest7.o	queue.o	-o	qtest7

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


