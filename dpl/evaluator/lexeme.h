//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lexeme lexeme;

extern char *getType(lexeme *l);
extern char* getSval(lexeme *l);
extern int getIval(lexeme *l);
extern double getRval(lexeme *l);
extern char* getKval(lexeme *l);
extern char* getFval(lexeme *l);
extern int getLineNum(lexeme *l);

extern lexeme *car(lexeme *x);
extern lexeme *cdr(lexeme *x);
extern void setCar(lexeme *x, lexeme *y);
extern void setCdr(lexeme *x, lexeme *y);
extern lexeme *cons(char *type, lexeme *left, lexeme *right);

extern lexeme *newLexeme(char *t, int n);
extern lexeme *newErrorLexeme(char *err, char *message, int n);
extern lexeme *newLexemeInt(int x, int n);
extern lexeme *newLexemeReal(double x, int n);
extern lexeme *newLexemeChar(char *type, char *x, int n);
extern lexeme *newLexemeKeyword(char *type, char *x, int n);
extern void displayLexeme(lexeme *x);

