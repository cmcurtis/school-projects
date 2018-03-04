OBJS = integer.o real.o string.o scanner.o sll.o queue.o bst.o gst.o avl.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-queue test-bst test-gst test-avl

test-sll : test-sll.o integer.o sll.o
		gcc $(LOPTS) test-sll.o integer.o sll.o -o test-sll

test-queue : test-queue.o integer.o sll.o queue.o
		gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-bst : test-bst.o integer.o sll.o queue.o bst.o
		gcc $(LOPTS) test-bst.o integer.o sll.o queue.o bst.o -o test-bst

test-gst : test-gst.o integer.o sll.o queue.o bst.o gst.o
		gcc $(LOPTS) test-gst.o integer.o sll.o queue.o bst.o gst.o -o test-gst

test-avl : test-avl.o integer.o sll.o queue.o bst.o avl.o
		gcc $(LOPTS) test-gst.o integer.o sll.o queue.o bst.o gst.o -o test-avl

# trees : trees.o real.o string.o scanner.o integer.o sll.o queue.o bst.o gst.o avl.o
# 		gcc $(LOPTS) trees.o real.o string.o scanner.o integer.o sll.o queue.o bst.o gst.o avl.o -o trees

test-sll.o : test-sll.c sll.h integer.h
		gcc $(OOPTS) test-sll.c

test-queue.o : test-queue.c queue.h sll.h integer.h
		gcc $(OOPTS) test-queue.c

test-bst.o : test-bst.c bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-bst.c

test-gst.o : test-gst.c gst.h bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-gst.c

test-avl.o : test-avl.c avl.h bst.h queue.h sll.h integer.h
		gcc $(OOPTS) test-avl.c

# trees.o : trees.c real.h string.h scanner.h integer.h sll.h queue.h bst.h gst.h avl.h
# 		gcc $(OOPTS) trees.c

avl.o : avl.c bst.h queue.h sll.h
		gcc $(OOPTS) avl.c

gst.o : gst.c bst.h queue.h sll.h
		gcc $(OOPTS) gst.c

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
	echo testing queue
	valgrind ./test-queue
	echo testing binary search tree
	valgrind ./test-bst
	echo testing green tree
	valgrind ./test-gst
	echo testing avl tree
	valgrind ./test-avl

test : all
	echo testing singly-linked list
	./test-sll
	echo testing queue
	./test-queue
	echo testing binary search tree
	./test-bst
	echo testing green tree
	./test-gst
	echo testing avl tree
	./test-avl

clean	:
		rm -f $(OBJS) *.o test-*.o test-queue test-sll test-bst test-gst test-avl 
