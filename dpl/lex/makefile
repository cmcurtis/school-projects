# # In order to execute this "Makefile" just type "make" 

OBJS = types.o lexeme.o scanner.o lexer.o 
SOURCE = types.c lexeme.c scanner.c lexer.c 
HEADER = types.h lexeme.h scanner.h lexer.h
OUT = scanner 
CC = gcc 
FLAGS = -g -c -Wall 
LFLAGS = 
# -g option enables debugging mode 
# -c flag generates object code for separate files 

all: $(OBJS) 
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 

# create/compile the individual files >>separately<< 
types.o: types.c 
	$(CC) $(FLAGS) types.c -std=c99 

scanner.o: scanner.c 
	$(CC) $(FLAGS) scanner.c -std=c99

lexer.o: lexer.c 
	$(CC) $(FLAGS) lexer.c -std=c99

scanner : 
	$(OBJS) $(CC) -g \ $(OBJS) -o scanner

test1 : 
	./scanner test1.txt

# clean house 
clean: 
	rm -f $(OBJS) $(OUT) 