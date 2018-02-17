OBJS = integer.o real.o string.o scanner.o sll.o dll.o stack.o queue.o bst.o heap.o heapsort.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-queue test-dll test-stack test-bst test-heap heapsort

test-sll : test-sll.o integer.o sll.o
		gcc $(LOPTS) test-sll.o integer.o sll.o -o test-sll

test-dll : test-dll.o integer.o dll.o
		gcc $(LOPTS) test-dll.o integer.o dll.o -o test-dll

test-stack : test-stack.o integer.o dll.o stack.o
		gcc $(LOPTS) test-stack.o integer.o dll.o stack.o -o test-stack

test-queue : test-queue.o integer.o sll.o queue.o
		gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-bst : test-bst.o integer.o sll.o queue.o bst.o
		gcc $(LOPTS) test-bst.o integer.o sll.o queue.o bst.o -o test-bst

test-heap : test-heap.o integer.o sll.o dll.o queue.o stack.o bst.o heap.o
		gcc $(LOPTS) test-heap.o integer.o sll.o dll.o queue.o stack.o bst.o heap.o -o test-heap

heapsort : heapsort.o real.o string.o scanner.o integer.o sll.o dll.o queue.o stack.o bst.o heap.o
		gcc $(LOPTS) heapsort.o real.o string.o scanner.o integer.o sll.o dll.o queue.o stack.o bst.o heap.o -o heapsort

test-sll.o : test-sll.c sll.h integer.h
		gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h
		gcc $(OOPTS) test-dll.c

test-stack.o : test-stack.c stack.h dll.h integer.h
		gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c queue.h sll.h integer.h
		gcc $(OOPTS) test-queue.c

test-bst.o : test-bst.c bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-bst.c

test-heap.o : test-heap.c heap.h bst.h stack.h queue.h sll.h dll.h integer.h
		gcc $(OOPTS) test-heap.c

heapsort.o : heapsort.c real.h string.h scanner.h integer.h sll.h dll.h queue.h stack.h bst.h heap.h
		gcc $(OOPTS) heapsort.c

heap.o : heap.c stack.h bst.h queue.h sll.h dll.h
		gcc $(OOPTS) heap.c

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
	echo testing stack
	valgrind ./test-stack
	echo testing queue
	valgrind ./test-queue
	echo testing binary search tree
	valgrind ./test-bst
	echo testing heap
	valgrind ./test-heap

test : all
	echo testing singly-linked list
	./test-sll
	echo testing doubly-linked list
	./test-dll
	echo testing stack
	./test-stack
	echo testing queue
	./test-queue
	echo testing binary search tree
	./test-bst
	echo testing heap
	./test-heap

clean	:
		rm -f $(OBJS) *.o test-*.o test-stack test-queue test-sll test-dll test-bst test-heap heapsort
