OBJS = types.o lexeme.o parser.o lexer.o environ.o eval.o
SOURCE = types.c lexeme.c parser.c lexer.c environ.c eval.c
HEADER = types.h lexeme.h parser.h lexer.h environ.h eval.h
OUT = mylang
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

environ.o : environ.c
	$(CC) $(FLAGS) environ.c -std=c99

eval.o : eval.c
	$(CC) $(FLAGS) eval.c -std=c99

error1 :
	cat error1.txt

error1x :
	./mylang error1.txt || true

error2 :
	cat error2.txt

error2x :
	./mylang error2.txt || true

error3 :
	cat error3.txt 

error3x :
	./mylang error3.txt || true

error4 :
	cat error4.txt

error4x :
	./mylang error4.txt || true

error5 :
	cat error5.txt

error5x :
	./mylang error5.txt || true

arrays :
	cat arrays.txt

arraysx :
	./mylang arrays.txt || true

conditionals :
	cat conditionals.txt

conditionalsx :
	./mylang conditionals.txt || true

recursion :
	cat recursion.txt

recursionx :
	./mylang recursion.txt || true

iteration :
	cat iteration.txt

iterationx :
	./mylang iteration.txt || true

functions :
	cat functions.txt

functionsx : # shows you can pass functions and return nested functions
	./mylang functions.txt || true

lambda :   
	cat lambda.txt

lambdax :
	./mylang lambda.txt || true

objects : 
	cat objects.txt

objectsx :  # get and update field, method call (e.g. setter)
	./mylang objects.txt || true

problem :
	cat problem.txt

problemx :
	./mylang problem.txt || true

# clean house 
clean: 
	rm -f $(OBJS) $(OUT) 