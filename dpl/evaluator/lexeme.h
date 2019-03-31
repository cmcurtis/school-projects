//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lexeme lexeme;

extern char *getType(lexeme *l);
extern void setType(lexeme *l, char *type);
extern char* getSval(lexeme *l);
extern int getIval(lexeme *l);
extern double getRval(lexeme *l);
extern char* getKval(lexeme *l);
extern FILE* getFval(lexeme *l);
extern void setFval(lexeme *l, FILE *fp);
extern int getLineNum(lexeme *l);

extern lexeme** getAval(lexeme* l);
extern void setAval(lexeme *l, lexeme* v, int i);
void newAval(lexeme *l, int size);


extern lexeme *car(lexeme *x);
extern lexeme *cdr(lexeme *x);
extern void setCar(lexeme *x, lexeme *y);
extern void setCdr(lexeme *x, lexeme *y);
extern lexeme *cons(char *type, lexeme *left, lexeme *right);

extern lexeme *newLexeme(char *t, int n);
extern lexeme *newErrorLexeme(char *err, char *message, lexeme *n);
extern lexeme *newLexemeBool(int x, int n);
extern lexeme *newLexemeInt(int x, int n);
extern lexeme *newLexemeReal(double x, int n);
extern lexeme *newLexemeChar(char *type, char *x, int n);
extern lexeme *newLexemeKeyword(char *type, char *x, int n);
extern void displayLexeme(lexeme *x);

