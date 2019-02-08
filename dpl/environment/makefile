OBJS = types.o lexeme.o environ.o tester.o 
SOURCE = types.c lexeme.c environ.c tester.c 
HEADER = types.h lexeme.h environ.h 
OUT = environment
CC = gcc 
FLAGS = -g -c -Wall 
LFLAGS = 

all : $(OBJS) 
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 

types.o : types.c
	$(CC) $(FLAGS) types.c -std=c99 

environ.o : environ.c
	$(CC) $(FLAGS) environ.c -std=c99

tester.o : tester.c 
	$(CC) $(FLAGS) tester.c -std=c99

run : all
	./environment

# clean house 
clean: 
	rm -f $(OBJS) $(OUT) 