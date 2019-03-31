OBJS = types.o lexeme.o parser.o lexer.o environ.o eval.o
SOURCE = types.c lexeme.c parser.c lexer.c environ.c eval.c
HEADER = types.h lexeme.h parser.h lexer.h environ.h eval.h
OUT = eval
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

run : all
	-./eval test1.txt
	-./eval test2.txt
	-./eval test3.txt
	-./eval test4.txt
	-./eval test5.txt

error1 :
	cat error1.txt

error1x :
	./eval error1.txt

error2 :
	cat error2.txt

error2x :
	./eval error2.txt

error3 :
	cat error3.txt

error3x :
	./eval error3.txt

error4 :
	cat error4.txt

error4x :
	./eval error4.txt

error5 :
	cat error5.txt

error5x :
	./eval error5.txt

arrays :
	cat arrays.txt

arraysx :
	./eval arrays.txt

conditionals :
	cat conditionals.txt

conditionalsx :
	./eval conditionals.txt

recursion :
	cat recursion.txt

recursionx :
	./eval recursion.txt

iteration :
	cat iteration.txt

iterationx :
	./eval iteration.txt

functions :
	cat functions.txt

functionsx : # shows you can pass functions and return nested functions
	./eval functions.txt

lambda :   
	cat lambda.txt

lambdax :
	./eval lambda.txt

objects : 
	cat objects.txt

objectsx :  # get and update field, method call (e.g. setter)
	./eval objects.txt

problem :
	cat problem.txt

problemx :
	.eval problem.txt

# clean house 
clean: 
	rm -f $(OBJS) $(OUT) 