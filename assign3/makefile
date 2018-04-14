OBJS = integer.o real.o string.o scanner.o dll.o sll.o queue.o bst.o avl.o binomial.o prim.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-queue test-bst test-avl test-binomial prim

test-sll : test-sll.o integer.o sll.o
		gcc $(LOPTS) test-sll.o integer.o sll.o -o test-sll

test-dll : test-dll.o integer.o dll.o
		gcc $(LOPTS) test-dll.o integer.o dll.o -o test-dll

test-queue : test-queue.o integer.o sll.o queue.o
		gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-bst : test-bst.o integer.o sll.o queue.o bst.o
		gcc $(LOPTS) test-bst.o integer.o sll.o queue.o bst.o -o test-bst

test-avl : test-avl.o integer.o sll.o queue.o bst.o avl.o
		gcc $(LOPTS) test-avl.o integer.o sll.o queue.o bst.o avl.o -o test-avl

test-binomial : test-binomial.o binomial.o queue.o sll.o integer.o dll.o 
		gcc $(LOPTS) test-binomial.o binomial.o queue.o sll.o integer.o dll.o -lm -o test-binomial 

prim : prim.o integer.o scanner.o sll.o queue.o bst.o dll.o avl.o edge.o vertex.o
		gcc $(LOPTS) prim.o integer.o scanner.o sll.o queue.o bst.o dll.o avl.o edge.o vertex.o -o prim

test-sll.o : test-sll.c sll.h integer.h
		gcc $(OOPTS) test-sll.c

test-queue.o : test-queue.c queue.h sll.h integer.h
		gcc $(OOPTS) test-queue.c

test-bst.o : test-bst.c bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-bst.c

test-binomial.o : test-binomial.c binomial.h queue.h sll.h dll.h integer.h
		gcc $(OOPTS) test-binomial.c -lm

test-avl.o : test-avl.c avl.h bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-avl.c

prim.o : prim.c integer.h scanner.h sll.h queue.h bst.h binomial.h avl.h dll.h vertex.h edge.h
		gcc $(OOPTS) prim.c

avl.o : avl.c bst.h queue.h sll.h
		gcc $(OOPTS) avl.c

binomial.o : binomial.c dll.h
		gcc $(OOPTS) binomial.c

bst.o : bst.c bst.h queue.h sll.h
		gcc $(OOPTS) bst.c

stack.o : stack.c stack.h dll.h
		gcc $(OOPTS) stack.c

queue.o : queue.c queue.h sll.h
		gcc $(OOPTS) queue.c

sll.o : sll.c sll.h
		gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
		gcc $(OOPTS) dll.c

vertex.o : vertex.c vertex.h
		gcc $(OOPTS) vertex.c

edge.o : edge.c edge.h
		gcc $(OOPTS) edge.c

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

real.o : real.c real.h
		gcc $(OOPTS) real.c

string.o : string.c string.h
		gcc $(OOPTS) string.c

scanner.o : scanner.c scanner.h
		gcc $(OOPTS) scanner.c

valgrind : all
	echo testing singly-linked list
	valgrind ./test-sll
	echo testing doubly-linked list
	valgrind ./test-dll
	echo testing queue
	valgrind ./test-queue
	echo testing binary search tree
	valgrind ./test-bst
	echo testing binomial heap
	valgrind ./test-binomial
	echo testing avl tree
	valgrind ./test-avl

test : all
	echo testing singly-linked list
	./test-sll
	echo testing doubly-linked list
	./test-dll
	echo testing queue
	./test-queue
	echo testing binary search tree
	./test-bst
	echo testing binomial heap
	valgrind ./test-binomial
	echo testing avl tree
	./test-avl

clean	:
		rm -f $(OBJS) *.o test-*.o test-queue test-sll test-bst test-avl test-binomial
