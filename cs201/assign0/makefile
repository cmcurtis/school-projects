OBJS = integer.o real.o string.o sll.o dll.o stack.o queue.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-queue test-dll test-stack

test-sll : test-sll.o integer.o sll.o
		gcc $(LOPTS) test-sll.o integer.o sll.o -o test-sll

test-dll : test-dll.o integer.o dll.o
		gcc $(LOPTS) test-dll.o integer.o dll.o -o test-dll

test-stack : test-stack.o integer.o dll.o stack.o
		gcc $(LOPTS) test-stack.o integer.o dll.o stack.o -o test-stack

test-queue : test-queue.o integer.o sll.o queue.o
		gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-sll.o : test-sll.c sll.h integer.h
		gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h
		gcc $(OOPTS) test-dll.c

test-stack.o : test-stack.c stack.h dll.h integer.h
		gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c queue.h sll.h integer.h
		gcc $(OOPTS) test-queue.c

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

valgrind : all
	echo testing singly-linked list
	valgrind ./test-sll
	echo testing doubly-linked list
	valgrind ./test-dll
	echo testing stack
	valgrind ./test-stack
	echo testing queue
	valgrind ./test-queue

test : all
	echo testing singly-linked list
	./test-sll
	echo testing doubly-linked list
	./test-dll
	echo testing stack
	./test-stack
	echo testing queue
	./test-queue

clean	:
		rm -f $(OBJS) *.o test-*.o test-stack test-queue test-sll test-dll
