OBJS = types.o lexeme.o recognizer.o lexer.o 
SOURCE = types.c lexeme.c recognizer.c lexer.c 
HEADER = types.h lexeme.h recognizer.h lexer.h
OUT = recognizer 
CC = gcc 
FLAGS = -g -c -Wall 
LFLAGS = 

all : $(OBJS) 
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 

types.o : types.c
	$(CC) $(FLAGS) types.c -std=c99 

recognizer.o : recognizer.c
	$(CC) $(FLAGS) recognizer.c -std=c99

lexer.o : lexer.c 
	$(CC) $(FLAGS) lexer.c -std=c99

run : all
	-./recognizer test1.txt
	-./recognizer test2.txt
	-./recognizer test3.txt
	-./recognizer test4.txt
	-./recognizer test5.txt

test1 : 
	./recognizer test1.txt

test2 : 
	./recognizer test2.txt

test3 : 
	./recognizer test3.txt

test4 : 
	./recognizer test4.txt

test5 : 
	./recognizer test5.txt

# clean house 
clean: 
	rm -f $(OBJS) $(OUT) 